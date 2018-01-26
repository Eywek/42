var db = require('../models/database');

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

           res.render('Chat/chat', {
               title: 'Messagerie',
               users: users.map(function (user) {
                   if (user.profile_pic)
                       user.profile_pic = '/uploads/pics/' + user.profile_pic;
                   else
                       user.profile_pic = '/assets/img/default_profile_pic.png';
                   return user;
               }),
               usersCanChat: users.map(function (user) {
                   return user.id;
               })
           });
        });
    }

};