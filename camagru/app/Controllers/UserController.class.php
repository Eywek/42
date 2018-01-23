<?php

namespace Controllers;

use Models\UserModel;
use Models\UsersSettingModel;
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
        return $res->sendJSON(['status' => true, 'success' => 'Vous vous êtes bien connecté !', 'redirect' => \url('/')]);
    }

    public function validEmail(Request $req, Response $res)
    {
        $findToken = UsersTokenModel::findFirst(['fields' => ['id'], 'conditions' => ['token' => $req->token, 'type' => 'EMAIL', 'used_at' => NULL]]);
        if (!$findToken)
            throw new \Routing\NotFoundException();

        // Set token as used
        $findToken->used_at = date('Y-m-d H:i:s');
        $findToken->save();

        $res->redirect('/');
    }

    public function signup(Request $req, Response $res)
    {
        // Validate
        $user = new UserModel();
        if (!$user->validate($req->getData()))
            return $res->sendJSON(['status' => false, 'error' => $user->getValidationError()]);
        if (!isset($req->getData()['password_confirmation']) || $req->getData()['password'] !== $req->getData()['password_confirmation'])
            return $res->sendJSON(['status' => false, 'error' => 'Les mot de passe ne correspondent pas.']);

        // Save
        $user->username = \sanitize($req->getData()['username']);
        $user->email = \sanitize($req->getData()['email']);
        $user->password = \hashPassword($req->getData()['password']);
        $user->save();

        // Add settings
        UsersSettingModel::create([
            'user_id' => $user->id
        ]);

        // Generate email token
        $token = UsersTokenModel::generate('EMAIL', $user->id);

        // Send email
        \sendMail($user->email, 'Inscription', new View('Emails/signup', [
            'username' => $user->username,
            'date' => date('Y-m-d H:i:s'),
            'ip' => getIP(),
            'url' => \url('/user/valid-email/' . $token)
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
        if (!isset($req->getData()['email']))
            return $res->sendJSON(['status' => false, 'error' => 'Vous devez spécifier un email.']);
        $findUser = UserModel::findFirst(['fields' => ['id', 'email', 'username'], 'conditions' => ['email' => $req->getData()['email']]]);
        if (!$findUser)
            return $res->sendJSON(['status' => false, 'error' => 'Aucun utilisateur trouvé avec ce mail.']);

        // Generate email token
        $token = UsersTokenModel::generate('RESET_PW', $findUser->id);

        // Send email
        \sendMail($findUser->email, 'Réinitialisation de mot de passe', new View('Emails/reset_password', [
            'username' => $findUser->username,
            'date' => date('Y-m-d H:i:s'),
            'ip' => getIP(),
            'url' => \url('/user/reset-password/' . $token)
        ]));

        // Success message
        return $res->sendJSON(['status' => true, 'success' => 'Un email de rénitialisation vous a été envoyé.']);
    }

    public function resetPassword(Request $req, Response $res)
    {
        $findToken = UsersTokenModel::findFirst(['fields' => ['id', 'user_id'], 'conditions' => ['token' => $req->token, 'type' => 'RESET_PW']]);
        if (!$findToken)
            throw new \Routing\NotFoundException();
        $user = $findToken->getUser();
        if (!$user)
            throw new \Routing\NotFoundException();
        if ($req->getMethod() !== 'POST')
            return $res->view('User/reset_password', ['title' => 'Rénitialiser son mot de passe', 'user' => $user]);
        // Validate
        if (!$user->validate($req->getData(), ['password']))
            return $res->sendJSON(['status' => false, 'error' => $user->getValidationError()]);
        if (!isset($req->getData()['password_confirmation']) || $req->getData()['password'] !== $req->getData()['password_confirmation'])
            return $res->sendJSON(['status' => false, 'error' => 'Les mot de passe ne correspondent pas.']);

        // Save
        $user->password = \hashPassword($req->getData()['password']);
        $user->save();

        // Set token as used
        $findToken->used_at = date('Y-m-d H:i:s');
        $findToken->save();

        return $res->sendJSON(['status' => true, 'success' => 'Le mot de passe à bien été modifié']);
    }

    public function editPassword(Request $req, Response $res)
    {
        if (!UserModel::isLogged())
            throw new \Routing\ForbiddenException();
        // Validate
        $user = UserModel::getCurrent();
        if (!$user->validate($req->getData(), ['password']))
            return $res->sendJSON(['status' => false, 'error' => $user->getValidationError()]);
        if (!isset($req->getData()['password_confirmation']) || $req->getData()['password'] !== $req->getData()['password_confirmation'])
            return $res->sendJSON(['status' => false, 'error' => 'Les mot de passe ne correspondent pas.']);

        // Update data
        $user->password = \hashPassword($req->getData()['password']);
        $user->save();

        return $res->sendJSON(['status' => true, 'success' => 'Votre mot de passe a bien été sauvegardé !']);
    }

    public function edit(Request $req, Response $res)
    {
        if (!UserModel::isLogged())
            throw new \Routing\ForbiddenException();
        // Validate
        $user = UserModel::getCurrent();
        if (!$user->validate($req->getData(), ['username', 'email'], [$user->id]))
            return $res->sendJSON(['status' => false, 'error' => $user->getValidationError()]);

        // Update data
        $user->username = \sanitize($req->getData()['username']);
        $user->email = \sanitize($req->getData()['email']);
        $user->save();

        return $res->sendJSON(['status' => true, 'success' => 'Vos informations ont bien été sauvegardées !']);
    }

    public function editSettings(Request $req, Response $res)
    {
        if (!UserModel::isLogged())
            throw new \Routing\ForbiddenException();
        if (!isset($req->getData()['email_notifications']))
            throw new \Routing\BadRequestException();

        UsersSettingModel::update([
            'email_notifications' => intval($req->getData()['email_notifications'])
        ], ['user_id' => UserModel::getCurrent()->id]);

        return $res->sendJSON(['status' => true, 'success' => 'Vos préférences ont bien été sauvegardées !']);
    }

    public function profile(Request $req, Response $res)
    {
        if (!UserModel::isLogged())
            $res->redirect('/');
        $user = UserModel::getCurrent();
        $user->settings = UsersSettingModel::findFirst(['conditions' => ['user_id' => $user->id]]);
        return $res->view('User/profile', ['user' => $user, 'title' => $user->username]);
    }

}