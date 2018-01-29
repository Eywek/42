var mysql = require('mysql');
var config = require('../../config/config');
var connection = mysql.createConnection({
    host     : config.database.host,
    user     : config.database.user,
    password : config.database.password,
    database : config.database.dbname
});

connection.connect(function(err) {
    if (err) {
        console.error('MYSQL ERROR ON CONNECT:\n ' + err.stack);
        return;
    }

    console.log('MYSQL CONNECTION ESTABLISHED ' + connection.threadId);
});

module.exports = connection;