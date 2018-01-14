<?php
require '../include/app.php';
redirectIfNotAdmin();

$items = queryDB('SELECT * FROM `items` ORDER BY `id` DESC;');
$categories = queryDB('SELECT * FROM `categories` ORDER BY `id` DESC;');

includeAdminHead();
?>
<?php
includeAdminFooter();
?>