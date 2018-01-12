<?php
/*
 * Globals
 */

session_start();
define('DS', DIRECTORY_SEPARATOR);
define('INCLUDE_DIR', realpath('.') . DS);
define('MODEL_DIR', realpath('../model') . DS);

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