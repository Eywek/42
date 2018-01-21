<?php
session_start();
date_default_timezone_set('Europe/Paris');

// GLOBALS
if (!defined('REWRITE_URL'))
    define('REWRITE_URL', true);
if (!defined('DS'))
    define('DS', DIRECTORY_SEPARATOR);
if (!defined('ROOT'))
    define('ROOT', realpath(__DIR__ . DS . '..') . DS);
define('PUBLIC_PATH', ROOT . 'public' . DS);
define('APP_PATH', ROOT . 'app' . DS);
define('VIEW_PATH', APP_PATH . 'Views' . DS);
define('CONFIG_PATH', ROOT . 'config' . DS);

// GLOBALS FUNCTIONS
require APP_PATH . 'Functions' . DS . 'debug.php';
require APP_PATH . 'Functions' . DS . 'security.php';
require APP_PATH . 'Functions' . DS . 'utils.php';

// AUTOLOAD
require APP_PATH . 'Core' . DS . 'Autoloader.class.php';
\Core\Autoloader::register();

// HANDLE REQUEST
$dispatcher = new \Routing\Dispatcher(new \Routing\Request($_GET['path'] ?? '/', $_SERVER['REQUEST_METHOD'], @json_decode(@file_get_contents('php://input'), true)), new \Routing\Response());

$dispatcher->addErrorHandler(404, function (\Routing\Request $req) {
   echo $req->getPath() . ' not found!';
});
$dispatcher->addErrorHandler(500, function (\Routing\Request $req) {
    echo $req->getPath() . ' internal error!';
});
$dispatcher->addErrorHandler(403, function (\Routing\Request $req) {
    echo $req->getPath() . ' forbidden!';
});
$dispatcher->addErrorHandler(400, function (\Routing\Request $req) {
    echo $req->getPath() . ' bad request!';
});

require CONFIG_PATH . 'routes.php';

$dispatcher->dispatch();