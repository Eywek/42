<?php


namespace Models;


class UserModel extends Model
{

    protected $_fields = [
        'username' => 'required:alpha_num:unique:min=3:max=20',
        'email' => 'required:unique:email:max=150',
        'password' => 'required:password'
    ];

    public function login()
    {
        if (!isset($this->id))
            return false;
        $_SESSION['user'] = $this->id;
        return true;
    }

    static public function isLogged()
    {
        return self::getCurrent() !== false;
    }

    static public function getCurrent()
    {
        if (!isset($_SESSION['user']))
            return false;
        // Find user
        $findUser = self::findFirst(['conditions' => ['id' => $_SESSION['user']]]);
        if (!$findUser)
            return false;
        return $findUser;
    }

}