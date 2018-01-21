<?php

namespace Models;

class PostModel extends Model
{

    static protected $_from = [
        UserModel::class => ['id', 'username']
    ];

}