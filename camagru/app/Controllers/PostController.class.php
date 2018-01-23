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

    public function post(Request $req, Response $res)
    {
        if (!UserModel::isLogged())
            throw new \Routing\ForbiddenException();
        $this->set(['title' => 'Poster une publication', 'posts' => PostModel::find(['conditions' => ['user_id' => UserModel::getCurrent()->id], 'order' => ['id' => 'DESC']])]);
        if ($req->getMethod() !== 'POST')
            return NULL;
        // Validate title
        $post = new PostModel();
        if (!$post->validate(['title' => $req->getData()['title']]))
            return $res->sendJSON(['status' => false, 'error' => $post->getValidationError()]);
        // Validate image
        $img = explode(',', $req->getData()['img']);
        if (count($img) !== 2)
            return $res->sendJSON(['status' => false, 'error' => 'Veuillez fournir une image valide.']);
        $img = $img[1];
        if (base64_decode($img) === false || base64_encode(base64_decode($img)) != $img)
            return $res->sendJSON(['status' => false, 'error' => 'Veuillez fournir une image valide.']);
        try {
            if (($img = \imagecreatefromstring(base64_decode($img))) === false)
                return $res->sendJSON(['status' => false, 'error' => 'Veuillez fournir une image valide.']);
        } catch (\Exception $e) {
            return $res->sendJSON(['status' => false, 'error' => 'Veuillez fournir une image moins volumineuse.']);
        }

        // Merge with mask
        $maskPath = PUBLIC_PATH . 'assets' . DS . 'img' . DS . 'masks' . DS . $req->getData()['mask'] . '.png';
        if (!file_exists($maskPath))
            return $res->sendJSON(['status' => false, 'error' => 'Veuillez rafraichir la page et réessayer.']);
        if (!($result = \mergeImage($img, \imagecreatefromstring(file_get_contents($maskPath)))))
            return $res->sendJSON(['status' => false, 'error' => 'Veuillez fournir une image valide.']);

        // Save post
        $post->title = \sanitize($req->getData()['title']);
        $post->user_id = UserModel::getCurrent()->id;
        $post->save();

        // Save file
        file_put_contents(PUBLIC_PATH . 'assets' . DS . 'img' . DS . 'uploads' . DS . 'post-' . $post->id . '.png', $result);

        // Success
        return $res->sendJSON(['status' => true, 'success' => 'Le post à bien été ajouté', 'data' => [
            'post' => [
                'id' => $post->id,
                'url' => \url('/assets/img/uploads/post-' . $post->id . '.png')
            ]
        ]]);
    }

    public function delete(Request $req, Response $res)
    {
        if (!UserModel::isLogged())
            throw new \Routing\ForbiddenException();
        if (empty(PostModel::findFirst(['conditions' => [
            'id' => $req->id,
            'user_id' => UserModel::getCurrent()->id
        ]])))
            throw new \Routing\NotFoundException();

        PostModel::delete([
            'id' => $req->id,
            'user_id' => UserModel::getCurrent()->id
        ]);
        PostsCommentModel::delete([
            'post_id' => $req->id
        ]);
        PostsLikeModel::delete([
            'post_id' => $req->id
        ]);
        @unlink(PUBLIC_PATH . 'assets' . DS . 'img' . DS . 'uploads' . DS . 'post-' . $req->id . '.png');

        return $res->sendJSON(['status' => true, 'success' => 'Le post a bien été supprimé']);
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
        $authorEmail = UserModel::findFirst(['fields' => ['email'], 'conditions' => ['id' => $findPost->user_id]]);
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