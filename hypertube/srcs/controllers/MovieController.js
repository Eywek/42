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
const kickass = require('kickass-api')

const insertMovie = (result, next, season, episode, parent_id) => {
  result.poster_path = result.poster_path || ''
  console.log('Inserting ' + (result.name ? result.name : result.title) + (season ? ' S' + season + 'E' + episode + ' parent_id:' + parent_id : ''))
  db.query('INSERT INTO `movies` SET `parent_id` = ?, `title` = ?, media_id = ?, media_type = ?, poster_path = ?, backdrop_path = ?, vote_average = ?, date = ?, overview = ?, season = ?, episode = ?, created_at = ?', [
    parent_id,
    result.name || result.title,
    result.id,
    (season ? 'tv' : result.media_type),
    result.poster_path,
    result.backdrop_path || result.poster_path,
    result.vote_average,
    result.release_date || result.first_air_date || result.air_date,
    result.overview,
    season,
    episode,
    new Date()
  ], (err, rows) => {
    if (err)
      console.error(err)
    next(err, rows)
  })
}
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
const convert = function (file) {
  console.log('Start converting file...')
  return new ffmpeg(file.createReadStream())
    .videoCodec('libvpx')
    .audioCodec('libvorbis')
    .format('webm')
    .audioBitrate(128)
    .videoBitrate(1024)
    .outputOptions([
      '-threads 8',
      '-deadline realtime',
      '-error-resilient 1'
    ])
    .on('end', function () {
      console.log('File is now webm !')
    })
    .on('error', function (err) {
      console.log('Error', err)
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
    //sendHeaders(req, res, file.length, type)

    // CONVERT
    let videoStream = (ext !== '.webm' && ext !== '.mp4') ? convert(file) : file.createReadStream()
    ext = (ext !== '.webm' && ext !== '.mp4') ? '.webm' : ext

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

    videoStream.pipe(fileStream)
    videoStream.pipe(responseStream)
  })
}
const findTorrent = (movieTitle, callback) => {
  // Find torrent
  console.log('Try to find torrent for ' + movieTitle + '...')
  async.parallel([
    (next) => {
      /*console.log('Search in kickass-api...')
      kickass.search({
        query: movieTitle,
        sort_by: 'seeders',
        order: 'desc',
      }).then((results) => {
        console.log('Found ' + results.length + ' results in kickass-api')
        if (results.length > 0)
          next(undefined, results[0])
        else
          next(undefined, null)
      }).catch(() => {
        console.log('Found 0 results in kickass-api')
        next(undefined, null)
      })*/
      next(undefined, null)
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
        next(undefined, results[0])
      })
    }
  ], (err, results) => {
    console.log(err, results)
    if (err) {
      console.error(err)
      return callback()
    }

    // Torrent
    if (!results[0] && !results[1]) {
      console.log('No torrent found')
      return callback()
    }
    let torrent = {}
    if (!results[0])
      torrent = results[1]
    else if (!results[1])
      torrent = results[0]
    else if (results[0].seeds > results[1].seeders)
      torrent = results[0]
    else
      torrent = results[1]

    console.log('Torrent magnet: ' + torrent.magnetLink || torrent.magnet)
    callback(torrent.magnetLink || torrent.magnet)
  })
}

