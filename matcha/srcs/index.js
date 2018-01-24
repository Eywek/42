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
   res.locals.moment = moment;
   next();
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
    require('./models/database').query('SELECT COUNT(`id`) AS `count` FROM `users_uploads` WHERE `user_id` = ?', [req.session.user], function (err, rows) {
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

app.get('/:username', authMiddleware, profileController.profile);
app.get('/:username/like', authMiddleware, profileController.like);
app.get('/:username/unlike', authMiddleware, profileController.unlike);
app.get('/:username/block', authMiddleware, profileController.block);
app.get('/:username/report', authMiddleware, profileController.report);

app.get('/find', authMiddleware, function (req, res) {
   res.render('profile/find', { title: 'Rechercher un utilisateur' });
});
app.post('/find', authMiddleware, profileController.find);

app.get('/view-match', authMiddleware, profileController.viewMatch);

// CHAT & NOTIFICATIONS
var chatController = require('./controllers/ChatController');

app.get('/chat', authMiddleware, chatController.index);
app.get('/:username/chat', authMiddleware, chatController.chat);

/*
    LAUNCH
 */
app.listen(config.port);