module.exports = function (req, res, next) {
    if (req.session.user)
        return next();
    if (req.xhr)
        return res.json({status: false, error: 'Vous devez vous connecter pour effectuer cette action.'});
    res.redirect('/');
};