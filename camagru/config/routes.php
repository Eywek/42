<?php
$dispatcher->addRoute('GET', '/', \Controllers\IndexController::class);

$dispatcher->addRoute('POST', '/user/signup', \Controllers\UserController::class, 'signup');
$dispatcher->addRoute('POST', '/user/signin', \Controllers\UserController::class, 'signin');
$dispatcher->addRoute('GET', '/user/signout', \Controllers\UserController::class, 'signout');


//$dispatcher->addRoute('GET', '/item/{itemId:[0-9]}/{categoryId:[0-9]}', \Controllers\IndexController::class);