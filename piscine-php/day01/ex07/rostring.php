#!/usr/bin/php
<?php
if ($argc < 2)
    exit;
$words = explode(' ', trim(preg_replace('/ +/', ' ', $argv[1])));
$first = $words[0];
$words = array_slice($words, 1);
$words[] = $first;
echo implode(' ', $words);
if (count($words) > 0)
    echo "\n";