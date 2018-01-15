<?php
if (!isset($_POST['message']))
    exit();
$value = htmlentities($_POST['message']);

$file = file_get_contents('data.csv');
$data = explode("\n", $file);
$list = [];
$lastId = 0;
foreach ($data as $datum) {
    $datum = explode(';', $datum);
    if (count($datum) != 2)
        break;
    $lastId = $lastId < intval($datum[0]) ? intval($datum[0]) : $lastId;
}
++$lastId;

$data = array_merge(["$lastId;$value"], $data);
file_put_contents('data.csv', implode("\n", $data));

echo json_encode(['id' => $lastId]);