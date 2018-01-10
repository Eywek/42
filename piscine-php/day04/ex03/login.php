<?php
session_start();
require 'auth.php';

$_SESSION['loggued_on_user'] = "";
if (!$_GET || !isset($_GET['login']) || empty($_GET['login']) || !isset($_GET['passwd']) || empty($_GET['passwd']))
    exit("ERROR\n");
if (!auth($_GET['login'], $_GET['passwd']))
    exit("ERROR\n");
$_SESSION['loggued_on_user'] = $_GET['login'];
echo "OK\n";