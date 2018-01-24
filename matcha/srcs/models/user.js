var db = require('../models/database');
var crypto = require('crypto');

module.exports = {

    table: 'users',

    fields: {
        'username': 'required:alpha_num:unique:min=3:max=20',
        'email': 'required:email:unique',
        'password': 'required:password'
    },

    login: function (username, password, next) {
        db.query('SELECT `id` FROM `users` WHERE `username` = ? AND `password` = ? LIMIT 1', [username, this.hashPassword(password)], function (err, rows) {
            if (err) {
                console.error(err);
                return next('Une erreur interne est survenue.')
            }

            if (!rows || rows.length === 0)
                return next("Vos identifiants sont invalides.");
            return next(undefined, rows[0].id);
        });
    },

    hashPassword: function (password) {
        var hash = crypto.createHmac('sha512', 'ME9deB97KD5gMgfY9h54ZmtPwg9L73');
        hash.update(password);
        return hash.digest('hex');
    },

    get: function (userId, next) {
      db.query('SELECT * FROM `users` WHERE user_id = ?', [userId], function (err, rows) {
          if (err)
              return next(err);
          if (!rows || rows.length === 0)
              return next(new Error('Utilisateur non trouvé.'));
          return next(undefined, rows[0]);
      })
    }
};