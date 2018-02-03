const db = require('../models/database')
const userModel = require('../models/user')
const validator = require('../models/validator')
const mailer = require('nodemailer')
var mailTransport = mailer.createTransport({
  auth: {
    user: "postmaster@keymetrics.io",
    pass: "2hlw2f2x4wd2"
  },
  port: 465,
  host: "smtp.mailgun.org",
  secure: true
})
const pug = require('pug')
const path = require('path')
const fs = require('fs')
const async = require('async')
const config = require('../../config/config')
const mdb = require('moviedb')(config.movieDbAPIKey)
const getFullLanguage = (lang) => {
  let content
  if ((content = JSON.parse(fs.readFileSync(path.join(__dirname, '../../locales/languages.json')))[lang]))
    return content.name || lang
  return lang
}

module.exports = {

  signup: (req, res) => {
    // Check if form is filled
    validator(userModel, req.body, function (err, status) {
      if (!status)
        return res.json({status: false, error: err})
      // Check if password_confirmation === password
      if (req.body.password !== req.body.password_confirmation)
        return res.json({status: false, error: res.__("Password doesn't match")})
      // Check if username or email is not already used
      db.query('SELECT `username` FROM `users` WHERE `username` = ? OR `email` = ? LIMIT 1', [req.body.username, req.body.email], function (err, rows) {
        if (err) {
          console.error(err)
          return res.json({status: false, error: res.__('Internal error')})
        }
        if (rows && rows.length > 0)
          return res.json({
            status: false,
            error: res.__('Username or email already used.')
          })

        // Add user to database
        db.query('INSERT INTO `users` SET `name` = ?, `last_name` = ?, `username` = ?, `password` = ?, `email` = ?, `created_at` = ?', [
          req.body.name,
          req.body.last_name,
          req.body.username,
          userModel.hashPassword(req.body.password),
          req.body.email,
          new Date()
        ], function (err, rows) {
          if (err) {
            console.error(err)
            return res.json({status: false, error: res.__('Internal error')})
          }

          // Connect it
          userModel.login(req.body.username, req.body.password, function (err, userId) {
            if (err)
              return res.json({status: false, error: res.__('Internal error')})
            req.session.user = userId

            // Send success message
            res.json({status: true, success: res.__("You're now logged"), redirect: '/'})
          })
        })
      })
    }, ['name', 'last_name', 'username', 'email', 'password'], false, res.__)
  },

  signout: (req, res) => {
    // Log out
    req.session.user = undefined
    // Redirect
    res.redirect('/')
  },

  account: (req, res) => {
    // Get user infos
    userModel.get(req.session.user, function (err, user) {
      if (err) {
        console.error(err)
        return res.sendStatus(500)
      }

      user.avatar = fs.existsSync(path.join(__dirname, '../../public/uploads/' + user.id + '.png')) ? '/uploads/' + user.id + '.png' : '/assets/img/default_profile_pic.png'

      res.render('User/account', {user: user, title: res.__('My account')})
    })
  },

  editAccount: (req, res) => {
    // Check if form is filled
    validator(userModel, req.body, function (err, status) {
      if (!status)
        return res.json({status: false, error: err})

      // Save data
      db.query('UPDATE `users` SET `name` = ?, `last_name` = ?, `username` = ?, `email` = ?, `lang` = ? WHERE `id` = ?', [
        req.body.name,
        req.body.last_name,
        req.body.username,
        req.body.email,
        req.body.lang,
        req.session.user
      ], function (err, rows) {
        if (err) {
          console.error(err)
          return res.json({status: false, error: res.__('Internal error')})
        }

        // Send success message
        return res.json({status: true, success: res.__('Your account is now updated!')})
      })
    }, ['name', 'last_name', 'username', 'email'], [req.session.user], res.__)
  },

  editPassword: (req, res) => {
    // Check if form is filled
    validator(userModel, req.body, function (err, status) {
      if (!status)
        return res.json({status: false, error: err})

      // Check if password_confirmation === password
      if (req.body.password !== req.body.password_confirmation)
        return res.json({status: false, error: res.__("Password doesn't match")})

      // Save data
      db.query('UPDATE `users` SET `password` = ? WHERE `id` = ?', [userModel.hashPassword(req.body.password), req.session.user], function (err, rows) {
        if (err) {
          console.error(err)
          return res.json({status: false, error: res.__('Internal error')})
        }

        // Send success message
        return res.json({status: true, success: res.__("Your account is now updated!")})
      })
    }, ['password'], false, res.__)
  },

  lostPassword: (req, res) => {
    // Check if form is filled
    if (!req.body.email || req.body.email.length === 0)
      return res.json({status: false, error: res.__("Please, fill the form")})

    // Find user with this email
    db.query('SELECT `id`, `email`, `username` FROM `users` WHERE `email` = ? LIMIT 1', [req.body.email], function (err, user) {
      if (err) {
        console.error(err)
        return res.json({status: false, error: res.__('Internal error')})
      }
      if (!user || user.length === 0)
        return res.json({status: false, error: res.__("No users found with this email")})

      // Generate token
      let token = require('uuid/v4')()
      db.query('INSERT INTO `users_tokens` SET `type` = \'RESET_PW\', `token` = ?, `user_id` = ?, `created_at` = ?', [
        token,
        user[0].id,
        new Date()
      ], function (err, rows) {
        if (err) {
          console.error(err)
          return res.json({status: false, error: res.__('Internal error')})
        }

        // Send email
        let fullUrl = req.protocol + '://' + req.get('host') + '/account/reset-password/' + token
        let mailOptions = {
          from: 'Hypertube <no-reply@hypertube.com>',
          to: user[0].email,
          subject: 'Rénitialisation de mot de passe',
          html: pug.renderFile(path.join(__dirname, '../../views/Emails/reset_password.pug'), {
            username: user[0].username,
            ip: req.ip,
            date: new Date(),
            url: fullUrl,
            __: res.__
          })
        };

        // send mail with defined transport object
        mailTransport.sendMail(mailOptions, (err) => {
          if (err) {
            console.error(err)
            return res.json({status: false, error: res.__("Internal error on email send.")})
          }

          // Send success message
          res.json({status: true, success: res.__("Reset email has been sent!")})
        });
      })
    })
  },

  resetPassword: (req, res) => {
    // Check if token is valid
    db.query('SELECT `users_tokens`.`id`, `user_id`, `name`, `users`.`username` FROM `users_tokens` INNER JOIN `users` ON `users`.`id` = `users_tokens`.`user_id` WHERE `token` = ? AND type = \'RESET_PW\' AND `used_at` IS NULL LIMIT 1', [req.params.token], function (err, rows) {
      if (err) {
        console.error(err)
        return res.json({status: false, error: res.__('Internal error')})
      }
      if (!rows || rows.length === 0)
        return res.sendStatus(404)

      // Render if GET
      if (req.method === 'GET')
        return res.render('User/reset_password', {title: res.__('Reset your password'), name: rows[0].name})

      // Check if form is filled
      validator(userModel, req.body, function (err, status) {
        if (!status)
          return res.json({status: false, error: err})

        // Check if password_confirmation === password
        if (req.body.password !== req.body.password_confirmation)
          return res.json({status: false, error: res.__('Password doesn\'t match')})

        // Edit data
        db.query('UPDATE `users` SET `password` = ? WHERE `id` = ?', [userModel.hashPassword(req.body.password), rows[0].user_id], function (err, user) {
          if (err) {
            console.error(err)
            return res.json({status: false, error: res.__('Internal error')})
          }

          // Set token as used
          db.query('UPDATE `users_tokens` SET `used_at` = ? WHERE `id` = ?', [new Date(), rows[0].id], function (err, token) {
            if (err) {
              console.error(err)
              return res.json({status: false, error: res.__('Internal error')})
            }

            // Connect it
            userModel.login(rows[0].username, req.body.password, function (err, userId) {
              if (err)
                return res.json({status: false, error: res.__('Internal error')})
              req.session.user = userId

              // Send success message
              res.json({status: true, success: res.__('Your password is updated!'), redirect: '/'})
            })
          })
        })
      }, ['password'], false, res.__)
    })
  },

  uploadAvatar: (req, res) => {
    if (!req.file)
      return res.json({status: false, error: res.__('You need to send a image (png)')})
    res.json({status: true, success: res.__('Your avatar is now saved!')})
  },

  profile: (req, res) => {
    db.query('SELECT `users`.`id`, `users`.`name`, `users`.`last_name`, `users`.`username`, `users`.`lang` ' +
      'FROM `users` ' +
      'WHERE `users`.`username` = ?', [req.params.username], (err, rows) => {
      if (err) {
        console.error(err)
        return res.sendStatus(500)
      }
      if (!rows || rows.length === 0)
        return res.sendStatus(404)
      let user = rows[0]
      // Get movies
      db.query('SELECT `movies`.`title`, `parent`.`title` AS `parent_title`, `movies`.`media_type`, `movies`.`media_id`, `parent`.`media_id` AS `parent_media_id` ' +
        'FROM `views` ' +
        'INNER JOIN `movies` ON `movies`.`id` = `views`.`movie_id` ' +
        'LEFT JOIN `movies` AS `parent` ON `parent`.`id` = `movies`.`parent_id` ' +
        'WHERE `views`.`user_id` = ? ' +
        'GROUP BY `movies`.`id`' +
        'ORDER BY `views`.`id` DESC', [user.id], (err, rows) => {
        let movies = []
        if (err)
          console.error(err)
        if (rows && rows.length > 0)
          movies = rows
        user.lang = getFullLanguage(user.lang)
        user.movies = movies
        user.profile_pic = fs.existsSync(path.join(__dirname, '../../public/uploads/' + user.id + '.png')) ? '/uploads/' + user.id + '.png' : '/assets/img/default_profile_pic.png'
        async.eachOf(user.movies, (movie, key, cb) => {
          let method = (movie.media_type === 'tv') ? 'tvInfo' : 'movieInfo'
          mdb[method]({id: (movie.parent_media_id ? movie.parent_media_id : movie.media_id)}, (err, infos) => {
            if (err)
              console.error(err)
            user.movies[key].poster_path = infos.poster_path
            cb()
          })
        }, () => {
          res.render('User/profile', {title: user.username, user:user})
        })
      })
    })
  }

}
