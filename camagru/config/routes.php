<?php
$dispatcher->addRoute('GET', '/', \Controllers\IndexController::class);

$dispatcher->addRoute('POST', '/user/signup', \Controllers\UserController::class, 'signup');

//$dispatcher->addRoute('GET', '/item/{itemId:[0-9]}/{categoryId:[0-9]}', \Controllers\IndexController::class);