var db = require('../models/database');
var _ = require('underscore');

module.exports = {

    chat: function (req, res) {

    },

    index: function (req, res) {
        db.query('SELECT `users`.`username`, `users`.`name`, `users`.`id`, ' +
            '`users_uploads`.`name` AS `profile_pic`, ' +
            '`active_users`.`user_id` AS `active` ' +
            'FROM `likes` ' +
            'INNER JOIN `users` ON `users`.`id` = `likes`.`liked_id` ' +
            'LEFT JOIN `users_uploads` ON `users_uploads`.`user_id` = `users`.`id` AND `users_uploads`.`is_profile_pic` = 1 ' +
            'LEFT JOIN `active_users` ON `active_users`.`user_id` = `users`.`id` ' +
            'INNER JOIN `likes` AS `matchs` ON `matchs`.`liked_id` = `likes`.`user_id` ' +
            'WHERE `likes`.`user_id` = ? AND `matchs`.`user_id` = `likes`.`liked_id`',
        [req.session.user], function (err, users) {
            if (err) {
                console.error(err);
                return res.sendStatus(500);
            }

            // Get messages
            db.query('SELECT `conversations`.`message`, `conversations`.`to_id`, `conversations`.`from_id` ' +
                'FROM `conversations` ' +
                'WHERE `conversations`.`to_id` = ? OR `conversations`.`from_id` = ?', [req.session.user, req.session.user], function (err, conversations) {
                if (err) {
                    console.error(err);
                    return res.sendStatus(500);
                }
                // Group
                conversations = _.groupBy(conversations, function (message) {
                    if (message.to_id === req.session.user)
                        return message.from_id;
                    return message.to_id;
                });
                // Add missing conversations
                for (var i = 0; i < users.length; i++) {
                    if (!conversations[users[i].id])
                        conversations[users[i].id] = [];
                }
                // Fix profile pic
                users = users.map(function (user) {
                    if (user.profile_pic)
                        user.profile_pic = '/uploads/pics/' + user.profile_pic;
                    else
                        user.profile_pic = '/assets/img/default_profile_pic.png';
                    return user;
                });
                // Users by id
                var usersById = {};
                for (i = 0; i < users.length; i++)
                    usersById[users[i].id] = users[i];
                // Remove conversations without not matched users
                for (key in conversations) {
                    if (usersById[key] === undefined)
                        delete conversations[key];
                }

                // TODO: Sort conversations by last messages

                res.render('Chat/chat', {
                    title: 'Messagerie',
                    usersById: usersById,
                    conversations: conversations
                });
            });
        });
    }

};