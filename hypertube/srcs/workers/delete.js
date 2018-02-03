const cron = require('node-cron')
const db = require('../models/database')
const async = require('async')
const fs = require('fs')
const path = require('path')

module.exports = cron.schedule('* * * * *', () => {
  db.query('SELECT `movies`.`file`, `movies`.`id` ' +
    'FROM `views` ' +
    'INNER JOIN `movies` ON `movies`.`id` = `views`.`movie_id` AND `movies`.`downloaded` = 1 ' +
    'WHERE `views`.`created_at` < DATE_SUB(NOW(), INTERVAL 1 MONTH) ' +
    'GROUP BY `views`.`movie_id` ' +
    'ORDER BY `views`.`id` DESC', (err, moviesToDelete) => {
    if (err)
      return console.error(err)
    if (!moviesToDelete || moviesToDelete.length === 0)
      return true

    async.each(moviesToDelete, (movie, next) => {
      db.query('UPDATE `movies` SET `downloaded` = 0, `file` = NULL WHERE `id` = ?', [movie.id], () => {})
      if (movie.file)
        fs.unlinkSync(path.join(__dirname, '../../files/' + movie.file))
      next()
    }, () => {})
  })
}, false)