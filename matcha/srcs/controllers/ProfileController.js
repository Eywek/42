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

               var fields = '`biography` = ?, `gender` = ?, `sexual_orientation` = ?, `tags` = ?, `age` = ?, `location` = ?';
               if (rows && rows.length > 0)
                   reqSql = 'UPDATE ' + accountModel.table + ' SET ' + fields + ' WHERE `user_id` = ?';
               else
                   reqSql = 'INSERT INTO ' + accountModel.table + ' SET ' + fields + ', `user_id` = ?';
               if (!req.body.location)
                   accountModel.getLocation(req.ip, function (err, location) {
                       if (err) {
                           console.error(err);
                           return res.json({status: false, error: 'Une erreur interne est survenue'});
                       }
                       next(location);
                   });
               else
                   next(req.body.location);

               function next(location) {
                   // Save data
                   db.query(reqSql, [
                       req.body.biography,
                       req.body.gender,
                       req.body.sexual_orientation,
                       req.body.tags,
                       parseInt(req.body.age),
                       location,
                       req.session.user
                   ], function (err, rows) {
                       if (err) {
                           console.error(err);
                           return res.json({status: false, error: 'Une erreur interne est survenue.'});
                       }

                       // Send success message
                       return res.json({status: true, success: 'Votre compte a bien été modifié.'});
                   })
               }
            });
        });
    },

    profile: function (req, res) {
        // Find user
        db.query('SELECT `users`.`id`, `users`.`username`, `users`.`name`, `users`.`last_login`, `users`.`created_at`, ' +
            '`users_accounts`.`biography`, `users_accounts`.`tags`, `users_accounts`.`gender`, `users_accounts`.`sexual_orientation`, `users_accounts`.`location`, ' +
            '`users_blockeds`.`id` AS `blocked`, ' +
            '`active_users`.`user_id` AS `active`, ' +
            '`likes`.`id` AS `liked`, ' +
            '`likes_from`.`id` AS `liked_you` ' +
            'FROM `users` ' +
            'INNER JOIN `users_accounts` ON `users`.`id` = `users_accounts`.`user_id` ' +
            'LEFT JOIN `users_blockeds` ON `users_blockeds`.`blocker_id` = ? AND `users_blockeds`.`user_id` = `users`.`id` ' +
            'LEFT JOIN `active_users` ON `active_users`.`user_id` = `users`.`id` ' +
            'LEFT JOIN `likes` ON `likes`.`liked_id` = `users`.`id` AND `likes`.`user_id` = ? ' +
            'LEFT JOIN `likes` AS `likes_from` ON `likes_from`.`liked_id` = ? AND `likes_from`.`user_id` = `users`.`id`' +
            'WHERE `users`.`username` = ?', [req.session.user, req.session.user, req.session.user, req.params.username], function (err, rows) {
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
                accountModel.computePopularity(user, function (err, popularity) {
                    if (err)
                        res.sendStatus(500);
                    user.popularity = popularity;
                    user.profile_pic = _.findWhere(user.uploads, {is_profile_pic: 1}) || '/assets/img/default_profile_pic.png';
                    if (typeof user.profile_pic === 'object')
                        user.profile_pic = '/uploads/pics/' + user.profile_pic.name;

                    // Get visitors if it's own account
                    if (req.session.user !== user.id) {
                        db.query('INSERT INTO `users_visits` SET `visited_id` = ?, `visitor_id` = ?', [user.id, req.session.user], function (err) {
                            if (err)
                                console.error(err);
                        });
                        return res.render('Profile/profile', {user: user, title: user.username});
                    }

                    db.query('SELECT `users`.`username`, `users_uploads`.`name` AS `profile_pic` ' +
                        'FROM `users_visits` ' +
                        'INNER JOIN `users` ON `users`.`id` = `users_visits`.`visitor_id` ' +
                        'LEFT JOIN `users_uploads` ON `users_uploads`.`user_id` = `users`.`id` AND `users_uploads`.`is_profile_pic` = 1 ' +
                        'WHERE `users_visits`.`visited_id` = ? ' +
                        'GROUP BY `users`.`id`' +
                        'ORDER BY `users_visits`.`id` DESC LIMIT 15', [user.id], function (err, visitors) {
                        if (err)
                            console.error(err);
                        if (!visitors)
                            visitors = [];
                        user.visitors = visitors.map(function (visitor) {
                            if (visitor.profile_pic)
                                visitor.profile_pic = '/uploads/pics/' + visitor.profile_pic;
                            else
                                visitor.profile_pic = '/assets/img/default_profile_pic.png';
                            return visitor;
                        });

                        return res.render('Profile/profile', {user: user, title: user.username});
                    })
                });
            });
        });
    },

    find: function (req, res) {
        var sqlPopularity = accountModel.sqlPopularity.replace('?', '`users`.`id`');
        var sql = 'SELECT `users`.`username`, `users`.`id`, ' +
            '`users_accounts`.`age`, `users_accounts`.`tags`, `users_accounts`.`location`, ' +
            '(' + sqlPopularity + ') AS `popularity`, ' +
            '`users_uploads`.`name` AS `profile_pic` ' +
            'FROM `users_accounts` ' +
            'INNER JOIN `users` ON `users`.`id` = `users_accounts`.`user_id` ' +
            'LEFT JOIN `users_uploads` ON `users_uploads`.`user_id` = `users`.`id` AND `users_uploads`.`is_profile_pic` = 1 ' +
            'LEFT JOIN `users_blockeds` ON `users_blockeds`.`user_id` = `users`.`id` OR `users_blockeds`.`blocker_id` = `users`.`id`' +
            'WHERE ';
        var values = [];

        if (req.body.age) {
            sql += '`users_accounts`.`age` >= ? AND `users_accounts`.`age` <= ? ';
            var age = req.body.age.split(',');
            if (age.length !== 2 || parseInt(age[0]) != age[0] || parseInt(age[1]) != age[1])
                return res.json({status: false, error: 'L\'âge est invalide.'});
            values.push(age[0], age[1]);
        }
        if (req.body.popularity) {
            sql += 'AND (' + sqlPopularity + ') >= ? AND (' + sqlPopularity + ') <= ? ';
            var popularity = req.body.popularity.split(',');
            if (popularity.length !== 2 || parseInt(popularity[0]) != popularity[0] || parseInt(popularity[1]) != popularity[1])
                return res.json({status: false, error: 'La popularité invalide.'});
            values.push(popularity[0], popularity[1]);
        }
        if (req.body.location) {
            sql += 'AND `users_accounts`.`location` LIKE ? ';
            values.push('%' + req.body.location + '%');
        }
        if (req.body.tags) {
            sql += 'AND `users_accounts`.`tags` LIKE ? ';
            if (!req.body.tags.match(/^([A-Za-z0-9 \-_]+,?)+$/))
                return res.json({status: false, error: 'Vos tags sont invalides.'});
            var tags = req.body.tags.split(',');
            values.push('%' + tags.join(',%') + '%');
        }
        sql += 'AND `users_blockeds`.`user_id` IS NULL ';
        sql += 'AND `users_accounts`.`user_id` != ?';
        values.push(req.session.user);

        db.query(sql, values, function (err, rows) {
           if (err) {
               console.error(err);
               return res.json({status: false, error: 'Une erreur est survenue'});
           }
           return res.json({status: true, success: rows.length + ' utilisateurs trouvés.', data: rows});
        });
    },

    viewMatch: function (req, res) {
        db.query('SELECT `users_accounts`.`sexual_orientation`, `users_accounts`.`gender`, `users_accounts`.`location`, `users_accounts`.`age`, `users_accounts`.`tags` ' +
            'FROM `users_accounts` ' +
            'WHERE `users_accounts`.`user_id` = ?', [req.session.user], function (err, user) {
            if (err) {
                console.error(err);
                return res.sendStatus(500);
            }
            if (!user || user.length === 0)
                return res.render('Profile/view-match', {title: 'Suggestions', users: [], user: false});
            user = user[0];
            var values = [];
            var where = '';

            // Sexe
            if (user.sexual_orientation === 'hetero' || user.sexual_orientation === 'homo') {
                where += '`users_accounts`.`gender` = ? AND (`users_accounts`.`sexual_orientation` = ? OR `users_accounts`.`sexual_orientation` = \'bi\')';
                if (user.sexual_orientation === 'hetero')
                    values.push(user.gender === 'men' ? 'women' : 'men');
                else
                    values.push(user.gender === 'men' ? 'men' : 'women');
                values.push(user.sexual_orientation);
            }

            // TODO: Not blocked

            // Not him
            where += ' AND `users_accounts`.`user_id` != ?';
            values.push(req.session.user);

            var sqlPopularity = accountModel.sqlPopularity.replace('?', '`users`.`id`');
            db.query('SELECT `users_accounts`.`tags`, `users_accounts`.`location`, `users_accounts`.`age`, ' +
               '(' + sqlPopularity + ') AS `popularity`, ' +
               '`users`.`username`, ' +
               '`users_uploads`.`name` AS `profile_pic` ' +
               'FROM `users_accounts` ' +
               'INNER JOIN `users` ON `users`.`id` = `users_accounts`.`user_id` ' +
               'LEFT JOIN `users_uploads` ON `users_uploads`.`user_id` = `users`.`id` AND `users_uploads`.`is_profile_pic` = 1 ' +
               'WHERE ' + where, values, function (err, users) {
                if (err) {
                    console.error(err);
                    return res.sendStatus(500);
                }

                // TODO: Match with location

                // TODO: Match with tags

                // TODO: Match with popularity

                res.render('Profile/view-match', {title: 'Suggestions', users: users.map(function (user) {
                    if (user.profile_pic)
                        user.profile_pic = '/uploads/pics/' + user.profile_pic;
                    else
                        user.profile_pic = '/assets/img/default_profile_pic.png';
                    return user;
                }), user: true});
            })
        });
    },

    like: function (req, res) { // TODO: Send notification to liked_id
        db.query('SELECT `id` FROM `users` WHERE `username` = ?', [req.params.username], function (err, user) {
           if (err) {
               console.error(err);
               return res.sendStatus(500);
           }
           if (!user || user.length === 0)
               return res.sendStatus(404);
            db.query('DELETE FROM `likes` WHERE `user_id` = ? AND `liked_id` = ?', [req.session.user, user[0].id], function (err, rows) {
                if (err) {
                    console.error(err);
                    return res.sendStatus(500);
                }
                // unlike
                if (rows.affectedRows > 0)
                    return res.send();
                // like
                db.query('INSERT INTO `likes` SET `user_id` = ?, `liked_id` = ?', [req.session.user, user[0].id], function (err) {
                    if (err) {
                        console.error(err);
                        return res.sendStatus(500);
                    }
                    res.send();
                })
            });
        });
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