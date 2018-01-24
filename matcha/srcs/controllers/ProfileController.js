var accountModel = require('../models/account');
var db = require('../models/database');
var validator = require('../models/validator');

module.exports = {

    uploadPhoto: function (req, res) {
        if (!req.file)
            return res.json({status: false, error: 'Vous devez fournir une photo.'});
        // Add to database
        db.query('INSERT INTO `users_uploads` SET `user_id` = ?, `uid` = ?, `created_at` = ?', [
            req.session.user,
            req.file.filename.split('.')[0],
            new Date()
        ], function (err, rows) {
           if (err) {
               console.error(err);
               return res.json({status: false, error: 'Une erreur interne est survenue.'});
           }

            res.json({status: true, success: 'Votre image a bien été sauvegardé !'});
        });
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
        
    },
    
    report: function (res, res) {
        
    }

};