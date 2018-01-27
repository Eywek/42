/*
    SETUP
 */
var express = require('express');
var bodyParser = require('body-parser');
var session = require('express-session');
var config = require('../config/config');
var path = require('path');
var multer  = require('multer');
var moment = require('moment');
moment.locale('fr');
var app = express();
var server = require('http').Server(app);
var io = require('socket.io')(server);
var db = require('./models/database');

app.set('view engine', 'pug');
app.set('views', path.join(__dirname, 'views'));
app.use(express.static(path.join(__dirname, '../', 'public')));
app.use(bodyParser.json()); // for parsing application/json
app.use(bodyParser.urlencoded({ extended: true })); // for parsing application/x-www-form-urlencoded
app.set('trust proxy', 1);
app.use(session({
    secret: 'wMnGuvBetLR27y48Y5y36fN8NM49Vp',
    resave: true,
    saveUninitialized: true,
    cookie: { secure: false }
}));
app.use(function (req, res, next) {
   res.locals.isLogged = (req.session.user !== undefined);
   res.locals.userId = req.session.user;
   res.locals.moment = moment;
   res.locals.googleApiKey = config.googleApiKey;
   res.locals.notifications = [];
    if (!res.locals.isLogged)
        return next();
    db.query('SELECT `notifications`.`id`, `notifications`.`content` FROM `notifications` WHERE `user_id` = ? AND `seen` = 0', [req.session.user], function (err, notifications) {
       if (err) {
           console.error(err);
           return next();
       }
       res.locals.notifications = notifications;
       next();
    });
});

/*
    WEBSOCKET
 */

db.query('DELETE FROM `active_users` WHERE 1=1;', function (err) {
    if (err)
        console.error(err);
});
var activeUsers = {};
io.on('connection', function(socket) {
    socket.on('user-active', function(data) {
        if (!data)
            return;
        db.query('INSERT INTO `active_users` SET `socket_id` = ?, `user_id` = ?', [socket.id, data.userId], function (err) {
            if (err)
                console.error(err);
        });
        activeUsers[socket.id] = data.userId;
        io.sockets.emit('user-active', data.userId);
    });
    socket.on('disconnect', function() {
        db.query('DELETE FROM `active_users` WHERE `socket_id` = ?', [socket.id], function (err) {
            if (err)
                console.error(err);
        });
        io.sockets.emit('user-disconnect', activeUsers[socket.id]);
    });

    // CHAT
    socket.on('new-chat-message', function (message) {
        if (!message)
            return;
        // FIND TARGET
        db.query('SELECT `users`.`id` ' +
            'FROM `users` ' +
            'INNER JOIN `likes` ON `likes`.`liked_id` = `users`.`id` AND `likes`.`user_id` = ? ' +
            'INNER JOIN `likes` AS `match` ON `match`.`user_id` = `users`.`id` AND `match`.`liked_id` = ? ' +
            'WHERE `users`.`id` = ?', [activeUsers[socket.id], activeUsers[socket.id], message.to], function (err, target) {
            if (err) {
                console.error(err);
                return;
            }
            if (!target || target.length === 0)
                return;
            // GET CURRENT USER
            db.query('SELECT `active_users`.`user_id`, `users`.`username`, `users`.`name`, ' +
                '`users_uploads`.`name` AS `profile_pic` ' +
                'FROM `active_users` ' +
                'INNER JOIN `users` ON `users`.`id` = `active_users`.`user_id` ' +
                'LEFT JOIN `users_uploads` ON `users_uploads`.`user_id` = `users`.`id` AND `users_uploads`.`is_profile_pic` = 1 ' +
                'WHERE `socket_id` = ?', [socket.id], function (err, user) {
                if (err) {
                    console.error(err);
                    return;
                }
                if (!user || user.length === 0)
                    return;
                user = user[0];

                // SAVE MESSAGE
                db.query('INSERT INTO `conversations` SET `from_id` = ?, `to_id` = ?, `message` = ?, `created_at` = ?', [
                    user.user_id,
                    target[0].id,
                    message.message,
                    new Date()
                ], function (err) {
                    if (err)
                        console.error(err);
                });

                // SEND NOTIFICATION
                var userModel = require('./models/user');
                require('./models/notification').send(
                    target[0].id,
                    '<a href="/' + userModel.htmlentities(user.username) +'">' + userModel.htmlentities(user.username) + '</a> vient de vous envoyer un message !',
                    io,
                    user.user_id,
                    'chat'
                );
                // SEND TO USER WHO RECEIVE THE MESSAGE
                db.query('SELECT `socket_id` FROM `active_users` WHERE `user_id` = ?', [message.to], function (err, socketId) {
                    if (err) {
                        console.error(err);
                        return;
                    }
                    if (socketId && socketId.length > 0)
                        io.to(socketId[0].socket_id).emit('new-chat-message', {
                            from: user.user_id,
                            from_account: {
                                name: user.name,
                                profile_pic: (user.profile_pic ? '/uploads/pics/' + user.profile_pic : '/assets/img/default_profile_pic.png')
                            },
                            message: require('./models/user').htmlentities(message.message)
                        });
                })
            });
        });
    })
});

