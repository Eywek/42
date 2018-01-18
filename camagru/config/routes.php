<?php
$dispatcher->addRoute('GET', '/{custom:.+}', \Controllers\IndexController::class);
$dispatcher->addRoute('GET', '/item/{itemId:[0-9]}/{categoryId:[0-9]}', \Controllers\IndexController::class);