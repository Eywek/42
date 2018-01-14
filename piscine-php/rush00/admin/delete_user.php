<?php
require '../include/app.php';
redirectIfNotAdmin();
if (!isset($_GET['id']))
{
    header('Location: users.php');
    exit();
}
deleteUser(intval($_GET['id']));
header('Location: users.php');