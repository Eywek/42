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
  async.race([
    // (next) => {
    //   console.log('Search in kickass-api...')
    //   kickass.search({
    //     query: movieTitle,
    //     sort_by: 'seeders',
    //     order: 'desc',
    //   }).then((results) => {
    //     console.log('Found ' + results.length + ' results in kickass-api')
    //     if (results.length > 0)
    //       next(undefined, results[0])
    //     else
    //       next(undefined, null)
    //   }).catch(() => {
    //     console.log('Found 0 results in kickass-api')
    //     next(undefined, null)
    //   })
    // },

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
  ], (err, result) => {
    if (err) {
      console.error(err)
      return callback()
    }

    // Torrent
    if (!result) {
      console.log('No torrent found')
      return callback()
    }
    let torrent = result
    console.log('Torrent magnet: ' + torrent.magnetLink || torrent.magnet)
    callback(torrent.magnetLink || torrent.magnet, 'test.mp4') // TODO
  })
}

module.exports = {

  view: (req, res) => {
    movieModel.get(req.params.title, (movie) => {
      if (!movie)
        return res.sendStatus(404)
      res.render('Movie/view', {title: movie.title, movie: movie})
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

      let movies = results.results || []
      async.eachOf(movies, (movie, i, next) => {
        db.query('SELECT `id` FROM `movies` WHERE `media_id` = ?', [movie.id], (err, rows) => {
          if (err)
            console.error(err)
          if (rows && rows.length > 0)
            return next()
          if (movie.media_type === 'tv') {
            movieModel.insert(movie, () => {})
            return next()
          }
          // Try to find torrent if a movie
          if (!movie.title)
            movie.title = movie.name
          findTorrent(movie.title, (magnet, file) => {
            if (!magnet) { // torrent not found
              delete movies[i]
              movies.length--
              return next()
            }
            movie.magnet = magnet
            let ext = path.extname(file)
            movie.file = movie.title + (ext === 'mp4' || ext === 'webm' ? ext : 'webm')
            movies[i] = movie
            if (!rows || rows.length === 0)
              movieModel.insert(movie, () => {})
            next()
          })
        })
      }, () => {
        res.json({status: true, success: res.__('Find %s results', movies.length),  results: movies})
      })
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