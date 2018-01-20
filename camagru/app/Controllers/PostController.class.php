<?php

namespace Controllers;

use Models\PostModel;
use Models\PostsCommentModel;
use Models\PostsLikeModel;
use Models\UserModel;
use Routing\Request;
use Routing\Response;

class PostController extends Controller
{

    public function post(Request $req, Response $res) // TODO
    {

    }

    public function like(Request $req, Response $res)
    {
        if (!UserModel::isLogged())
            throw new \Routing\ForbiddenException();
        $findPost = PostModel::findFirst(['fields' => ['id'], 'conditions' => ['id' => $req->id]]);
        if (!$findPost)
            throw new \Routing\NotFoundException();

        PostsLikeModel::create([
            'post_id' => $findPost->id,
            'user_id' => UserModel::getCurrent()['id']
        ]);

        return $res->sendJSON(['status' => true, 'success' => 'Le like a été ajouté']);
    }

    public function comment(Request $req, Response $res)
    {
        if (!UserModel::isLogged())
            throw new \Routing\ForbiddenException();
        $findPost = PostModel::findFirst(['fields' => ['id'], 'conditions' => ['id' => $req->id]]);
        if (!$findPost)
            throw new \Routing\NotFoundException();
        // Validate
        $comment = new PostsCommentModel();
        if (!$comment->validate($req->getData()))
            return $res->sendJSON(['status' => false, 'error' => $comment->getValidationError()]);

        // Save
        PostsCommentModel::create([
            'post_id' => $findPost->id,
            'user_id' => UserModel::getCurrent()['id'],
            'content' => \sanitize($req->getData()['content'])
        ]);

        return $res->sendJSON(['status' => true, 'success' => 'Le commentaire a été ajouté']);
    }

    public function get(Request $req, Response $res)
    {
        $posts = PostModel::find([
            'order' => ['`posts`.`created_at`' => 'DESC'],
            'join' => [PostsCommentModel::class, PostsLikeModel::class]
        ]);
        return $res->sendJSON(['status' => true, 'data' => ['posts' => $posts, 'count' => count($posts)]]);
    }

}