<?php
include 'include/app.php';

if ($_POST) {
    loadModel('user');
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

<h1>Inscription</h1>

<?php
    if (isset($error))
            echo "<div class='alert alert-error'><b>Erreur :</b> $error</div>";
?>

<form action="" method="post">

    <div class="input-group-inline">
        <div class="input-group">
            <label for="first_name">Prénom</label>
            <input type="text" name="first_name" placeholder="Votre prénom">
        </div>

        <div class="input-group">
            <label for="name">Nom</label>
            <input type="text" name="name" placeholder="Votre nom">
        </div>
    </div>

    <div class="input-group">
        <label for="email">Email</label>
        <input type="email" name="email" placeholder="Entrez un email valide">
    </div>

    <div class="input-group-inline">
        <div class="input-group">
            <label for="password">Mot de passe</label>
            <input type="password" name="password" placeholder="Votre mot de passe">
        </div>

        <div class="input-group">
            <label for="password_confirmation">Confirmation du mot de passe</label>
            <input type="password" name="password_confirmation" placeholder="Répéter votre mot de passe">
        </div>
    </div>

    <button type="submit">M'inscrire</button>

</form>

<?php
includeFooter();
?>
