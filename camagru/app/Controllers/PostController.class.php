<?php

namespace Controllers;

use Models\PostModel;
use Models\PostsCommentModel;
use Models\PostsLikeModel;
use Models\UserModel;
use Models\UsersSettingModel;
use Routing\Request;
use Routing\Response;
use Routing\View;

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
        $findLikeWithThisUser = PostsLikeModel::findFirst(['fields' => ['id'], 'conditions' => ['post_id' => $req->id, 'user_id' => UserModel::getCurrent()->id]]);
        if (!empty($findLikeWithThisUser))
            throw new \Routing\BadRequestException();

        PostsLikeModel::create([
            'post_id' => $findPost->id,
            'user_id' => UserModel::getCurrent()->id
        ]);

        return $res->sendJSON(['status' => true, 'success' => 'Le like a été ajouté']);
    }

    public function unlike(Request $req, Response $res)
    {
        if (!UserModel::isLogged())
            throw new \Routing\ForbiddenException();
        $findPost = PostModel::findFirst(['fields' => ['id'], 'conditions' => ['id' => $req->id]]);
        if (!$findPost)
            throw new \Routing\NotFoundException();

        PostsLikeModel::delete([
            'post_id' => $findPost->id,
            'user_id' => UserModel::getCurrent()->id
        ]);

        return $res->sendJSON(['status' => true, 'success' => 'Le like a été supprimé']);
    }

    public function comment(Request $req, Response $res)
    {
        if (!UserModel::isLogged())
            throw new \Routing\ForbiddenException();
        $findPost = PostModel::findFirst(['fields' => ['id', 'title', 'user_id'], 'conditions' => ['id' => $req->id]]);
        if (!$findPost)
            throw new \Routing\NotFoundException();
        // Validate
        $comment = new PostsCommentModel();
        if (!$comment->validate($req->getData()))
            return $res->sendJSON(['status' => false, 'error' => $comment->getValidationError()]);

        // Save
        PostsCommentModel::create([
            'post_id' => $findPost->id,
            'user_id' => UserModel::getCurrent()->id,
            'content' => \sanitize($req->getData()['content'])
        ]);

        $postAuthorSettings = UsersSettingModel::findFirst(['fields' => ['email_notifications'], 'conditions' => ['user_id' => $findPost->user_id]]);
        $authorEmail = UsersSettingModel::findFirst(['fields' => ['email'], 'conditions' => ['id' => $findPost->user_id]]);
        if ($postAuthorSettings && $postAuthorSettings->email_notifications && $authorEmail)
            \sendMail($authorEmail->email, "Commentaire sur votre publication", new View('Emails/new_comment', [
                'author' => UserModel::getCurrent()->username,
                'date' => date('Y-m-d H:i:s'),
                'title' => $findPost->title
            ]));

        return $res->sendJSON(['status' => true, 'success' => 'Le commentaire a été ajouté', 'data' => [
            'comment' => [
                'content' => \sanitize($req->getData()['content'])
            ],
            'post' => [
                'id' => $findPost->id
            ]
        ]]);
    }

    public function get(Request $req, Response $res)
    {
        $params = [
            'order' => ['`posts`.`created_at`' => 'DESC'],
            'join' => [PostsCommentModel::class, PostsLikeModel::class],
            'from' => [UserModel::class]
        ];
        if ($req->limit)
            $params['limit'] = (($req->offset) ? $req->offset . ',' : '') . $req->limit;
        $posts = PostModel::find($params);
        if (UserModel::isLogged())
            foreach ($posts as $key => $post)
                $posts[$key]->hasLiked = UserModel::hasLike($post);
        return $res->sendJSON(['status' => true, 'data' => ['posts' => $posts, 'count' => count($posts)]]);
    }

}