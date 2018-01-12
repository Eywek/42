<?php

include_once('IFighter.class.php');
include_once('NightsWatch.class.php');

class JonSnow implements IFighter {
	public function fight() {
		print("* looses his wolf on the enemy, and charges with courage *" . PHP_EOL);
	}
	public function isABastard() {
		return True;
	}
}

class MaesterAemon {
	public function sendRavens() {
		print("* sends a raven carrying an important message *" . PHP_EOL);
	}
}

class SamwellTarly implements IFighter {
	public function fight() {
		print("* flees, finds a girl, grows a spine, and defends her to the bitter end *" . PHP_EOL);
	}
	public function makeHisFatherProud() {
		return False;
	}
}

$jon = new JonSnow();
$aemon = new MaesterAemon();
$sam = new SamwellTarly();
$nw = new NightsWatch();

$nw->recruit($jon);
$nw->recruit($aemon);
$nw->recruit($sam);

$nw->fight();

?>
