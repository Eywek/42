<?php
if (!defined('CONFIG_PATH'))
    define('CONFIG_PATH', realpath('.') . '/');

$installed = CONFIG_PATH . 'installed';
if (file_exists($installed))
    exit('NOPE');
require_once '../app/Models/Database.class.php';

$sql = CONFIG_PATH . 'camagru.sql';
\Models\Database::getPDO()->query(file_get_contents($sql));

file_put_contents($installed, '1');

echo 'OK';