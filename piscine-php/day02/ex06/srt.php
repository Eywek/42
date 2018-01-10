#!/usr/bin/php
<?php
if ($argc < 2)
    exit(1);
if (!file_exists($argv[1]))
    exit(1);
$content = file_get_contents($argv[1]);
$lines = explode("\n\n", $content);
$times = [];
foreach ($lines as $line) {
    $line = explode("\n", $line);
    $time = $line[1];
    $time = substr($time, 0, 12);
    $times[$time] = [
        'time' => $line[1],
        'text' => $line[2]
    ];
}
ksort($times);
$i = 1;
$count = count($times);
foreach ($times as $time => $data) {
    echo $i++ . "\n";
    echo $data['time'] . "\n";
    echo $data['text'] . "\n";
    if ($i - 1 < $count)
        echo "\n";
}