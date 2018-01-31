const db = require('./database')
const config = require('../../config/config')
const mdb = require('moviedb')(config.movieDbAPIKey)
const path = require('path')
const async = require('async')
const _ = require('underscore')

const insertNewEpisodes = (media_id, db_id, season, episodesAlreadySaved, callback) => {
  mdb.tvSeasonInfo({
    id: media_id,
    season_number: season
  }, (err, infos) => {
    if (err) {
      console.error(err)
      return callback(err)
    }
    // Insert new episodes
    async.map(infos.episodes, (episode, cb) => {
      let returnEpisode = {
        id: episodesAlreadySaved[episode.episode_number] || null,
        title: episode.name,
        file: null,
        downloaded: null,
        episode: episode.episode_number,
        season: season
      }
      if (episodesAlreadySaved[episode.episode_number]) // already saved
        return cb(undefined, returnEpisode)
      insert(episode, (err, rows) => {
        returnEpisode.id = rows.insertId
        return cb(undefined, returnEpisode)
      }, season, episode.episode_number, db_id)
    }, callback)
  })
}

const getEpisodesFromSeasons = (media, db_id, next) => {
  seasons = {}
  db.query('SELECT `id`, `title`, `file`, `downloaded`, `episode`, `season` FROM `movies` WHERE `parent_id` = ? ORDER BY season,episode', [db_id], (err, episodes) => {
    if (err) {
      console.error(err)
      return next({})
    }
    let seasons = _.groupBy(episodes, 'season')
    let movieSeasonsEpisodeCount = {}
    for (let i = 0; i < media.seasons.length; i++)
      movieSeasonsEpisodeCount[media.seasons[i].season_number] = media.seasons[i].episode_count

    async.each(media.seasons, (seasonInfo, callback) => {
      let season = seasonInfo.season_number
      if (!seasons[season])
        seasons[season] = []
      let episodes = seasons[season]
      if (movieSeasonsEpisodeCount[season] <= episodes.length)
        return callback()
      // Get new episodes
      let episodesAlreadySaved = {}
      for (let i = 0; i < seasons[season].length; i++)
        episodesAlreadySaved[seasons[season][i].episode] = seasons[season][i].id
      insertNewEpisodes(media.id, db_id, season, episodesAlreadySaved, (err, results) => {
        if (err)
          return callback()
        seasons[season] = results
        callback()
      })
    }, () => {
      if (Object.keys(seasons).length >= media.seasons.length)
        return next(seasons)
      // Add new seasons
      async.eachSeries(_.difference(Object.keys(seasons), media.seasons.map((season) => { return season.season_number })), (season, callback) => {
        insertNewEpisodes(media.id, db_id, season, {}, (err, results) => {
          if (err)
            return callback()
          seasons[season] = results
          callback()
        })
      }, () => {
        next(seasons)
      })
    })
  })
}

const insert = (result, next, season, episode, parent_id) => {
  result.poster_path = result.poster_path || ''
  console.log('Inserting ' + (result.name ? result.name : result.title) + (season ? ' S' + season + 'E' + episode + ' parent_id:' + parent_id : ''))
  db.query('INSERT INTO `movies` SET `parent_id` = ?, `title` = ?, media_id = ?, file = ?, magnet = ?, media_type = ?, poster_path = ?, backdrop_path = ?, vote_average = ?, date = ?, overview = ?, season = ?, episode = ?, created_at = ?', [
    parent_id,
    result.name || result.title,
    result.id,
    result.file,
    result.magnet,
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

module.exports = {

  get: (title, next) => {
    // GET IN DATABASE
    db.query('SELECT `id`, `media_id`, `title`, `file`, `downloaded`, `vote_average`, `media_type`, `poster_path`, `backdrop_path`, `date`, `overview` ' +
      'FROM `movies` ' +
      'WHERE `movies`.`title` = ? ' +
      'LIMIT 1', [title], (err, movie) => {
      if (err) {
        console.error(err)
        return next()
      }
      if (!movie || movie.length === 0)
        return next()
      movie = movie[0]
      movie.type = movie.downloaded ? path.extname(movie.file) : 'webm' // TODO: Not only webm (if torrent is mp4)

      // GET MORE INFOS
      if (movie.media_type === 'movie') {
        mdb.movieInfo({id: movie.media_id}, (err, media) => {
          if (err) {
            console.error(err)
            return next()
          }
          movie.created_by = media.created_by
          movie.in_production = media.in_production
          return next(movie)
        })
      } else {
        movie.seasons = {}
        mdb.tvInfo({id: movie.media_id}, (err, media) => {
          if (err) {
            console.error(err)
            return next()
          }
          movie.created_by = media.created_by
          movie.in_production = media.in_production

          getEpisodesFromSeasons(media, movie.id, (seasons) => {
            movie.seasons = seasons
            return next(movie)
          })
        })
      }
    })
  },

  insert: insert

}