<?php
/*
 * Globals
 */

session_start();
define('DS', DIRECTORY_SEPARATOR);
define('INCLUDE_DIR', realpath(__DIR__) . DS);
define('MODEL_DIR', realpath(__DIR__ . DS . '..' . DS . 'model') . DS);
define('CONFIG_DIR', realpath(__DIR__ . DS . '..' . DS . 'config') . DS);

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

function displayPost($name)
{
    return (isset($_POST[$name])) ? $_POST[$name] : '';
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