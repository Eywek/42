<?php
include 'include/app.php';

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
        <div class="hr"></div>
        <div id="milieu">
            <?php
                 if (isset($error))
                    echo "<div class='alert alert-error'><b>Erreur :</b> $error</div>";
            ?>
            <form action="" method="post">
                <br><label for="first_name">Prénom</label><input type="text" name="first_name" placeholder="Votre prénom" value="<?= displayPost('first_name') ?>"><br />
                <br><label for="name">Nom</label><input type="text" name="name" placeholder="Votre nom" value="<?= displayPost('name') ?>"><br />
                <br><label for="email">Email</label><input type="email" name="email" placeholder="Entrez un email valide" value="<?= displayPost('email') ?>"><br />
                <br><label for="password">Mot de passe</label><input type="password" name="password" placeholder="Votre mot de passe" value="<?= displayPost('password') ?>"><br />
                <br><label for="password_confirmation">Confirmation du mot de passe</label><input type="password" name="password_confirmation" placeholder="Répéter votre mot de passe" value="<?= displayPost('password_confirmation') ?>"><br />
                <br><button type="submit" class="button">M'inscrire</button><br /><br>
            </form>
        </div>
        <div class="hr"></div>

<?php
includeFooter();
?>
