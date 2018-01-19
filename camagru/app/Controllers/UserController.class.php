<?php

namespace Controllers;

use Models\UserModel;
use Routing\Request;
use Routing\Response;

class UserController
{

    public function signin(Request $req, Response $res)
    {

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

        // Send email

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

    }

    public function edit(Request $req, Response $res)
    {

    }

    public function profile(Request $req, Response $res)
    {

    }

}