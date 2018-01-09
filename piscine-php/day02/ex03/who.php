#!/usr/bin/php
<?php
// Global
date_default_timezone_set('Europe/Paris');

// File
$file = fopen("/var/run/utmpx", "r");

// Read the file
while ($utmpx = fread($file, 628)) {
    $unpack = unpack("a256a/a4b/a32c/id/ie/I2f/a256g/i16h", $utmpx);
    $users[$unpack['c']] = $unpack;
}

// Sorting by keys
ksort($users);

// Display
foreach ($users as $user){
    if ($user['e'] !== 7)
        continue;
    // Display user
    echo str_pad(substr(trim($user['a']), 0, 8), 9);
    // Display type
    echo str_pad(substr(trim($user['c']), 0, 8), 9);
    // Log time
    echo str_pad(date("M", $user["f1"]), 5);
    echo date("j H:i", $user["f1"]);
    echo "\n";
}