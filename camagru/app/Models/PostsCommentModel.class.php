<?php

namespace Models;

class PostsCommentModel extends Model
{

    protected $_fields = [
        'content' => 'required:min=10:max=500'
    ];

}