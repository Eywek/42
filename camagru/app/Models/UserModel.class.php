<?php


namespace Models;


class UserModel extends Model
{

    protected $_fields = [
        'username' => 'required:alpha_num:unique:min=3:max=20',
        'email' => 'required:unique:email:max=150',
        'password' => 'required:password'
    ];

}