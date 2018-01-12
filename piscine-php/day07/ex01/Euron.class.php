<?php

include('Greyjoy.class.php');

class Euron extends Greyjoy {
	public function announceMotto() {
		print($this->familyMotto . PHP_EOL);
	}
}

?>
