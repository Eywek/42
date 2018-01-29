const db = require('../models/database')
const userModel = require('../models/user')
const validator = require('../models/validator')
const sendmail = require('sendmail')()
const pug = require('pug')
const path = require('path')
const fs = require('fs')

module.exports = {

  signin: function (req, res) {
    // Check if form is filled
    if (!req.body.username || req.body.username.length === 0 || !req.body.password || req.body.password.length === 0)
      return res.json({status: false, error: res.__("Please, fill the form")})

    // Find user with this username and password
    userModel.login(req.body.username, req.body.password, function (err, userId) {
      if (err)
        return res.json({status: false, error: res.__(err)})

      // Connect it
      req.session.user = userId
      // Send success message
      res.json({status: true, success: res.__("You're now logged"), redirect: '/'})
    })
  },

  signup: function (req, res) {
    // Check if form is filled
    validator(userModel, req.body, function (err, status) {
      if (!status)
        return res.json({status: false, error: res.__(err)})
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
    })
  },

  signout: function (req, res) {
    // Log out
    req.session.user = undefined
    // Redirect
    res.redirect('/')
  },

  account: function (req, res) {
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

  editAccount: function (req, res) {
    // Check if form is filled
    validator(userModel, req.body, function (err, status) {
      if (!status)
        return res.json({status: false, error: res.__(err)})

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
    }, ['name', 'last_name', 'username', 'email'], [req.session.user])
  },

  editPassword: function (req, res) {
    // Check if form is filled
    validator(userModel, req.body, function (err, status) {
      if (!status)
        return res.json({status: false, error: res.__(err)})

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
    }, ['password'])
  },

  lostPassword: function (req, res) {
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
        sendmail({
          from: 'no-reply@matcha.com',
          to: user[0].email,
          subject: 'Rénitialisation de mot de passe',
          html: pug.renderFile(path.join(__dirname, '../views/Emails/reset_password.pug'), {
            username: user[0].username,
            ip: req.ip,
            date: new Date(),
            url: '/account/reset-password/' + token
          })
        }, function (err, reply) {
          if (err) {
            console.error(err)
            return/* res.json({status: false, error: res.__("Internal error on email send.")})*/
          }

          // Send success message
          res.json({status: true, success: res.__("Reset email has been sent!")})
        })
      })
    })
  },

  resetPassword: function (req, res) {
    // Check if token is valid
    db.query('SELECT `users_tokens`.`id`, `user_id`, `name` FROM `users_tokens` INNER JOIN `users` ON `users`.`id` = `users_tokens`.`user_id` WHERE `token` = ? AND type = \'RESET_PW\' AND `used_at` IS NULL LIMIT 1', [req.params.token], function (err, rows) {
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
          return res.json({status: false, error: res.__(err)})

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
      }, ['password'])
    })
  },

  uploadAvatar: function (req, res) {
    if (!req.file)
      return res.json({status: false, error: res.__('You need to send a image')})
    res.json({status: true, success: res.__('Your avatar is now saved!')})
  }

}
