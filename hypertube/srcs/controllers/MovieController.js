const db = require('../models/database')
const config = require('../../config/config')
const mdb = require('moviedb')(config.movieDbAPIKey)
const async = require('async')
const torrentStream = require('torrent-stream')
const ffmpeg = require('fluent-ffmpeg')
const pump = require('pump')
const stream = require('stream')
const thepiratebay = require('thepiratebay')
const path = require('path')
const fs = require('fs')
const movieModel = require('../models/movie')
const TorrentSearchApi = require('torrent-search-api')
const torrentSearch = new TorrentSearchApi()
const srt2vtt = require('srt-to-vtt')
const opensubtitles = require("subtitler")
const request = require('request')
torrentSearch.enableProvider('Torrent9')

const sendHeaders = function (req, res, size, type) {
  let range = req.headers.range
  let positions = range.replace(/bytes=/, "").split("-")
  let start = parseInt(positions[0], 10)
  let total = size
  let end = positions[1] ? parseInt(positions[1], 10) : total - 1
  let chunksize = (end - start) + 1

  res.writeHead(206, {
    "Content-Range": "bytes " + start + "-" + end + "/" + total,
    "Accept-Ranges": "bytes",
    "Content-Length": chunksize,
    "Content-Type": "video/" + type
  })
  return [start, end]
}
const convert = function (file, thread) {
  if (!thread)
    thread = 8
  console.log('Start converting file...')
  return new ffmpeg(file.createReadStream())
    .videoCodec('libvpx')
    .audioCodec('libvorbis')
    .format('webm')
    .audioBitrate(128)
    .videoBitrate(1024)
    .outputOptions([
      '-threads ' + thread,
      '-deadline realtime',
      '-error-resilient 1'
    ])
    .on('end', function () {
      console.log('File is now webm !')
    })
    .on('error', function (err) {
    })
}
let downloadingStreams = {}
const streaming = (filename, magnetLink, req, res, onFileWrited) => {
  // CALCULS
  let range = req.headers.range
  if (!range)
    return res.sendStatus(416)

  console.log('File doesn\'t exist ! Start downloading...')

  // INIT DOWNLOAD
  let engine = torrentStream(magnetLink)
  engine.on('ready', function() {
    console.log('Download ended!')

    // GET THE FILE
    engine.files = engine.files.sort(function (a, b) {
      return b.length - a.length
    }).slice(0, 1)
    let file = engine.files[0]
    let ext = path.extname(file.name)
    console.log('File found! (' + file.name + ')')
    downloadingStreams[filename] = file

    // HEADER
    //sendHeaders(req, res, file.length, (ext !== '.webm' && ext !== '.mp4') ? 'webm' : ext.substr(1))

    // CONVERT
    let needConvert = (ext !== '.webm' && ext !== '.mp4')
    let videoStream = needConvert ? convert(file) : file.createReadStream()
    ext = needConvert ? '.webm' : ext

    // MULTIPLE STREAMS
    let filePath = path.join(__dirname, '../../files/' + filename + ext)
    let fileStream = fs.createWriteStream(filePath)
    let responseStream = new stream.Writable()
    let responseClosed = false

    res.on('close', function () {
      console.log('Response closed!')
      responseClosed = true
    })
    let onFileClose = function (err) {
      console.log('File closed!')
      if (err)
        console.error(err)
    }
    fileStream.on('close', onFileClose).on('error', onFileClose).on('finish', () => {
      console.log('File is now on disk!')
      onFileWrited(filename + ext)
    })
    videoStream.on('end', () => {
      console.log('Video stream has reached is end')
    })

    responseStream._write = (chunk, encoding, done) => {
      let checker = setInterval(() => {
        if (responseClosed)
          cb()
      }, 50)
      let cb = () => {
        clearInterval(checker)
        done()
      }
      if (responseClosed)
        return cb()
      res.write(chunk, encoding, cb)
    }
    responseStream.on('end', () => {
      console.log('Response stream has reached is end')
      res.end()
    })

    if (needConvert) {
      console.log('Pumping to res and file...')
      pump(videoStream, fileStream)
      pump(convert(file, 2), responseStream)
    } else {
      console.log('Piping to res and file...')
      videoStream.pipe(fileStream)
      videoStream.pipe(responseStream)
    }
  })
}
const findTorrent = (movieTitle, callback) => {
  // Find torrent
  console.log('Try to find torrent for ' + movieTitle + '...')
  async.race([
    (next) => {
      console.log('Search in torrent9...')
      torrentSearch.search(movieTitle)
      .then(torrents => {
        console.log('Found ' + torrents.length + ' results in torrent9')
        if (!torrents || torrents.length === 0)
          return
        torrentSearch.getMagnet(torrents[0])
          .then(magnet => {
            next(undefined, magnet)
          })
          .catch(err => {
            console.log(err)
          })
      })
      .catch(err => {
        console.log(err)
      });
    },

    (next) => {
      console.log('Search in thepiratebay...')
      thepiratebay.search(movieTitle, {
        filter: {
          verified: false
        },
        category: 'video',
        orderBy: 'seeds',
        sortBy: 'desc'
      }).then(function(results) {
        console.log('Found ' + results.length + ' results in thepiratebay')
        next(undefined, (results && results[0]) ? results[0].magnetLink : undefined)
      })
    }
  ], (err, magnet) => {
    if (err) {
      console.error(err)
      return callback()
    }

    // Torrent
    if (!magnet) {
      console.log('No torrent found')
      return callback()
    }
    console.log('Torrent magnet: ' + magnet)
    callback(magnet)
  })
}
const getFullLanguage = (lang) => {
  let content
  if ((content = JSON.parse(fs.readFileSync(path.join(__dirname, '../../locales/languages.json')))[lang]))
    return content.name || lang
  return lang
}

