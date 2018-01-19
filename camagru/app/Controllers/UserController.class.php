<?php

namespace Controllers;

use Models\UserModel;
use Routing\Request;
use Routing\Response;
use Routing\View;

class UserController
{

    public function signin(Request $req, Response $res)
    {
        if (!isset($req->getData()['username']) || !isset($req->getData()['password']))
            return $res->sendJSON(['status' => false, 'error' => 'Vous devez remplir tous les champs.']);
        $findUser = UserModel::findFirst(['conditions' => ['username' => $req->getData()['username'], 'password' => $req->getData()['password']]]);
        if (!$findUser)
            return $res->sendJSON(['status' => false, 'error' => 'Vos identifiants sont incorrects.']);

        // TODO: Check if user has valided his email

        $findUser->login();

        return $res->sendJSON(['status' => true, 'success' => 'Vous vous êtes bien connecté !']);
    }

    public function signup(Request $req, Response $res)
    {
        // Validate
        $user = new UserModel();
        if (!$user->validate($req->getData()))
            return $res->sendJSON(['status' => false, 'error' => $user->getValidationError()]);
        if ($req->getData()['password'] !== $req->getData()['password_confirmation'])
            return $res->sendJSON(['status' => false, 'error' => 'Les mot de passe ne correspondent pas.']);

        // Save
        $user->username = \sanitize($req->getData()['username']);
        $user->email = \sanitize($req->getData()['email']);
        $user->password = \hashPassword($req->getData()['password']);
        $user->save();

        // Send email, TODO: Create a token to valid email, store it
        \sendMail($user->email, 'Inscription', new View('Emails/signup', [
            'username' => $user->username,
            'date' => date('Y-m-d H:i:s'),
            'ip' => getIP()
        ]));

        // Success message
        return $res->sendJSON(['status' => true, 'success' => 'Vous vous êtes bien inscris, vous avez reçu un mail de confirmation.']);
    }

    public function signout(Request $req, Response $res)
    {
        session_destroy();
        $res->redirect('/');
    }

    public function lostPassword(Request $req, Response $res)
    {

    }

    public function resetPassword(Request $req, Response $res)
    {

    }

    public function editPassword(Request $req, Response $res)
    {
        if (!UserModel::isLogged())
            $res->redirect('/');
    }

    public function edit(Request $req, Response $res)
    {
        if (!UserModel::isLogged())
            $res->redirect('/');
    }

    public function profile(Request $req, Response $res)
    {
        if (!UserModel::isLogged())
            $res->redirect('/');
    }

}