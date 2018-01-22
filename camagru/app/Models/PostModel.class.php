<?php

namespace Models;

class PostModel extends Model
{

    protected $_fields = [
        'title' => 'required:min=5:max=80',
        'user_id' => ''
    ];

    static protected $_from = [
        UserModel::class => ['id', 'username']
    ];

}