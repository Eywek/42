#!/usr/bin/php
<?php
$array = array_slice($argv, 1);
$words = [];
foreach ($array as $el)
    foreach (explode(' ', trim(preg_replace('/ +/', ' ', $el))) as $e)
        $words[] = $e;
sort($words);
foreach ($words as $word)
    echo "$word\n";