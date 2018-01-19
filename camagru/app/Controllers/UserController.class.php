<?php

namespace Controllers;

use Models\UserModel;
use Models\UsersTokenModel;
use Routing\Request;
use Routing\Response;
use Routing\View;

class UserController
{

    public function signin(Request $req, Response $res)
    {
        if (!isset($req->getData()['username']) || !isset($req->getData()['password']))
            return $res->sendJSON(['status' => false, 'error' => 'Vous devez remplir tous les champs.']);
        $findUser = UserModel::findFirst(['conditions' => ['username' => $req->getData()['username'], 'password' => hashPassword($req->getData()['password'])]]);
        if (!$findUser)
            return $res->sendJSON(['status' => false, 'error' => 'Vos identifiants sont incorrects.']);

        // Check email
        if (!empty(UsersTokenModel::findFirst(['conditions' => ['user_id' => $findUser->id, 'type' => 'EMAIL', 'used_at' => NULL]])))
            return $res->sendJSON(['status' => false, 'error' => 'Vous devez avoir validé votre email.']);

        // Success
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

        // Generate email token
        $token = UsersTokenModel::generate('EMAIL', $user->id);

        // Send email
        \sendMail($user->email, 'Inscription', new View('Emails/signup', [
            'username' => $user->username,
            'date' => date('Y-m-d H:i:s'),
            'ip' => getIP(),
            'url' => '/user/valid-email/' . $token
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
        $res->view('User/profile', ['user' => UserModel::getCurrent()]);
    }

}