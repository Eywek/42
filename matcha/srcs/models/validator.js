var db = require('./database');
var async = require('async');

module.exports = function (model, data, next, requireds, uniqueBypassIds) {
    var value;

    async.eachOfSeries(model.fields, function (types, name, callback) {
        if (requireds !== undefined && requireds.indexOf(name) === -1)
            return callback();

        types = types.split(':');
        async.eachSeries(types, function (type, cb) {
            if (type.indexOf('=') !== -1) {
                type = type.split('=');
                value = type[1];
                type = type[0];
            }

            switch (type) {
                case 'required':
                    if (data[name] === undefined || data[name].length === 0)
                        return cb("Le champ " + name + " ne peut pas être vide.");
                    cb();
                    break;
                case 'unique':
                    db.query('SELECT `id` FROM `' + model.table + '` WHERE `' + name + '` = ? ' + (uniqueBypassIds ? 'AND `id` NOT IN (' + uniqueBypassIds.join(',') + ')' : ''), data[name], function (err, rows) {
                       if (err) {
                           console.error(err);
                           return cb(err);
                       }
                       if (rows && rows.length > 0)
                           return cb("La valeur du champ " + name + " est déjà utilisée.");
                       cb();
                    });
                    break;
                case 'email':
                    if (!data[name].match(/^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/))
                        return cb("Le champ " + name + " doit être un email valide.");
                    cb();
                    break;
                case 'password':
                    if (data[name].length < 8)
                        return cb("Le champ " + name + " doit avoir un minimum de 8 caractères.");
                    else if (!data[name].match(/[0-9]/))
                        return cb("Le champ " + name + " doit contenir au minimum un chiffre.");
                    else if (!data[name].match(/[A-Z]/))
                        return cb("Le champ " + name + " doit contenir au minimum une lettre majuscule.");
                    else if (!data[name].match(/[a-z]/))
                        return cb("Le champ " + name + " doit contenir au minimum une lettre minuscule.");
                    cb();
                    break;
                case 'min':
                    if (data[name].length < value)
                        return cb("Le champ " + name + " doit avoir un minimum de " + value + " caractères.");
                    cb();
                    break;
                case 'max':
                    if (data[name].length > value)
                        return cb("Le champ " + name + " doit avoir un maximum de " + value + " caractères.");
                    cb();
                    break;
                case 'alpha_num':
                    if (!data[name].match(/^[0-9a-zA-Z]+$/))
                        return cb("Le champ " + name + " doit être uniquement alphanumérique.");
                    cb();
                    break;
                case 'alpha':
                    if (!data[name].match(/^[a-zA-Z ]+$/))
                        return cb("Le champ " + name + " doit être uniquement alphabétique.");
                    cb();
                    break;
                case 'in':
                    var values = value.split(',');
                    if (values.indexOf(data[name]) === -1)
                        return cb("Le champ " + name + " doit uniquement avoir une des valeurs suivantes: " + value + ".");
                    cb();
                    break;
                case 'number':
                    if (!data[name].match(/^[0-9]+$/))
                        return cb("Le champ " + name + " doit être un nombre valide.");
                    cb();
                    break;
                case 'between':
                    var values = value.split(',');
                    if (parseInt(data[name]) < parseInt(values[0]) || parseInt(data[name]) > parseInt(values[1]))
                        return cb("Le champ " + name + " doit être compris entre " + values[0] + " et " + values[1] + ".");
                    cb();
                    break;
            }
        }, function (err) {
            if (err)
                return next(err, false);
            return callback();
        })
    }, function () {
        next(undefined, true);
    });
};