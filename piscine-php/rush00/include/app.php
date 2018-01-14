<?php
/*
 * Globals
 */

date_default_timezone_set('Europe/Paris');
session_start();
define('DS', DIRECTORY_SEPARATOR);
define('ROOT', realpath(__DIR__) . DS . '..' . DS);
define('INCLUDE_DIR', realpath(__DIR__) . DS);
define('MODEL_DIR', realpath(__DIR__ . DS . '..' . DS . 'model') . DS);
define('CONFIG_DIR', realpath(__DIR__ . DS . '..' . DS . 'config') . DS);

if (!file_exists(ROOT . 'installed') && basename($_SERVER["SCRIPT_FILENAME"], '.php') != 'install') {
    header('Location: install.php');
    exit();
}

require 'functions.php';
require 'database.php';

/*
 * Templating
 */

function includeHead()
{
    include INCLUDE_DIR . 'template' . DS . 'header.php';
}

function includeFooter()
{
    include INCLUDE_DIR . 'template' . DS . 'footer.php';
}

function includeAdminHead()
{
    include INCLUDE_DIR . 'template' . DS . 'admin' . DS . 'header.php';
}

function includeAdminFooter()
{
    include INCLUDE_DIR . 'template' . DS . 'admin' . DS . 'footer.php';
}

function displayPost($name, $default = '')
{
    return (isset($_POST[$name])) ? $_POST[$name] : $default;
}

/*
 * Models
 */

function loadModel($name)
{
    require_once MODEL_DIR . "$name.php";
}

/*
 * Configuration
 */

function getConfig()
{
    return include(CONFIG_DIR . 'app.php');
}

/*
 * INIT
 */

loadModel('user');