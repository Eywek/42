#!/usr/bin/php
<?php
// date
date_default_timezone_set("Europe/Paris");

// file
$fd = fopen("/var/run/utmpx", "r");
$users = array();
while ($line = fread($fd, 628)) {
	$line = unpack("a256user/a4id/a32line/ipid/itype/I2time", $line);
	if (strcmp($line['type'], "7") == 0)
		$users[] = $line;
}

// sorting
usort($users, function ($a, $b) {
	if ($a['user'] == $b['user']) {
		if ($a['line'] == $b['line'])
			return 0;
		return ($a['line'] < $b['line']) ? -1 : 1;
	}
	return ($a['user'] < $b['user']) ? -1 : 1;
});

// size
$maxSize = 0;
foreach ($users as $user) {
	$calcul = strlen(preg_replace('/[\x00-\x1F\x80-\xFF]/', '', $user['user']));
	$maxSize = ($calcul > $maxSize) ? $calcul : $maxSize;
}

// display
foreach ($users as $user) {
	$user['user'] = preg_replace('/[\x00-\x1F\x80-\xFF]/', '', $user['user']);
	$user['line'] = preg_replace('/[\x00-\x1F\x80-\xFF]/', '', $user['line']);
	printf("%s %s  %s \n", str_pad($user['user'], $maxSize), $user['line'], date("M j H:i", $user['time1']));
}
