<?php
session_start();
require 'auth.php';

$_SESSION['loggued_on_user'] = "";
if (!$_POST || !isset($_POST['login']) || empty($_POST['login']) || !isset($_POST['passwd']) || empty($_POST['passwd']))
    exit("ERROR\n");
if (!auth($_POST['login'], $_POST['passwd']))
    exit("ERROR\n");
$_SESSION['loggued_on_user'] = $_POST['login'];
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>42chat</title>
</head>
<body>

    <h1>
        42chat
    </h1>

    <a href="logout.php" style="float: right">Se déconnecter</a>

    <iframe name="chat" src="chat.php" width="100%" height="550px"></iframe>
    <iframe name="speak" src="speak.php" width="100%" height="50px"></iframe>

    <script>
        setInterval(function () {
            frames['chat'].location = 'chat.php'
        }, 5000) // 5 sec
    </script>
</body>
</html>
