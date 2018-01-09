#!/usr/bin/php
<?php
if ($argc < 2)
    exit(0);
if (!in_array($argv[1], ['moyenne', 'moyenne_user', 'ecart_moulinette']))
    exit(0);
// Read
$file = fopen('php://stdin', 'r');
if (!$file)
    exit(0);
$line = fgetcsv($file, 0, ';');

// Functions
function displayAverage($file)
{
    $count = 0;
    $total = 0;
    while ($line = fgetcsv($file, 0, ';')) {
        if ($line[2] != 'moulinette') {
            $total += $line[1];
            if ($line[1] !== "")
                ++$count;
        }
    }
    echo $total / $count . "\n";
}
function getUserAverage($file)
{
    $count = [];
    $total = [];
    $moulinette = [];
    while ($line = fgetcsv($file, 0, ';')) {
        if ($line[2] != 'moulinette') {
            if (!isset($total[$line[0]])) {
                $total[$line[0]] = 0;
                $count[$line[0]] = 0;
            }
            $total[$line[0]] += $line[1];
            if ($line[1] !== "")
                ++$count[$line[0]];
        } else {
            if (!isset($moulinette[$line[0]]))
                $moulinette[$line[0]] = 0;
            if ($line[1] !== "")
                $moulinette[$line[0]] = $line[1];
        }
    }
    ksort($total);
    foreach ($total as $user => $value)
        $total[$user] = $value / $count[$user];
    return [$total, $moulinette];
}
function displayUserAverage($file)
{
    $total = getUserAverage($file)[0];
    foreach ($total as $user => $value) {
        echo "$user:$value\n";
    }
}
function displayMoulinette($file)
{
    list($total, $moulinette) = getUserAverage($file);
    foreach ($total as $user => $value) {
        if (!isset($moulinette[$user]))
            $moulinette[$user] = 0;
        echo "$user:" . ($value - $moulinette[$user]) . "\n";
    }
}

switch ($argv[1]) {
    case 'moyenne':
        displayAverage($file);
        break;
    case 'moyenne_user':
        displayUserAverage($file);
        break;
    case 'ecart_moulinette':
        displayMoulinette($file);
        break;
}