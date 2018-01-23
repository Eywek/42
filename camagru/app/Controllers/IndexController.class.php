<?php

namespace Controllers;

use Models\PostModel;
use Models\PostsCommentModel;
use Models\PostsLikeModel;
use Models\UserModel;
use Routing\Request;
use Routing\Response;

class IndexController extends Controller
{

    public function index(Request $req, Response $res)
    {
        $posts = PostModel::find([
            'order' => ['`posts`.`created_at`' => 'DESC'],
            'join' => [PostsCommentModel::class, PostsLikeModel::class],
            'from' => [UserModel::class],
            'limit' => 5
        ]);
        $this->set(['title' => 'Accueil', 'posts' => $posts]);
    }

    public function setup(Request $req, Response $res)
    {
        require CONFIG_PATH . 'setup.php';
        exit();
    }

}