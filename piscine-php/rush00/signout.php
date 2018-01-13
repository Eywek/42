<?php
require 'include/app.php';
loadModel('user');
logout();

header('Location: index.php');