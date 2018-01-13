<?php
/*
 * Globals
 */

session_start();
define('DS', DIRECTORY_SEPARATOR);
define('INCLUDE_DIR', realpath('../include'));
define('MODEL_DIR', realpath(__DIR__ . DS . '..' . DS . 'model') . DS);

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

/*
 * Models
 */

function loadModel($name)
{
    require_once MODEL_DIR . "$name.php";
}