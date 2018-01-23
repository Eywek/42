/*
    SETUP
 */
var express = require('express');
var config = require('../config/config');
var app = express();
app.set('view engine', 'pug');
app.set('views', './views');

/*
    ROUTES
 */

// HOME
app.all('/', require('./controllers/IndexController').index);

// USERS
var userController = require('./controllers/UserController');

app.get('/sign', function (req, res) {
    res.render('user/auth', { title: 'Rejoignez-nous' });
});
app.post('/signin', userController.signin);
app.post('/signup', userController.signup);
app.post('/account/lost-password', userController.lostPassword);
app.get('/account/reset-password', function (req, res) {
    res.render('user/reset_password', { title: 'Rénitialisation du mot de passe' });
});
app.post('/account/reset-password', userController.resetPassword);
app.get('/account/valid', userController.validAccount);

app.get('/signout', userController.signout);

app.get('/account', userController.account);
app.post('/account', userController.editAccount);
app.post('/account/password', userController.editPassword);

// MATCHING
var profileController = require('./controllers/ProfileController');

app.post('/account/add-photo', profileController.uploadPhoto);
app.post('/account/bio', profileController.updateBio);

app.get('/{username}', profileController.profile);
app.get('/{username}/like', profileController.like);
app.get('/{username}/unlike', profileController.unlike);
app.get('/{username}/block', profileController.block);
app.get('/{username}/report', profileController.report);

app.get('/find', function (req, res) {
   res.render('profile/find', { title: 'Rechercher un utilisateur' });
});
app.post('/find', profileController.find);

app.get('/view-match', profileController.viewMatch);

// CHAT & NOTIFICATIONS
var chatController = require('./controllers/ChatController');

app.get('/{username}/chat', chatController.chat);

/*
    LAUNCH
 */
app.listen(config.port);