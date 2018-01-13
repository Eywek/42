<?php
include 'include/app.php';
loadModel('user');
if (getUser())
    header('Location: index.php');

if ($_POST) {
    if (($error = validate([
            'email' => [
                'name' => 'Email',
                'rules' => ['not_empty', 'min_length' => 2, 'max_length' => 255]
            ],
            'password' => [
                'name' => 'Mot de passe',
                'rules' => ['not_empty']
            ]
        ], $_POST)) === true) {
        $status = login($_POST['email'], $_POST['password'], 'email');
        if ($status) {
            header('Location: index.php');
            exit();
        }
        $error = 'Vos identifiants sont invalides.';
    }
}

includeHead();
?>
<div id="content">
		<div class="hr"></div>
		<div id="up_link">
			<a href="./signup.php" title="to_signup"><div class="block-icon" style="border-left: 1px solid #9A9A9A; border-right: 1px solid #9A9A9A;"><img class="icon" src="./img/pen.png"><span style="display:block">Inscription</span></div></a>
			<div class="block-icon"><a href="cart.php" title="Panier" style="text-decoration:none; color:inherit;"><img class="icon" src="./img/shopping-cart.png"><span style="display:block">Mon panier</span></a></div>
		</div>
		<div id="haut"><h1>Connexion &agrave; Goodies World</h1></div>
		<div class="hr"></div>
		<div id="menu">
			<ul id="menu">
				<a href="./index.php" title="Accueil" ><li>Accueil</li></a>
				<a href="http://www.google.com" title="Google" ><li>Mon compte</li></a>
				<a href="http://www.google.com" title="Google" ><li></li></a>
				<a href="http://www.google.com" title="Google" ><li>Lien4</li></a>
				<a href="http://www.google.com" title="Google" ><li>Lien5</li></a>
				<a href="http://www.google.com" title="Google" ><li>Lien6</li></a>
			</ul>
		</div>
		<div class="hr"></div>
		<div id="milieu">
            <?php
            if (isset($error))
                echo "<div class='alert alert-error'><b>Erreur :</b> $error</div>";
            ?>
			<form action="" method="post">
        	<label for="login">Email: </label><input type="email" name="email" placeholder="votre email"/><br />
        	<label for="password">Mot de passe: </label><input type="password" name="password" placeholder="votre mot de passe"/><br />
        	<input type="submit" name="submit" value="signin"/><br />
    </form>
		</div>
		<div class="hr"></div>
<?php
includeFooter();
?>