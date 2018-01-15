<?php
if (!isset($_POST['id']))
    exit();

$file = file_get_contents('data.csv');
$data = explode("\n", $file);
$list = [];
foreach ($data as $datum) {
    $explode = explode(';', $datum);
    if ($explode[0] == $_POST['id'])
        continue;
    if (count($explode) != 2)
        break;
    $list[] = $datum;
}
file_put_contents('data.csv', implode("\n", $list));