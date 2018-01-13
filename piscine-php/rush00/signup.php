<?php
include 'include/app.php';
loadModel('user');

if (getUser())
    header('Location: index.php');
if ($_POST) {
    $signup = signup($_POST);
    if (is_int($signup))
    {
        // Login
        login($signup);
        // Redirect
        header('Location: index.php');
    } else
        $error = $signup;
}

$title = 'Inscription';
includeHead();
?>
    <div id="content">
        <div class="hr"></div>
        <div id="up_link">
            <a href="./signin.php" title="to_signin"><div class="block-icon" id="connect-icon"><img class="icon" src="./img/user-2.png"><span style="display:block">Connexion</span></div></a>
            <a href="./signup.php" title="to_signup"><div class="block-icon" style="border-left: 1px solid #9A9A9A; border-right: 1px solid #9A9A9A;"><img class="icon" src="./img/pen.png"><span style="display:block">Inscription</span></div></a>
            <div class="block-icon"><a href="cart.php" title="Panier" style="text-decoration:none; color:inherit;"><img class="icon" src="./img/shopping-cart.png"><span style="display:block">Mon panier</span></a></div>
        </div>
        <div id="haut"><h1>Inscription &agrave; Goodies World</h1></div>
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
            <?php
                 if (isset($error))
                    echo "<div class='alert alert-error'><b>Erreur :</b> $error</div>";
            ?>
            <form action="connexion.php" method="get">
            <label for="first_name">Prénom</label><input type="text" name="first_name" placeholder="Votre prénom" value="<?= isset($_POST['first_name']) ? $_POST['first_name'] : '' ?>"><br />
            <label for="name">Nom</label><input type="text" name="name" placeholder="Votre nom" value="<?= isset($_POST['name']) ? $_POST['name'] : '' ?>"><br />
            <label for="email">Email</label><input type="email" name="email" placeholder="Entrez un email valide" value="<?= isset($_POST['email']) ? $_POST['email'] : '' ?>"><br />
            <label for="password">Mot de passe</label><input type="password" name="password" placeholder="Votre mot de passe" value="<?= isset($_POST['password']) ? $_POST['password'] : '' ?>"><br />
            <label for="password_confirmation">Confirmation du mot de passe</label><input type="password" name="password_confirmation" placeholder="Répéter votre mot de passe" value="<?= isset($_POST['password_confirmation']) ? $_POST['password_confirmation'] : '' ?>"><br />
            <input type="submit" name="submit" value="M'inscrire"/><br />
            </form>
        </div>
        <div class="hr"></div>

<?php
includeFooter();
?>
