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
const FortyTwoStrategy = require('passport-42').Strategy
const GitHubStrategy = require('passport-github').Strategy
const TwitterStrategy = require('passport-twitter').Strategy
const GoogleStrategy = require('passport-google-oauth20').Strategy
const db = require('./srcs/models/database')
const deleteWorker = require('./srcs/workers/delete')
const { exec } = require('child_process');
exec('ffmpeg -h', (error, stdout, stderr) => {
  if (error) {
    console.error('ffmpeg is needed!')
    return process.exit()
  }
})

deleteWorker.start()
const logOrInsert = (profile, type, cb) => {
  db.query("SELECT `user_id` FROM `users_oauth` WHERE `oauth_id` = ? AND `oauth_type` = ?", [profile.id, type], (err, rows) => {
    if (err)
      console.error(err)
    if (rows && rows.length > 0)
      return cb(undefined, {id: rows[0].user_id})
    // CREATE USER
    db.query('SELECT `users`.`email`, `users`.`username` FROM `users` WHERE `username` = ? ' + (profile.email.length > 0 ? 'OR `email` = ?' : '') + ' LIMIT 1', [profile.username, profile.email], (err, rows) => {
      if (err)
        console.error(err)
      if (rows && rows.length > 0) {
        if (rows[0].username === profile.username)
          profile.username += Math.round(Math.random() * (100 - 1) + 1)
        if (rows[0].email === profile.email && profile.email.length > 0)
          profile.email = ''
      }

      db.query('INSERT INTO `users` SET `name` = ?, `last_name` = ?, `username` = ?, `email` = ?, `password` = NULL, `lang` = ?, `created_at` = ?', [
        profile.first_name,
        profile.last_name,
        profile.username,
        profile.email,
        'en',
        new Date()
      ], (err, user) => {
        if (err)
          return cb(err)
        db.query("INSERT INTO `users_oauth` SET `user_id` = ?, `oauth_id` = ?, `oauth_type` = ?", [user.insertId, profile.id, type], (err, rows) => {
          if (err)
            return cb(err)
          cb(undefined, {id: user.insertId})
        })
      })
    })
  })
}

passport.use(new LocalStrategy((username, password, done) => {
  // Find user with this username and password
  userModel.login(username, password, (err, userId) => {
    if (err)
      return done(undefined, false, i18n.__(err))
    done(undefined, {id: userId})
  })
}))
passport.use(new GitHubStrategy({
    clientID: 'c969547925e815a667e4',
    clientSecret: '167c3d8676cf5971cc2ede14bbdbd85b985e96c6',
    callbackURL: "http://localhost:8080/signin/github/callback"
  },
  function(accessToken, refreshToken, profile, cb) {
    logOrInsert({
      id: profile.id,
      first_name: profile.displayName,
      last_name: '',
      username: profile.username,
      email: profile._json.email || ''
    }, 'GITHUB', cb)
  }
))
passport.use(new FortyTwoStrategy({
    clientID: 'f3c4112a603858f8ccce9b41bc357857e9675b14e66e7cdb70db958fb6412685',
    clientSecret: '52c5bf716dcdc8c530b1e422daedf13205040371745e9040b22a0a66f4d778c2',
    callbackURL: "http://localhost:8080/signin/42/callback"
  }, (accessToken, refreshToken, profile, cb) => {
    logOrInsert({
      id: profile.id,
      first_name: profile._json.first_name,
      last_name: profile._json.last_name,
      username: profile._json.login,
      email: profile._json.email
    }, '42', cb)
  }
))
passport.use(new TwitterStrategy({
    consumerKey: 'SmKqQa55ZioTILYyihgg0RZte',
    consumerSecret: 'DtNOdUSwE5PshINJCU7Ho7mlNEN5wrKrhRP3EqGT383mmodLvs',
    callbackURL: "http://127.0.0.1:8080/signin/twitter/callback"
  }, (token, tokenSecret, profile, cb) => {
    logOrInsert({
      id: profile.id,
      first_name: profile.displayName,
      last_name: '',
      username: profile.username,
      email: ''
    }, 'TWITTER', cb)
  }
))
passport.use(new GoogleStrategy({
    clientID: '323624276627-02u32h2kak0k49rf4ps0g7vmu23986hq.apps.googleusercontent.com',
    clientSecret: 'yLH2ugNjaJ6Fb4pXWrHFh5dh',
    callbackURL: "http://127.0.0.1:8080/signin/google/callback"
  }, (token, tokenSecret, profile, cb) => {
    logOrInsert({
      id: profile.id,
      first_name: profile.name.givenName,
      last_name: profile.name.familyName,
      username: profile.displayName,
      email: (profile._json.emails && profile._json.emails[0]) ? profile._json.emails[0].value : ''
    }, 'GOOGLE', cb)
  }
))
app.use(passport.initialize())

