<?php
include 'include/app.php';
includeHead();
?>

	<div id="content">
		<div class="hr"></div>
		<div id="up_link">
			<a href="./signin.php" title="to_signin"><div class="block-icon" id="connect-icon"><img class="icon" src="./img/user-2.png"><span style="display:block">Connexion</span></div></a>
			<a href="./signup.php" title="to_signup"><div class="block-icon" style="border-left: 1px solid #9A9A9A; border-right: 1px solid #9A9A9A;"><img class="icon" src="./img/pen.png"><span style="display:block">Inscription</span></div></a>
			<div class="block-icon"><a href="cart.php" title="Panier" style="text-decoration:none; color:inherit;"><img class="icon" src="./img/shopping-cart.png"><span style="display:block">Mon panier</span></a></div>
		</div>
		<div id="haut"><h1>Goodies World</h1></div>
		<div class="hr"></div>
		<div id="menu">
			<ul id="menu">
				<a href="./index.php" title="Accueil" ><li>Accueil</li></a>
				<a href="http://www.google.com" title="Google" ><li>Mon compte</li></a>
				<a href="http://www.google.com" title="Google" ><li>Lien3</li></a>
				<a href="http://www.google.com" title="Google" ><li>Lien4</li></a>
				<a href="http://www.google.com" title="Google" ><li>Lien5</li></a>
				<a href="http://www.google.com" title="Google" ><li>Lien6</li></a>
			</ul>
		</div>
		<div class="hr"></div>
		<div id="milieu">
			Ici seront affichés les meilleurs articles<br />
		</div>
		<div class="hr"></div>
<?php
includeFooter();
?>
		
