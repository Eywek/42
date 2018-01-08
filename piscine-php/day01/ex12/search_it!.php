#!/usr/bin/php
<?php
if ($argc < 3)
    exit(0);
$key = $argv[1];
$array = [];

$elements = array_slice($argv, 2);
foreach ($elements as $element) {
    $element = explode(':', $element);
    if (count($element) != 2)
        continue;
    $array[$element[0]] = $element[1]; // key:value -> [key => value]
}

if (isset($array[$key]))
    echo "{$array[$key]}\n";