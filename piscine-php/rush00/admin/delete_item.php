<?php
require '../include/app.php';
redirectIfNotAdmin();
if (!isset($_GET['id']))
{
    header('Location: items.php');
    exit();
}
queryDB('DELETE FROM `items` WHERE `id` = ?', ['i', $_GET['id']]);
header('Location: items.php');
