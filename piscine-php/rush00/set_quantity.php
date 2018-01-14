<?php
require 'include/app.php';
loadModel('item');


function render($status)
{
	if (!isset($_GET['redirect']))
		exit(json_encode(['status' => $status]));
	header('Location: cart.php');
	exit();
}

if (!isset($_GET['id']) || !isset($_GET['quantity']))
    render(false);
$item = queryDB('SELECT `id` FROM `items` WHERE `id` = ?', ['i', $_GET['id']]);
if (empty($item))
    render(false);

setQuantity($item[0]['id'], intval($_GET['quantity']));
render(true);