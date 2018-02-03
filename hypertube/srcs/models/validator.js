let db = require('./database');
let async = require('async');

module.exports = function (model, data, next, requireds, uniqueBypassIds, i18n) {
    let value;

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
                        return cb(i18n("The field %s cannot be null.", name));
                    cb();
                    break;
                case 'unique':
                    db.query('SELECT `id` FROM `' + model.table + '` WHERE `' + name + '` = ? ' + (uniqueBypassIds ? 'AND `id` NOT IN (' + uniqueBypassIds.join(',') + ')' : ''), data[name], function (err, rows) {
                       if (err) {
                           console.error(err);
                           return cb(err);
                       }
                       if (rows && rows.length > 0)
                           return cb(i18n('The value of the field %s is already used.', name));
                       cb();
                    });
                    break;
                case 'email':
                    if (!data[name].match(/^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/))
                        return cb(i18n('The field %s need to be a valid email.', name));
                    cb();
                    break;
                case 'password':
                    if (data[name].length < 8)
                        return cb(i18n('The field %s need to contains at least %s characters.', name, 8));
                    else if (!data[name].match(/[0-9]/))
                        return cb(i18n('The field %s need to contains at least one number.', name));
                    else if (!data[name].match(/[A-Z]/))
                        return cb(i18n('The field %s need to contains at least one upper letter.', name));
                    else if (!data[name].match(/[a-z]/))
                        return cb(i18n('The field %s need to contains at least one lower letter.', name));
                    cb();
                    break;
                case 'min':
                    if (data[name].length < value)
                        return cb(i18n('The field %s need to contains at least %s characters.', name, value));
                    cb();
                    break;
                case 'max':
                    if (data[name].length > value)
                        return cb(i18n('The field %s need to contains %s characters max.', name, value));
                    cb();
                    break;
                case 'alpha_num':
                    if (!data[name].match(/^[0-9a-zA-Z]+$/))
                        return cb(i18n('The field %s need to contains only alphanumerics characters.', name));
                    cb();
                    break;
                case 'alpha':
                    if (!data[name].match(/^[a-zA-Z ]+$/))
                        return cb(i18n('The field %s need to contains only alpha characters.', name));
                    cb();
                    break;
                case 'in':
                    if (value.split(',').indexOf(data[name]) === -1)
                        return cb(i18n('The field %s need to contains only this values: %s.', name, value));
                    cb();
                    break;
                case 'number':
                    if (!data[name].match(/^[0-9]+$/))
                        return cb(i18n('The field %s need to be a valid number.', name));
                    cb();
                    break;
                case 'between':
                    let values = value.split(',');
                    if (parseInt(data[name]) < parseInt(values[0]) || parseInt(data[name]) > parseInt(values[1]))
                        return cb(i18n('The field %s need to be between %s and %s.', name, values[0], values[1]));
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