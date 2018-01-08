#!/usr/bin/php
<?php
// Global
date_default_timezone_set('Europe/Paris');

// Parsing
$preg = preg_match('/(Lundi|Mardi|Mercredi|Jeudi|Vendredi|Samedi|Dimanche) ([0-9]|1[0-9]|2[0-9]|3[0-1]) (Janvier|Fevrier|Mars|Avril|Mai|Juin|Juillet|Aout|Septembre|Octobre|Novembre|Decembre) ([0-9]{4}) (([01][0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9]))/i', $argv[1], $matches);

// Get month
$months = ['janvier', 'fevrier', 'mars', 'avril', 'mai', 'juin', 'juillet', 'aout', 'septembre', 'octobre', 'novembre', 'decembre'];
$month = ($month = array_search(strtolower($matches[3]), $months)) ? $month + 1 : false;
if (!$month)
{
    echo "Wrong Format\n";
    exit;
}

// Setup time
$time = $matches[4] . '-' . $month . '-' . $matches[2] . ' ' . $matches[5];
$time = strtotime($time);

// Display
if (!$time || !$preg)
    echo "Wrong Format\n";
else
    echo $time . "\n";
