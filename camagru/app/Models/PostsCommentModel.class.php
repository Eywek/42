<?php

namespace Models;

class PostsCommentModel extends Model
{

    protected $_fields = [
        'content' => 'required:min=3:max=500'
    ];

    static protected $_fromDefault = true;
    static protected $_from = [
        UserModel::class => ['id', 'username', 'email']
    ];

}