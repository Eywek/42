const express = require('express')
const bodyParser = require('body-parser')
const session = require('express-session')
const config = require('./config/config')
const path = require('path')
const moment = require('moment')
const multer = require('multer')
const i18n = require("i18n")
const app = express()
const passport = require('passport')
const LocalStrategy = require('passport-local').Strategy
const userModel = require('./srcs/models/user')

passport.use(new LocalStrategy((username, password, done) => {
  // Find user with this username and password
  userModel.login(username, password, (err, userId) => {
    if (err)
      return done(undefined, false, i18n.__(err))
    done(undefined, {id: userId})
  })
}))
app.use(passport.initialize())

i18n.configure({
  locales:['en', 'fr'],
  directory: __dirname + '/locales'
})

app.use(i18n.init)
app.set('view engine', 'pug')
app.set('views', path.join(__dirname, 'views'))
app.use(express.static(path.join(__dirname, 'public')))
app.use(bodyParser.json())
app.use(bodyParser.urlencoded({ extended: true }))
app.set('trust proxy', 1)
app.use(session({
  secret: 'wMnGuvBetLR27y48Y5y36fN8NM49Vp',
  resave: true,
  saveUninitialized: true,
  cookie: { secure: false }
}))
app.use(function (req, res, next) {
  res.locals.isLogged = (req.session.user !== undefined)
  res.locals.userId = req.session.user
  res.locals.moment = moment
  res.locals.notifications = []
  next()
})

// USERS
const userController = require('./srcs/controllers/UserController')
const authMiddleware = require('./srcs/middlewares/auth')

app.post('/signin', (req, res, next) => {
  passport.authenticate('local', { session: false }, (err, user, info) => {
    if (err)
      return next(err)
    if (!user)
      return res.json({status: false, error: info})
    req.session.user = user.id
    return res.json({status: true, success: res.__("You're now logged"), redirect: '/account'})
  })(req, res, next)
})
app.post('/signup', userController.signup)
app.post('/account/lost-password', userController.lostPassword)
app.get('/account/reset-password/:token', userController.resetPassword)
app.post('/account/reset-password/:token', userController.resetPassword)
app.get('/signout', authMiddleware, userController.signout)
app.get('/account', authMiddleware, userController.account)
app.post('/account', authMiddleware, userController.editAccount)
app.post('/account/password', authMiddleware, userController.editPassword)

let upload = multer({
  fileFilter: function (req, file, cb) {
    if (file.mimetype !== 'image/png')
      return cb(undefined, false);
    if (file.originalname.indexOf('.png') === -1)
      return cb(undefined, false);
    cb(undefined, true);
  },
  limits: {
    fieldSize: '2MB'
  },
  storage: multer.diskStorage({
    destination: function (req, file, cb) {
      cb(null, path.join(__dirname, '/public/uploads/'))
    },
    filename: function (req, file, cb) {
      cb(null, req.session.user + '.png')
    }
  })
});
app.post('/account/photo', authMiddleware, upload.single('picture'), userController.uploadAvatar);

// GLOBAL ROUTES
const movieController = require('./srcs/controllers/MovieController')

app.get('/', (req, res) => {
  if (req.session.user)
    return res.redirect('/account')
  res.render('home', {title: 'Hypertube'})
})
app.post('/search', authMiddleware, movieController.search)
app.get('/library', authMiddleware, (req, res) => {
  res.render('library', {title: i18n.__('Library')})
})
app.get('/library/:limit(\\d+)/:offset(\\d+)', authMiddleware, movieController.library)
app.get('/:title', authMiddleware, movieController.view)
app.post('/:title/comment', authMiddleware, movieController.comment)
app.get('/:id/stream', authMiddleware, movieController.stream)


app.listen(config.port)