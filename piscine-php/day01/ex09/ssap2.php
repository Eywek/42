#!/usr/bin/php
<?php
// Parsing
$array = array_slice($argv, 1);
$words = [];
foreach ($array as $el)
    foreach (explode(' ', trim(preg_replace('/ +/', ' ', $el))) as $e)
        $words[] = $e;

// Sorting alpha

usort($words, function ($a, $b) {
    return strcmp(strtolower($a), strtolower($b));
});
$words = array_values($words); // reset keys

// Display alpha
foreach ($words as $i => $word) {
    if (ctype_alpha($word))
        echo "$word\n";
}

// Display numeric
foreach ($words as $i => $word) {
    if (is_numeric($word))
        echo "$word\n";
}

// Others
foreach ($words as $i => $word) {
    if (!ctype_alpha($word) && !is_numeric($word))
        echo "$word\n";
}