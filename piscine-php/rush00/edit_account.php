<?php
include 'include/app.php';
redirectIfNotLogged();
$user = getUser();

if ($_POST) {
    $edit = edit($_POST);
    if ($edit === true)
    {
        // Redirect
        header('Location: account.php');
    } else
        $error = $edit;
}

$title = "Modifier mon compte";
includeHead();
?>
	        <div class="hr"></div>
        <div id="milieu">
            <?php
                 if (isset($error))
                    echo "<div class='alert alert-error'><b>Erreur :</b> $error</div>";
            ?>
            <form action="" method="post">
            <label for="first_name">Prénom</label><input type="text" name="first_name" placeholder="Votre prénom" value="<?= $user['first_name'] ?>"><br />
            <label for="name">Nom</label><input type="text" name="name" placeholder="Votre nom" value="<?= $user['name'] ?>"><br />
            <label for="email">Email</label><input type="email" name="email" placeholder="Entrez un email valide" value="<?= $user['email'] ?>"><br />
            <label for="password">Mot de passe</label><input type="password" name="password" placeholder="Votre mot de passe" value=""><br />
            <label for="password_confirmation">Confirmation du mot de passe</label><input type="password" name="password_confirmation" placeholder="Répéter votre mot de passe" value=""><br />
            <input type="submit" name="submit" value="Confirmer"/><br />
            </form>
        </div>
        <div class="hr"></div>

<?php
includeFooter();
?>