module.exports = {

  view: (req, res) => {
    let searchQuery = 'SELECT * FROM `movies` WHERE `title` = ?'
    db.query(searchQuery, [req.params.title], (err, rows) => {
      if (err) {
        console.error(err)
        return res.sendStatus(500)
      }
      let next = (movie) => {
        let render = () => {
          res.render('Movie/view', {title: movie.title, movie: movie})
        }

        movie.type = (movie.downloaded ? path.extname(movie.file) : 'webm')

        if (movie.media_type === 'movie')
          return render()
        movie.seasons = {}
        // GET SEASONS
        mdb.tvInfo({
          id: movie.media_id
        }, (err, result) => {
          if (err) {
            console.error(err)
            return res.sendStatus(500)
          }

          // GET EPISODES
          async.each(result.seasons, (season, cb) => {
            mdb.tvSeasonInfo({
              id: movie.media_id,
              season_number: season.season_number
            }, (err, results) => {
              if (err) {
                console.error(err)
                return res.sendStatus(500)
              }

              // SAVE INTO DB
              async.each(results.episodes, (result, next) => {
                db.query('SELECT `id` FROM `movies` WHERE `parent_id` = ? AND `season` = ? AND `episode` = ?', [movie.id, season.season_number, result.episode_number], function (err, rows) {
                  if (err)
                    console.error(err)
                  if (!rows || rows.length === 0)
                    insertMovie(result, next, season.season_number, result.episode_number, movie.id)
                })
              }, () => {})
              movie.seasons[season.season_number] = results.episodes
              cb()
            })
          }, () => {
            render()
          })
        })
      }

      // ALREADY SAVED
      if (rows && rows.length > 0)
        return next(rows[0])

      // FIND MOVIE
      mdb.searchMulti({
        query: req.body.query
      }, (err, results) => {
        if (err)
          return res.sendStatus(500)
        insertMovie(results.results[0], (err, rows) => {
          db.query(searchQuery, [rows.insertId], (err, rows) => {
            if (err) {
              console.error(err)
              return res.sendStatus(500)
            }
            next(rows[0])
          })
        })
      })
    })
  },

  search: (req, res) => {
    if (!req.body.query)
      return res.json({status: false, error: res.__('Please, fill the form')})
    mdb.searchMulti({
      query: req.body.query
    }, (err, results) => {
      if (err)
        return res.json({status: false, error: (err.response && err.response.text) ? err.response.text : res.__('Internal error')})

      // RENDER
      res.json({status: true, success: res.__('Find %s results', results.results.length || 0),  results: results.results || []})

      // SAVE INTO DB
      async.each(results.results, (result, next) => {
        db.query('SELECT `id` FROM `movies` WHERE `media_id` = ?', [result.id], (err, rows) => {
          if (err)
            console.error(err)
          if (!rows || rows.length === 0)
            insertMovie(result, next)
          else
            next()
        })
      }, () => {})
    })
  },

  stream: (req, res) => {
    // Find torrent
    db.query('SELECT `movies`.`id`, `movies`.`file`, `movies`.`downloaded`, `movies`.`title`, `movies`.`episode`, `movies`.`season`, `parent`.`title` AS `parent_title` FROM `movies` ' +
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
        let [start, end] = sendHeaders(req, res, fs.statSync(filePath).size, path.extname(filePath))

        // CREATE STREAM
        fs.createReadStream(filePath, {
          start: start,
          end: end
        }).pipe(res)
        return
      }

      if (movie.episode)
        movie.title = movie.parent_title + ' S' + (movie.season.toString().length === 1 ? '0' + movie.season : movie.season) + 'E' + (movie.episode.toString().length === 1 ? '0' + movie.episode : movie.episode)

      // IF DOWNLOADING
      if (downloadingStreams[movie.title]) {
        let file = downloadingStreams[movie.title]
        let ext = path.extname(file.name)
        console.log('Already downloading, streaming download...')

        // HEADER
        //sendHeaders(req, res, file.length, type)

        // CONVERTING
        let videoStream = (ext !== '.webm' && ext !== '.mp4') ? convert(file) : file.createReadStream()

        // STREAMING
        pump(videoStream, res)
        return
      }

      // DONWLOAD
      findTorrent(movie.title, (magnetLink) => {
        console.log(movie.title, magnetLink)
        if (!magnetLink)
          return res.sendStatus(404)
        streaming(movie.title, magnetLink, req, res, (filename) => {
          db.query('UPDATE `movies` SET `downloaded` = 1, `file` = ? WHERE `id` = ?', [filename, movie.id], (err) => {
            if (err)
              console.error(err)
            else
              console.log(filename + ' is downloaded now')
          })
        })
      })
    })
  },

  library: (req, res) => {

  }

}