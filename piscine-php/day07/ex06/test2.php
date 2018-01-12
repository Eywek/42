<?php

include_once('UnholyFactory.class.php');
include_once('Fighter.class.php');

class CrippledSoldier extends Fighter {
	public function __construct() {
		parent::__construct("crippled soldier");
	}
}

$uf = new UnholyFactory();
$uf->absorb(new CrippledSoldier());

$requested_fighters = Array(
	"crippled soldier",
	"crippled soldier",
	"crippled soldier",
	"crippled soldier",
);

$actual_fighters = Array(
);

foreach ($requested_fighters as $rf) {
	$f = $uf->fabricate($rf);
	if ($f != null) {
		array_push($actual_fighters, $f);
	}
}

$targets = Array("the Hound", "Tyrion", "Podrick");

foreach ($actual_fighters as $f) {
	foreach ($targets as $t) {
		$f->fight($t);
	}
}
