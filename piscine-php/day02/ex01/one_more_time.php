#!/usr/bin/php
<?php
if ($argc < 2)
    exit(0);

// Global
date_default_timezone_set('Europe/Paris');

// Parsing
$preg = preg_match('/^([Ll]undi|[Mm]ardi|[Mm]ercredi|[jJ]eudi|[vV]endredi|[sS]amedi|[dD]imanche) ([0-9]|1[0-9]|2[0-9]|3[0-1]) ([jJ]anvier|[fF]evrier|[mM]ars|[aA]vril|[mM]ai|[jJ]uin|[jJ]uillet|[aA]out|[sS]eptembre|[oO]ctobre|[nN]ovembre|[dD]ecembre) ([0-9]{4}) (([01][0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9]))$/', $argv[1], $matches);
if (!$preg)
	exit("Wrong Format\n");

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
