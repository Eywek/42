<?php
$dispatcher->addRoute('GET', '/', \Controllers\IndexController::class);


/*
 * USERS
 */
$dispatcher->addRoute('POST', '/user/signup', \Controllers\UserController::class, 'signup');
$dispatcher->addRoute('POST', '/user/signin', \Controllers\UserController::class, 'signin');
$dispatcher->addRoute('GET', '/user/signout', \Controllers\UserController::class, 'signout');

$dispatcher->addRoute('GET', '/user/valid-email/{token:[0-9a-f-]+}', \Controllers\UserController::class, 'validEmail');
$dispatcher->addRoute('POST', '/user/lost-password', \Controllers\UserController::class, 'lostPassword');
$dispatcher->addRoute('GET', '/user/reset-password/{token:[0-9a-f-]+}', \Controllers\UserController::class, 'resetPassword');
$dispatcher->addRoute('POST', '/user/reset-password/{token:[0-9a-f-]+}', \Controllers\UserController::class, 'resetPassword');

$dispatcher->addRoute('GET', '/user', \Controllers\UserController::class, 'profile');
$dispatcher->addRoute('POST', '/user/edit', \Controllers\UserController::class, 'edit');
$dispatcher->addRoute('POST', '/user/edit-password', \Controllers\UserController::class, 'editPassword');
$dispatcher->addRoute('POST', '/user/edit-settings', \Controllers\UserController::class, 'editSettings');

/*
 * POSTS
 */
$dispatcher->addRoute('GET', '/posts', \Controllers\PostController::class, 'get');
$dispatcher->addRoute('POST', '/posts/{id:[0-9]+}/like', \Controllers\PostController::class, 'like');
$dispatcher->addRoute('POST', '/posts/{id:[0-9]+}/unlike', \Controllers\PostController::class, 'unlike');
$dispatcher->addRoute('POST', '/posts/{id:[0-9]+}/comment', \Controllers\PostController::class, 'comment');
$dispatcher->addRoute('POST', '/posts', \Controllers\PostController::class, 'post');