i18n.configure({
  locales:['en', 'fr'],
  directory: __dirname + '/locales',
  register: global
})

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
  if (req.session.user === undefined) {
    i18n.init()
    res.__ = i18n.__
    return next()
  }
  db.query('SELECT `lang` FROM `users` WHERE `id` = ?', [req.session.user], (err, user) => {
    if (err)
      console.error(err)
    if (!user || user.length === 0) {
      req.session.user = undefined
      return res.redirect('/')
    }
    res.locals.current_user = req.user = {language: user[0].lang}
    i18n.setLocale(req.user.language)
    i18n.init()
    res.__ = i18n.__
    next()
  })
})

// USERS
const userController = require('./srcs/controllers/UserController')
const authMiddleware = require('./srcs/middlewares/auth')
const login = (req, res, next, method, onlyRedirect) => {
  passport.authenticate(method, { session: false }, (err, user, info) => {
    if (err) {
      console.error(err)
      return res.redirect('/')
    }
    if (!user)
      return (onlyRedirect) ? res.redirect('/') : res.json({status: false, error: info})
    req.session.user = user.id
    if (onlyRedirect)
      return res.redirect('/account')
    return res.json({status: true, success: res.__("You're now logged"), redirect: '/account'})
  })(req, res, next)
}

app.post('/signin', (req, res, next) => {
  login(req, res, next, 'local')
})
app.get('/signin/42', passport.authenticate('42'))
app.get('/signin/42/callback',(req, res, next) => {
  login(req, res, next, '42', true)
})
app.get('/signin/github', passport.authenticate('github', { scope: ['read:user', 'user:email'] }))
app.get('/signin/github/callback',(req, res, next) => {
  login(req, res, next, 'github', true)
})
app.get('/signin/twitter', passport.authenticate('twitter'))
app.get('/signin/twitter/callback',(req, res, next) => {
  login(req, res, next, 'twitter', true)
})
app.get('/signin/google', passport.authenticate('google', { scope: ['profile', 'https://www.googleapis.com/auth/plus.profile.emails.read'] }))
app.get('/signin/google/callback',(req, res, next) => {
  login(req, res, next, 'google', true)
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
      return cb(undefined, false)
    if (file.originalname.indexOf('.png') === -1)
      return cb(undefined, false)
    cb(undefined, true)
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
})
app.post('/account/photo', authMiddleware, upload.single('picture'), userController.uploadAvatar)
app.get('/user/:username', authMiddleware, userController.profile)

// GLOBAL ROUTES
const movieController = require('./srcs/controllers/MovieController')

app.get('/', (req, res) => {
  if (req.session.user)
    return res.redirect('/account')
  res.render('home', {title: 'Hypertube'})
})
app.post('/search', authMiddleware, movieController.search)
app.get('/library', authMiddleware, (req, res) => {
  db.query('SELECT `media_id` FROM `views` WHERE `user_id` = ?', [req.session.user], (err, views) => {
    if (err)
      console.error(err)
    if (!views)
      views = []
    else
      views = views.map((view) => {
        return view.media_id
      })
    res.render('library', {title: i18n.__('Library'), oldest_date: '1900', viewedMovies: views})
  })
})
app.post('/library/:page(\\d+)', authMiddleware, movieController.library)
app.get('/:title', authMiddleware, movieController.view)
app.post('/:title/comment', authMiddleware, movieController.comment)
app.get('/:title/like', authMiddleware, movieController.like)
app.delete('/comment/:comment_id', authMiddleware, movieController.deleteComment)
app.get('/:id/stream', authMiddleware, movieController.stream)
app.get('/:id/subtitles/:lang([A-Za-z]{2})', authMiddleware, movieController.subtitles)

app.listen(config.port)