module.exports = {

  view: (req, res) => {
    movieModel.get(req.params.title, req.user.language, (movie) => {
      if (!movie)
        return res.sendStatus(404)
      db.query('SELECT `comments`.`content`, `comments`.`id`, `users`.`username`, `users`.`id` AS `user_id`, `comments`.`created_at` ' +
        'FROM `comments` ' +
        'INNER JOIN `users` ON `users`.`id` = `comments`.`user_id` ' +
        'WHERE `movie_id` = ?', [movie.id], (err, comments) => {
        if (err)
          console.error(err)
        if (!comments)
          comments = []

        db.query('SELECT `users`.`id`, `users`.`username`, `likes`.`id` AS `liked` ' +
          'FROM `users` ' +
          'LEFT JOIN `likes` ON `likes`.`user_id` = `users`.`id` AND `movie_id` = ? ' +
          'WHERE `users`.`id` = ?', [movie.id, req.session.user], (err, user) => {
          if (err) {
            console.error(err)
            return res.sendStatus(500)
          }
          if (!user || user.length === 0)
            return res.sendStatus(404)

          res.render('Movie/view', {title: movie.title, movie: movie, comments: comments.map((comment) => {
            comment.user_avatar = fs.existsSync(path.join(__dirname, '../../public/uploads/' + comment.user_id + '.png')) ? '/uploads/' + comment.user_id + '.png' : '/assets/img/default_profile_pic.png'
            return comment
          }), user: {
            username: user[0].username,
            avatar: fs.existsSync(path.join(__dirname, '../../public/uploads/' + user[0].id + '.png')) ? '/uploads/' + user[0].id + '.png' : '/assets/img/default_profile_pic.png',
            liked: user[0].liked
          }})
        })
      })
    })
  },

  search: (req, res) => {
    if (!req.body.query)
      return res.json({status: false, error: res.__('Please, fill the form')})
    mdb.searchMulti({
      query: req.body.query,
      language: req.user.language
    }, (err, results) => {
      if (err)
        return res.json({status: false, error: (err.response && err.response.text) ? err.response.text : res.__('Internal error')})

      let movies = results.results.slice(0, 3) || []
      let total = movies.length
      async.eachOf(movies, (movie, i, next) => {
        db.query('SELECT `movies`.`id`, `views`.`id` AS `viewed` FROM `movies` ' +
          'LEFT JOIN `views` ON `views`.`movie_id` = `movies`.`id` ' +
          'WHERE `movies`.`media_id` = ?', [movie.id], (err, rows) => {
          if (err)
            console.error(err)

          movies[i] = {
            original: movie.original_name || movie.original_title || movie.name || movie.title,
            title: movie.name || movie.title,
            media_type: movie.media_type,
            overview: movie.overview,
            poster_path: movie.poster_path,
            date: movie.release_date || movie.first_air_date || movie.air_date,
            vote_average: movie.vote_average,
            viewed: (rows && rows.length > 0 && rows[0].viewed)
          }

          if (rows && rows.length > 0)
            return next()
          if (movie.media_type === 'tv') {
            movieModel.insert(movie, () => {})
            return next()
          }
          // Try to find torrent if a movie
          if (!movie.original_title)
            movie.original_title = movie.original_name || movie.title || movie.name
          if (!rows || rows.length === 0)
            movieModel.insert(movie, () => {})
          next()
        })
      }, () => {
        res.json({status: true, success: res.__('Find %s results', total),  results: movies})
      })
    })
  },

  stream: (req, res) => {
    // Find torrent
    db.query('SELECT `movies`.`id`, `movies`.`file`, `movies`.`downloaded`, `movies`.`media_id`, `movies`.`title`, `movies`.`episode`, `movies`.`season`, `parent`.`title` AS `parent_title` FROM `movies` ' +
      'LEFT JOIN `movies` AS `parent` ON `parent`.`id` = `movies`.`parent_id` ' +
      'WHERE `movies`.`id` = ?', [req.params.id], (err, rows) => {
      if (err) {
        console.error(err)
        return res.sendStatus(500)
      }

      if (!rows || rows.length === 0) {
        console.log('Film #' + req.params.id + ' not found')
        return res.sendStatus(404)
      }
      let movie = rows[0]

      if (movie.downloaded) {
        // HEADERS
        let filePath = path.join(__dirname, '../../files/' + movie.file)
        let [start, end] = sendHeaders(req, res, fs.statSync(filePath).size, path.extname(filePath).substr(1))

        // CREATE STREAM
        fs.createReadStream(filePath, {
          start: start,
          end: end
        }).pipe(res)
        return
      }

      if (movie.episode)
        movie.title = movie.parent_title + ' S' + (movie.season.toString().length === 1 ? '0' + movie.season : movie.season) + 'E' + (movie.episode.toString().length === 1 ? '0' + movie.episode : movie.episode)
      db.query('UPDATE `movies` SET `views` = `views` + 1 WHERE `id` = ?', [movie.id], () => {})
      db.query('INSERT INTO `views` SET `media_id` = ?, `movie_id` = ?, `user_id` = ?, `created_at` = ?', [movie.media_id, movie.id, req.session.user, new Date()], () => {})

      // IF DOWNLOADING
      if (downloadingStreams[movie.title]) {
        let file = downloadingStreams[movie.title]
        let ext = path.extname(file.name)
        console.log('Already downloading, streaming download...')

        // HEADER
        //sendHeaders(req, res, file.length, (ext !== '.webm' && ext !== '.mp4') ? 'webm' : ext.substr(1))

        // CONVERTING
        let videoStream = (ext !== '.webm' && ext !== '.mp4') ? convert(file) : file.createReadStream()

        // STREAMING
        pump(videoStream, res)
        return
      }

      let stream = (magnetLink) => {
        streaming(movie.title, magnetLink, req, res, (filename) => {
          db.query('UPDATE `movies` SET `downloaded` = 1, `file` = ? WHERE `id` = ?', [filename, movie.id], (err) => {
            if (err)
              console.error(err)
            else
              console.log(filename + ' is downloaded now')
          })
        })
      }

      // DONWLOAD
      findTorrent(movie.title, (magnetLink) => {
        if (!magnetLink)
          return res.sendStatus(404)
        stream(magnetLink)
      })
    })
  },

  subtitles: (req, res) => {
    // Find torrent
    db.query('SELECT `movies`.`title`, `movies`.`episode`, `movies`.`season`, `parent`.`title` AS `parent_title` FROM `movies` ' +
      'LEFT JOIN `movies` AS `parent` ON `parent`.`id` = `movies`.`parent_id` ' +
      'WHERE `movies`.`id` = ?', [req.params.id], (err, rows) => {
      if (err) {
        console.error(err)
        return res.sendStatus(500)
      }

      if (!rows || rows.length === 0)
        return res.sendStatus(404)
      let movie = rows[0]

      const lang = getFullLanguage(req.params.lang)
      if (movie.episode)
        movie.title = movie.parent_title + ' S' + (movie.season.toString().length === 1 ? '0' + movie.season : movie.season) + 'E' + (movie.episode.toString().length === 1 ? '0' + movie.episode : movie.episode)
      console.log('Downloading subtitles (' + lang + ') for ' + movie.title + ' ...')
      opensubtitles.api.login().then((token) => {
        opensubtitles.api.searchForTitle(token, lang, movie.title).then((results) => {

          console.log(results.length + ' subtitles found')
          if (results.length === 0)
            res.sendStatus(404)
          let subtitle = results.filter((result) => {
            return result.LanguageName === lang
          }).splice(0, 1)[0]
          let file = subtitle.SubDownloadLink.slice(0, -3)

          res.writeHead(200, {
            "Content-Type": "text/vtt"
          })

          let filename = path.join(__dirname, '../../files/' + movie.title + '-' + lang + '-' + Math.round(Math.random() * 100) +  '.srt')
          let writeStream = fs.createWriteStream(filename)
          writeStream.on('finish', () => {
            let readStream = fs.createReadStream(filename)
            readStream.on('end', () => {
              fs.unlinkSync(filename)
            })
            readStream.pipe(srt2vtt()).pipe(res)
          })
          request.get(file).pipe(writeStream)
        })
      })
    })
  },

  library: (req, res) => { // `date` DESC, `vote_average` DESC
    let order = ''
    if (req.body.order.vote_average)
      order = 'vote_average.' + (req.body.order.vote_average === 'DESC' ? 'desc' : 'asc')
    if (req.body.order.date)
      order = 'release_date.' + (req.body.order.date === 'DESC' ? 'desc' : 'asc')

    async.parallel([
      (cb) => {
        if (req.body.noMovie == 'true')
          return cb(undefined, [])
        mdb.discoverMovie({
          language: req.user.language,
          sort_by: order,
          page: parseInt(req.params.page),
          'release_date.lte': new Date(req.body.releaseDate.max),
          'release_date.gte': new Date(req.body.releaseDate.min),
          'vote_average.lte': req.body.note.max,
          'vote_average.gte': req.body.note.min
        }, (err, movies) => {
          cb(err, movies)
        })
      },
      (cb) => {
        if (req.body.noTv == 'true')
          return cb(undefined, [])
        mdb.discoverTv({
          language: req.user.language,
          sort_by: order.replace('release_date', 'air_date'),
          page: parseInt(req.params.page),
          'air_date.lte': new Date(req.body.releaseDate.max),
          'air_date.gte': new Date(req.body.releaseDate.min),
          'vote_average.lte': req.body.note.max,
          'vote_average.gte': req.body.note.min
        }, (err, movies) => {
          cb(err, movies)
        })
      }
    ], (err, results) => {
      if (err)
        console.error(err)
      let movies = []
      if (!results[0] || !results[0].results)
        results[0] = {results: []}
      if (!results[1] || !results[1].results)
        results[1] = {results: []}

      for (let i = 0; i < results[0].results.length; i++) {
        if (results[0].results[i])
          movies.push({
            title: results[0].results[i].title,
            original: results[0].results[i].original_title,
            media_type: 'movie',
            poster_path: results[0].results[i].poster_path,
            date: results[0].results[i].release_date,
            media_id: results[0].results[i].id,
            vote_average: results[0].results[i].vote_average,
          })
      }
      for (let i = 0; i < results[1].results.length; i++) {
        if (results[1].results[i])
          movies.push({
            title: results[1].results[i].name,
            original: results[1].results[i].original_name,
            media_type: 'tv',
            poster_path: results[1].results[i].poster_path,
            date: results[1].results[i].first_air_date,
            media_id: results[1].results[i].id,
            vote_average: results[1].results[i].vote_average,
          })
      }
      res.json({status: true, movies: movies})
    })
  },

  comment: (req, res) => {
    if (!req.body.content || req.body.content.length < 10)
      return res.json({status: false, error: res.__('The content of the comment need to have minimum 10 characters.')})
    db.query('SELECT `id` FROM `movies` WHERE `title` = ?', [req.params.title], (err, rows) => {
      if (err) {
        console.error(err)
        return res.sendStatus(500)
      }
      if (!rows || rows.length === 0)
        return res.sendStatus(404)

      db.query('INSERT INTO `comments` SET `content` = ?, `user_id` = ?, `movie_id` = ?, `created_at` = ?', [
        req.body.content,
        req.session.user,
        rows[0].id,
        new Date()
      ], (err, rows) => {
        if (err)
          console.error(err)
        return res.json({status: true, success: res.__('Comment has been added!'), data: {comment: {id: rows.insertId}}})
      })
    })
  },

  deleteComment: (req, res) => {
    db.query('DELETE FROM `comments` WHERE `id` = ? AND `user_id` = ?', [req.params.comment_id, req.session.user], (err) => {
      if (err)
        console.error(err)
    })
    res.json({})
  },

  like: (req, res) => {
    db.query('SELECT `movies`.`id`, `likes`.`id` AS `like_id` ' +
      'FROM `movies` ' +
      'LEFT JOIN `likes` ON `likes`.`movie_id` = `movies`.`id` AND `likes`.`user_id` = ? ' +
      'WHERE `movies`.`title` = ? ', [req.session.user, req.params.title], (err, rows) => {
      if (err)
        return console.error(err)
      if (!rows || rows.length === 0)
        return

      if (rows[0].like_id)
        db.query('DELETE FROM `likes` WHERE `id` = ?', [rows[0].like_id], (err) => {
          if (err)
            return console.error(err)
        })
      else
        db.query('INSERT INTO `likes` SET `user_id` = ?, `movie_id` = ?', [
          req.session.user,
          rows[0].id
        ], (err) => {
          if (err)
            return console.error(err)
        })
    })
    res.json({})
  },

}