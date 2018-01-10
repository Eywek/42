#!/usr/bin/php
<?php
if ($argc < 3)
    exit(1);
if (!file_exists($argv[1]))
    exit(1);
$file = fopen($argv[1], 'r');
if (!$file)
    exit(1);
$line = fgetcsv($file, 0, ';');
if (!in_array($argv[2], $line))
    exit(1);
$key = $argv[2];

// Set vars
$vars = $line;
$varsList = [];
foreach ($line as $var)
    $varsList[$var] = [];

while ($line = fgetcsv($file, 0, ';')) {
    foreach ($line as $index => $value)
        $varsList[$vars[$index]][$line[array_search($key, $vars)]] = $value;
}
extract($varsList);

// Waiting commands
while (42)
{
    echo "Entrez votre commande : ";
    $fd = fopen("php://stdin","r");
    $line = fgets($fd);
    if (!$line)
        break;
    $code = trim($line);
    fclose($fd);
    eval($code);
}
