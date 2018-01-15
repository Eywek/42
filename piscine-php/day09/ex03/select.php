<?php
$file = file_get_contents('data.csv');
$data = explode("\n", $file);
$list = [];
foreach ($data as $datum) {
    $datum = explode(';', $datum);
    if (count($datum) != 2)
        break;
    $list[$datum[0]] = $datum[1];
}
echo json_encode(['list' => $list]);