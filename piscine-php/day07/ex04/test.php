<?php

include_once('Lannister.class.php');
include_once('Jaime.class.php');
include_once('Tyrion.class.php');

class Stark {
}

class Cersei extends Lannister {
}

class Sansa extends Stark {
}

$j = new Jaime();
$c = new Cersei();
$t = new Tyrion();
$s = new Sansa();

$j->sleepWith($t);
$j->sleepWith($s);
$j->sleepWith($c);

$t->sleepWith($j);
$t->sleepWith($s);
$t->sleepWith($c);

?>
