module.exports = {

  index: function (req, res) {
      if (req.session.user)
          res.redirect('/account');
      else
          res.render('index', {title: 'Connectez-vous'});
  }

};