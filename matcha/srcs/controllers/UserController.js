var db = require('../models/database');
var userModel = require('../models/user');
var validator = require('../models/validator');
var sendmail = require('sendmail')();
var pug = require('pug');
var path = require('path');

module.exports = {

    signin: function (req, res) {
        // Check if form is filled
        if (!req.body.username || req.body.username.length === 0 || !req.body.password || req.body.password.length === 0)
            return res.json({status: false, error: 'Veuillez remplir tous les champs.'});

        // Find user with this username and password
        userModel.login(req.body.username, req.body.password, function (err, userId) {
            if (err)
                return res.json({status: false, error: err});

            // Connect it
            req.session.user = userId;
            // Send success message
            res.json({status: true, success: 'Vous vous êtes bien connecté !', redirect: '/'})
        })
    },

    signup: function (req, res) {
        // Check if form is filled
        validator(userModel, req.body, function (err, status) {
            if (!status)
                return res.json({status: false, error: err});
            // Check if password_confirmation === password
            if (req.body.password !== req.body.password_confirmation)
                return res.json({status: false, error: 'Les mot de passes ne correspondent pas.'});
            // Check if username or email is not already used
            db.query('SELECT `username` FROM `users` WHERE `username` = ? OR `email` = ? LIMIT 1', [req.body.username, req.body.email], function (err, rows) {
                if (err) {
                    console.error(err);
                    return res.json({status: false, error: 'Une erreur interne est survenue.'});
                }
                if (rows && rows.length > 0)
                    return res.json({status: false, error: 'Ce' + (rows[0].username === req.body.username ? ' pseudo' : 't email') + ' est déjà utilisé.'});

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
                        console.error(err);
                        return res.json({status: false, error: 'Une erreur interne est survenue.'});
                    }

                    // Connect it
                    userModel.login(req.body.username, req.body.password, function (err, userId) {
                        if (err)
                            return res.json({status: false, error: 'Une erreur interne est survenue lors de la connexion'});
                        req.session.user = userId;

                        // Send success message
                        res.json({status: true, success: 'Vous vous êtes bien inscris !', redirect: '/'});
                    })
                })
            })
        })
    },

    signout: function (req, res) {
        // Log out
        req.session.user = undefined;
        // Redirect
        res.redirect('/');
    },

    account: function (req, res) {
        // Get user infos
        userModel.get(req.session.user, function (err, user) {
            if (err) {
                console.error(err);
                return res.sendStatus(500);
            }

            // Get bio
            db.query('SELECT `biography`, `tags`, `gender`, `sexual_orientation`, `age`, `location` FROM `users_accounts` WHERE `user_id` = ?', [user.id], function (err, account) {
                if (err) {
                    console.error(err);
                    return res.sendStatus(500);
                }
                if (!account || account.length === 0)
                    account = {
                        biography: '',
                        tags: '',
                        gender: '',
                        sexual_orientation: '',
                        age: '',
                        location: ''
                    };
                else
                    account = account[0];

                // Get photos
                db.query('SELECT `id`, `name`, `is_profile_pic` FROM `users_uploads` WHERE `user_id` = ?', [user.id], function (err, photos) {
                    if (err) {
                        console.error(err);
                        return res.sendStatus(500);
                    }

                    res.render('User/account', {user: user, account: account, title: 'Mon compte', photos: photos || []});
                });
            });
        })
    },

    editAccount: function (req, res) {
        // Check if form is filled
        validator(userModel, req.body, function (err, status) {
            if (!status)
                return res.json({status: false, error: err});

            // Save data
            db.query('UPDATE `users` SET `name` = ?, `last_name` = ?, `username` = ?, `email` = ? WHERE `id` = ?', [
                req.body.name,
                req.body.last_name,
                req.body.username,
                req.body.email,
                req.session.user
            ], function (err, rows) {
                if (err) {
                    console.error(err);
                    return res.json({status: false, error: 'Une erreur interne est survenue.'});
                }

                // Send success message
                return res.json({status: true, success: 'Votre compte a bien été modifié.'});
            })
        }, ['name', 'last_name', 'username', 'email'], [req.session.user]);
    },

    editPassword: function (req, res) {
        // Check if form is filled
        validator(userModel, req.body, function (err, status) {
            if (!status)
                return res.json({status: false, error: err});

            // Check if password_confirmation === password
            if (req.body.password !== req.body.password_confirmation)
                return res.json({status: false, error: 'Les mot de passes ne correspondent pas.'});

            // Save data
            db.query('UPDATE `users` SET `password` = ? WHERE `id` = ?', [userModel.hashPassword(req.body.password), req.session.user], function (err, rows) {
                if (err) {
                    console.error(err);
                    return res.json({status: false, error: 'Une erreur interne est survenue.'});
                }

                // Send success message
                return res.json({status: true, success: 'Votre compte a bien été modifié.'});
            })
        }, ['password']);
    },

    lostPassword: function (req, res) {
        // Check if form is filled
        if (!req.body.email || req.body.email.length === 0)
            return res.json({status: false, error: 'Veuillez remplir tous les champs.'});

        // Find user with this email
        db.query('SELECT `id`, `email`, `username` FROM `users` WHERE `email` = ? LIMIT 1', [req.body.email], function (err, user) {
            if (err) {
                console.error(err);
                return res.json({status: false, error: 'Une erreur interne est survenue.'});
            }
            if (!user || user.length === 0)
                return res.json({status: false, error: 'Aucun utilisateur avec cet email n\'a été trouvé.'});

            // Generate token
            var token = require('uuid/v4')();
            db.query("INSERT INTO `users_tokens` SET `type` = 'RESET_PW', `token` = ?, `user_id` = ?, `created_at` = ?", [
                token,
                user[0].id,
                new Date()
            ], function (err, rows) {
                if (err) {
                    console.error(err);
                    return res.json({status: false, error: 'Une erreur interne est survenue.'});
                }

                var fullUrl = req.protocol + '://' + req.get('host') + '/account/reset-password/' + token;
                // Send email
                sendmail({
                    from: 'no-reply@matcha.com',
                    to: user[0].email,
                    subject: 'Rénitialisation de mot de passe',
                    html: pug.renderFile(path.join(__dirname, '../views/Emails/reset_password.pug'), {
                        username: user[0].username,
                        ip: req.ip,
                        date: new Date(),
                        url: fullUrl
                    })
                }, function(err, reply) {
                    if (err) {
                        console.error(err);
                        return res.json({status: false, error: 'Une erreur interne est survenue lors de l\'envoie de l\'email.'})
                    }

                    // Send success message
                    res.json({status: true, success: 'Un email de rénitialisation vous a été envoyé !'});
                });
            })
        })
    },

    resetPassword: function (req, res) {
        // Check if token is valid
        db.query("SELECT `users_tokens`.`id`, `user_id`, `name`, `username` FROM `users_tokens` INNER JOIN `users` ON `users`.`id` = `users_tokens`.`user_id` WHERE `token` = ? AND type = 'RESET_PW' AND `used_at` IS NULL LIMIT 1", [req.params.token], function (err, rows) {
            if (err) {
                console.error(err);
                return res.json({status: false, error: 'Une erreur interne est survenue.'});
            }
            if (!rows || rows.length === 0)
                return res.sendStatus(404);

            // Render if GET
            if (req.method === 'GET')
                return res.render('User/reset_password', {title: 'Rénitialisation de mot de passe', name: rows[0].name});

            // Check if form is filled
            validator(userModel, req.body, function (err, status) {
                if (!status)
                    return res.json({status: false, error: err});

                // Check if password_confirmation === password
                if (req.body.password !== req.body.password_confirmation)
                    return res.json({status: false, error: 'Les mot de passes ne correspondent pas.'});

                // Edit data
                db.query('UPDATE `users` SET `password` = ? WHERE `id` = ?', [userModel.hashPassword(req.body.password), rows[0].user_id], function (err, user) {
                    if (err) {
                        console.error(err);
                        return res.json({status: false, error: 'Une erreur interne est survenue.'});
                    }

                    // Set token as used
                    db.query('UPDATE `users_tokens` SET `used_at` = ? WHERE `id` = ?', [new Date(), rows[0].id], function (err, token) {
                        if (err) {
                            console.error(err);
                            return res.json({status: false, error: 'Une erreur interne est survenue.'});
                        }

                        // Connect it
                        userModel.login(rows[0].username, req.body.password, function (err, userId) {
                            if (err)
                                return res.json({status: false, error: 'Une erreur interne est survenue lors de la connexion'});
                            req.session.user = userId;

                            // Send success message
                            res.json({status: true, success: 'Vous avez bien rénitialisé votre mot de passe !', redirect: '/'});
                        })
                    })
                })
            }, ['password']);
        })
    },

};