<?php


namespace Models;


class UserModel extends Model
{

    protected $_fields = [
        'username' => 'required:alpha_num:unique:min=3:max=20',
        'email' => 'required:unique:email:max=150',
        'password' => 'required:password'
    ];

    static private $_currentUser;

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
        if (self::$_currentUser)
            return self::$_currentUser;
        // Find user
        $findUser = self::findFirst(['conditions' => ['id' => $_SESSION['user']]]);
        if (!$findUser)
            return false;
        self::$_currentUser = $findUser;
        return $findUser;
    }

    static public function hasLike(PostModel $post)
    {
        if (!self::isLogged())
            return false;
        foreach ($post->likes as $like)
            if ($like->user_id === self::getCurrent()->id)
                return true;
        return false;
    }

}