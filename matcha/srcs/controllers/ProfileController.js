var accountModel = require('../models/account');
var db = require('../models/database');
var validator = require('../models/validator');
var path = require('path');
var fs = require('fs');
var _ = require('underscore');

module.exports = {

    uploadPhoto: function (req, res) {
        if (!req.file)
            return res.json({status: false, error: 'Vous devez fournir une photo.'});
        // Add to database
        db.query('INSERT INTO `users_uploads` SET `user_id` = ?, `name` = ?, `created_at` = ?', [
            req.session.user,
            req.file.filename,
            new Date()
        ], function (err, result) {
           if (err) {
               console.error(err);
               return res.json({status: false, error: 'Une erreur interne est survenue.'});
           }

            res.json({status: true, success: 'Votre image a bien été sauvegardé !', data: {
                upload: {
                    id: result.insertId,
                    name: req.file.filename
                }
            }});
        });
    },

    deletePhoto: function (req, res) {
        db.query('SELECT `name` FROM `users_uploads` WHERE `user_id` = ? AND `id` = ?', [req.session.user, req.params.id], function (err, file) {
            if (err)
                console.error();
            db.query('DELETE FROM `users_uploads` WHERE `user_id` = ? AND `id` = ?', [req.session.user, req.params.id], function (err) {
                if (err)
                    console.error();
            });
            if (file)
                fs.unlinkSync(path.join(__dirname, '../../public/uploads/pics/', file[0].name))
        });
        res.send();
    },

    editPhoto: function (req, res) {
        db.query('UPDATE `users_uploads` SET `is_profile_pic` = 0 WHERE `user_id` = ?', [req.session.user, req.params.id], function (err) {
            if (err)
                console.error();
            db.query('UPDATE `users_uploads` SET `is_profile_pic` = 1 WHERE `user_id` = ? AND `id` = ?', [req.session.user, req.params.id], function (err) {
                if (err)
                    console.error();
            });
        });
        res.send();
    },

    updateBio: function (req, res) {
        var reqSql;
        // Check if form is filled
        validator(accountModel, req.body, function (err, status) {
            if (!status)
                return res.json({status: false, error: err});
            if (!req.body.tags.match(/^([A-Za-z0-9 \-_]+,?)+$/))
                return res.json({status: false, error: 'Vos tags sont invalides.'});

            // check if user as already save data
            db.query('SELECT `id` FROM `users_accounts` WHERE `user_id` = ? LIMIT 1', [req.session.user], function (err, rows) {
               if (err) {
                   console.error(err);
                   return res.json({status: false, error: 'Une erreur interne est survenue'});
               }

               var fields = '`biography` = ?, `gender` = ?, `sexual_orientation` = ?, `tags` = ?';
               if (rows && rows.length > 0)
                   reqSql = 'UPDATE ' + accountModel.table + ' SET ' + fields + ' WHERE `user_id` = ?';
               else
                   reqSql = 'INSERT INTO ' + accountModel.table + ' SET ' + fields + ', `user_id` = ?';

               // Save data
                db.query(reqSql, [
                    req.body.biography,
                    req.body.gender,
                    req.body.sexual_orientation,
                    req.body.tags,
                    req.session.user
                ], function (err, rows) {
                    if (err) {
                        console.error(err);
                        return res.json({status: false, error: 'Une erreur interne est survenue.'});
                    }

                    // Send success message
                    return res.json({status: true, success: 'Votre compte a bien été modifié.'});
                })
            });
        });
    },

    profile: function (req, res) {
        // Find user
        db.query('SELECT `users`.`id`, `users`.`username`, `users`.`name`, `users`.`created_at`, ' +
            '`users_accounts`.`biography`, `users_accounts`.`tags`, `users_accounts`.`gender`, `users_accounts`.`sexual_orientation`, ' +
            '`users_blockeds`.`id` AS `blocked` ' +
            'FROM `users` ' +
            'INNER JOIN `users_accounts` ON `users`.`id` = `users_accounts`.`user_id` ' +
            'LEFT JOIN `users_blockeds` ON `users_blockeds`.`blocker_id` = ? AND `users_blockeds`.`user_id` = `users`.`id` ' +
            'WHERE `users`.`username` = ?', [req.session.user, req.params.username], function (err, rows) {
            if (err) {
                console.error(err);
                return res.sendStatus(500);
            }
            if (!rows || rows.length === 0)
                return res.sendStatus(404);
            var user = rows[0];

            // Uploads
            db.query('SELECT `name`, `is_profile_pic` FROM `users_uploads` WHERE `user_id` = ?', [user.id], function (err, uploads) {
                if (err) {
                    console.error(err);
                    return res.sendStatus(500);
                }
                if (!uploads)
                    uploads = [];

                user.uploads = uploads;
                user.profile_pic = _.findWhere(user.uploads, {is_profile_pic: 1}) || '/assets/img/default_profile_pic.png';
                if (typeof user.profile_pic === 'object')
                    user.profile_pic = '/uploads/pics/' + user.profile_pic.name;

                // View
                res.render('Profile/profile', {user: user, title: user.username});
            });
        });
    },

    find: function (req, res) {

    },

    viewMatch: function (req, res) {

    },

    like: function (req, res) {

    },

    unlike: function (req, res) {

    },

    block: function (req, res) {
        var sql;
        db.query('SELECT `id` FROM `users` WHERE `username` = ?', [req.params.username], function (err, user) {
            if (err) {
                console.error(err);
                return res.sendStatus(500);
            }
            if (!user || user.length === 0)
                return res.sendStatus(404);

            db.query('SELECT `id` FROM `users_blockeds` WHERE `blocker_id` = ? AND `user_id` = ?', [req.session.user, user[0].id], function (err, rows) {
                if (err) {
                    console.error(err);
                    return res.sendStatus(500);
                }
                if (rows && rows.length > 0)
                    sql = 'DELETE FROM `users_blockeds` WHERE `blocker_id` = ? AND `user_id` = ?';
                else
                    sql = 'INSERT INTO `users_blockeds` SET `blocker_id` = ?, `user_id` = ?';

                db.query(sql, [req.session.user, user[0].id], function (err) {
                    if (err) {
                        console.error(err);
                        return res.sendStatus(500);
                    }

                    res.send();
                })
            })
        })
    },
    
    report: function (req, res) {
        db.query('INSERT INTO `users_reports` (`user_id`, `report_id`) ' +
            'SELECT `users`.`id` AS `user_id`, ? FROM `users` WHERE `users`.`username` = ? LIMIT 1', [req.session.user, req.params.username], function (err) {
            if (err)
                console.error(err);
        });
        res.send();
    }

};