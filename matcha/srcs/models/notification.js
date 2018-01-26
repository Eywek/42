var async = require('async');
var db = require('../models/database');

module.exports = {

    send: function (userId, notification, io, fromId, type) {
        async.parallel([
            function (cb) {
                // Add notification
                db.query('INSERT INTO `notifications` SET `user_id` = ?, `content` = ?, `created_at` = ?', [userId, notification, new Date()], function (err, result) {
                    if (err)
                        return cb(err);
                    cb(undefined, result);
                });
            },
            // Search socket id
            function (cb) {
                db.query('SELECT `socket_id` FROM `active_users` WHERE `user_id` = ?', [userId], function (err, data) {
                    if (err)
                        return cb(err);
                    cb(undefined, data);
                })
            },
            // Check if bloqued
            function (cb) {
                db.query('SELECT `id` FROM `users_blockeds` WHERE `user_id` = ? AND `blocker_id` = ?', [fromId, userId], function (err, result) {
                    if (err)
                        return cb(err);
                    cb(undefined, result);
                })
            }
        ], function (err, results) {
            if (err)
                console.error(err);
            if (err || !results[1] || results[1].length === 0)
                return;
            // blocked
            if (results[2] && results[2].length > 0)
                return;
            var id = results[0].insertId;

            io.to(results[1][0].socket_id).emit('new-notification', {
                id: id,
                content: notification,
                type: type
            });
        });
    },

    read: function (notificationId) {
        db.query('UPDATE `notifications` SET `seen` = 1 WHERE `id` = ?', [notificationId], function (err) {
            if (err)
                return console.error(err);
        })
    }

};