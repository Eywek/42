var db = require('./database');
var request = require('request');
var async = require('async');

module.exports = {

    table: 'users_accounts',

    fields: {
        'biography': 'required:max=500',
        'gender': 'required:in=men,women',
        'sexual_orientation': 'required:in=hetero,homo,bi',
        'tags': 'required:max=500',
        'age': 'required:number:between=18,90'
    },

    sqlPopularity: "SELECT ? AS `popularity`",

    computePopularity: function (user, next) {
        db.query(this.sqlPopularity, [user.id], function (err, result) {
            if (err) {
                console.error(err);
                return next(err)
            }
            if (!result)
                return next(undefined, 0);
            return next(undefined, result[0].popularity);
        });
    },

    getLocation: function (ip, next) {
        ip = '92.147.244.173';
        if (ip === '::1' || ip === '127.0.0.1')
            return next(undefined, '17e Arrondissement, Paris, France');
        async.parallel([

            function (cb) {
                request("https://ipinfo.io/" + ip + "/json", function (err, response, body) {
                    if (err)
                        return cb(err);
                    cb(undefined, JSON.parse(body));
                });
            },

            function (cb) {
                request("http://country.io/names.json", function (err, response, body) {
                    if (err)
                        return cb(err);
                    cb(undefined, JSON.parse(body));
                });
            }

        ], function (err, results) {
            if (err)
                return next(err);
            var location = results[0];
            var countries = results[1];

            next(undefined, location.city + ', ' + location.region + ', ' + (countries[location.country] || location.country));
        });
    }
};