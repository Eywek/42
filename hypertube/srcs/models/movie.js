const db = require('./database')
const config = require('../../config/config')
const mdb = require('moviedb')(config.movieDbAPIKey)
const path = require('path')
const async = require('async')
const _ = require('underscore')

const insertNewEpisodes = (media_id, db_id, season, episodesAlreadySaved, lang, callback) => {
  mdb.tvSeasonInfo({
    id: media_id,
    season_number: season,
    language: lang
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
        season: season,
        date: episode.air_date
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

const getEpisodesFromSeasons = (media, db_id, lang, next) => {
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
      insertNewEpisodes(media.id, db_id, season, episodesAlreadySaved, lang, (err, results) => {
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
        insertNewEpisodes(media.id, db_id, season, {}, lang, (err, results) => {
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
  db.query('INSERT INTO `movies` SET `parent_id` = ?, `title` = ?, media_id = ?, file = ?, media_type = ?, season = ?, episode = ?, created_at = ?', [
    parent_id,
    result.original_title || result.original_name || result.name || result.title,
    result.id,
    result.file,
    (result.media_type || 'tv'),
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

  get: (title, lang, next) => {
    // GET IN DATABASE
    db.query('SELECT `id`, `media_id`, `media_type` ' +
      'FROM `movies` ' +
      'WHERE `movies`.`title` = ? ' +
      'LIMIT 1', [title], (err, movie) => {
      if (err) {
        console.error(err)
        return next()
      }
      if (movie && movie.length > 0)
        return cb(movie[0])
      // Insert it
      mdb.searchMulti({query: title}, (err, movie) => {
        if (err) {
          console.error(err)
          return next()
        }
        if (!movie || !movie.results || movie.results.length === 0)
          return next()
        db.query('INSERT INTO `movies` SET `title` = ?, `media_id` = ?, `media_type` = ?, `created_at` = ?', [
          movie.results[0].original_title || movie.results[0].original_name,
          movie.results[0].id,
          movie.results[0].media_type,
          new Date()
        ], (err, insert) => {
          if (err) {
            console.error(err)
            return next()
          }
          cb({
            media_id: movie.results[0].id,
            media_type: movie.results[0].media_type,
            id: insert.insertId
          })
        })
      })
    })
    let cb = (movie) => {
      movie.type = 'webm'

      mdb[(movie.media_type === 'tv' ? 'tv' : 'movie') + 'Credits']({id: movie.media_id}, (err, credits) => {
        if (err)
          console.error(err)
        movie.credits = credits || {cast: [], crew: []}

        // GET MORE INFOS
        if (movie.media_type === 'movie') {
          mdb.movieInfo({id: movie.media_id, language: lang}, (err, media) => {
            if (err) {
              console.error(err)
              return next()
            }
            movie.time = media.runtime
            movie.original = media.original_title || media.original_name
            movie.title = media.title || media.name
            movie.overview = media.overview
            movie.created_by = media.created_by
            movie.in_production = media.in_production
            movie.poster_path = media.poster_path
            movie.backdrop_path = media.backdrop_path
            movie.vote_average = media.vote_average
            movie.date = media.release_date
            return next(movie)
          })
        } else {
          movie.seasons = {}
          mdb.tvInfo({id: movie.media_id, language: lang}, (err, media) => {
            if (err) {
              console.error(err)
              return next()
            }
            movie.time = media.episode_run_time[0]
            movie.original = media.original_title || media.original_name
            movie.title = media.title || media.name
            movie.overview = media.overview
            movie.created_by = media.created_by
            movie.in_production = media.in_production
            movie.poster_path = media.poster_path
            movie.backdrop_path = media.backdrop_path
            movie.vote_average = media.vote_average
            movie.date = media.first_air_date
            getEpisodesFromSeasons(media, movie.id, lang, (seasons) => {
              movie.seasons = seasons
              return next(movie)
            })
          })
        }
      })
    }
  },

  insert: insert

}
