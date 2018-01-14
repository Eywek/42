<?php
require 'include/app.php';
loadModel('item');

if (!isset($_GET['id']))
    exit(json_encode(['status' => false]));
$item = queryDB('SELECT `id` FROM `items` WHERE `id` = ?', ['i', $_GET['id']]);
if (empty($item))
    exit(json_encode(['status' => false]));

addToCart($item[0]['id']);
exit(json_encode(['status' => true]));