/*
    ROUTES
 */

var authMiddleware = require('./middlewares/auth');

// HOME
app.all('/', require('./controllers/IndexController').index);

// USERS
var userController = require('./controllers/UserController');

app.post('/signin', userController.signin);
app.post('/signup', userController.signup);
app.post('/account/lost-password', userController.lostPassword);
app.get('/account/reset-password/:token', userController.resetPassword);
app.post('/account/reset-password/:token', userController.resetPassword);
//app.get('/account/valid', userController.validAccount);

app.get('/signout', authMiddleware, userController.signout);

app.get('/account', authMiddleware, userController.account);
app.post('/account', authMiddleware, userController.editAccount);
app.post('/account/password', authMiddleware, userController.editPassword);

// MATCHING
var profileController = require('./controllers/ProfileController');

var upload = multer({
    fileFilter: function (req, file, cb) {
        if (file.mimetype !== 'image/png' && file.mimetype !== 'image/jpeg')
            return cb(undefined, false);
        if (file.originalname.indexOf('.png') === -1 && file.originalname.indexOf('.jpg') === -1 && file.originalname.indexOf('.jpeg') === -1)
            return cb(undefined, false);
        cb(undefined, true);
    },
    limits: {
        fieldSize: '2MB'
    },
    storage: multer.diskStorage({
        destination: function (req, file, cb) {
            cb(null, path.join(__dirname, '../public/uploads/pics/'))
        },
        filename: function (req, file, cb) {
            cb(null, require('uuid/v4')() + '.' + (file.mimetype === 'image/png' ? 'png' : 'jpg'))
        }
    })
});
app.post('/account/photo', authMiddleware, function (req, res, next) {
    // Check if not 5 picture already saved
    db.query('SELECT COUNT(`id`) AS `count` FROM `users_uploads` WHERE `user_id` = ?', [req.session.user], function (err, rows) {
        if (err) {
            console.error(err);
            return res.json({status: false, error: 'Une erreur interne est survenue.'});
        }
        if (rows && rows.length > 0 && rows[0].count >= 5)
            return res.json({status: false, error: 'Vous ne pouvez avoir que 5 photos maximum sur notre service.'});
        next();
    })
}, upload.single('picture'), profileController.uploadPhoto);
app.delete('/account/photo/:id', authMiddleware, profileController.deletePhoto);
app.put('/account/photo/:id', authMiddleware, profileController.editPhoto);
app.post('/account/bio', authMiddleware, profileController.updateBio);

app.get('/find', authMiddleware, function (req, res) {
    db.query('SELECT `users_accounts`.`tags`, `users_accounts`.`location` FROM `users_accounts` WHERE `users_accounts`.`user_id` = ?', [req.session.user], function (err, account) {
       if (err) {
           console.error(err);
           return res.sendStatus(500);
       }
       if (!account || account.length === 0)
           account = {tags: '', location: ''};
       else
           account = account[0];
       res.render('profile/find', { title: 'Rechercher un utilisateur', user: account });
    });
});
app.post('/find', authMiddleware, profileController.find);

app.get('/view-match', authMiddleware, profileController.viewMatch);

// CHAT & NOTIFICATIONS
var chatController = require('./controllers/ChatController');

app.get('/chat', authMiddleware, chatController.index);
app.get('/:username/chat', authMiddleware, chatController.chat);

// ACCOUNTS
app.get('/:username', authMiddleware, function (req, res) {
    profileController.profile(req, res, io);
});
app.get('/:username/like', authMiddleware, function (req, res) {
    profileController.like(req, res, io);
});
app.get('/:username/block', authMiddleware, profileController.block);
app.get('/:username/report', authMiddleware, profileController.report);

// NOTIFICATIONS
app.get('/notifications/:id/seen', authMiddleware, function (req, res) {
    require('./models/notification').read(req.params.id);
    res.send();
});

/*
    LAUNCH
 */
server.listen(config.port);