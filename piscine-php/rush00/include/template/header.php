<?php
loadModel('item');
?>
<!DOCTYPE html>
<html lang ="fr">
<head>
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Goodies World</title>
	<link rel="stylesheet" type="text/css" href="assets/css/style.css">
    <link rel="stylesheet" href="assets/font-awesome-4.7.0/css/font-awesome.min.css">
</head>
<body>
    <div id="content">
        <div class="hr"></div>
        <div id="up_link">
            <?php if (!getUser()): ?>
                <a href="./signin.php" title="to_signin"><div class="block-icon" id="connect-icon"><img class="icon" src="assets/img/user-2.png"><span style="display:block">Connexion</span></div></a>
                <a href="./signup.php" title="to_signup"><div class="block-icon" style="border-left: 1px solid #9A9A9A; border-right: 1px solid #9A9A9A;"><img class="icon" src="assets/img/pen.png"><span style="display:block">Inscription</span></div></a>
            <?php else: ?>
                <a href="./account.php" title="to_signup"><div class="block-icon" style="border-right: 1px solid #9A9A9A;"><img class="icon" src="assets/img/user-2.png"><span style="display:block">Mon compte</span></div></a>
                <a href="./signout.php" title="to_signup"><div class="block-icon" style="border-right: 1px solid #9A9A9A;"><img class="icon" src="assets/img/user-2.png"><span style="display:block">Se déconnecter</span></div></a>
            <?php endif; ?>
            <div class="block-icon"><a href="cart.php" title="Panier" style="text-decoration:none; color:inherit;"><img class="icon" src="assets/img/shopping-cart.png"><span style="display:block">Mon panier</span></a></div>
        </div>
        <div id="haut">
            <h1><a href="index.php">Goodies World</a></h1>
        </div>
        <div class="hr"></div>
        <div id="menu">
            <ul id="menu">
                <?php
                foreach (getItemCategories() as $category) {
                    echo "<a href=\"index.php?category=$category\"><li>$category</li></a>";
                }
                ?>
            </ul>
        </div>