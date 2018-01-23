<?php
define('DS', DIRECTORY_SEPARATOR);
define('ROOT', realpath(__DIR__) . DS);
define('REWRITE_URL', false);

require ROOT . 'public' . DS . 'index.php';
