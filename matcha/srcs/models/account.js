var db = require('./database');
var https = require('https');

module.exports = {

    table: 'users_accounts',

    fields: {
        'biography': 'required:max=500',
        'gender': 'required:in=men,women,other',
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
        if (ip === '::1' || ip === '127.0.0.1')
            return next(undefined, '17e Arrondissement, Paris, France');
        https.get("https://ipinfo.io/" + ip + "/json", function(res) {
            var bodyChunks = [];
            res.on('data', function(chunk) {
                bodyChunks.push(chunk);
            }).on('end', function() {
                var data = JSON.parse(Buffer.concat(bodyChunks));
                next(undefined, data.city + ', ' + data.region + ', ' + data.country);
            }).on('error', function (err) {
                next(err);
            })
        });
    }
};