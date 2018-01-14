<?php
require '../include/app.php';
redirectIfNotAdmin();
if (!isset($_GET['id']))
{
    header('Location: users.php');
    exit();
}
$user = queryDB('SELECT * FROM `users` WHERE `id` = ?', ['i', $_GET['id']]);
if (empty($user))
{
    header('Location: users.php');
    exit();
}
$user = $user[0];

if ($_POST) {
    $edit = edit($_POST, $_GET['id']);
    if ($edit === true)
    {
        if ($_POST['is_admin'])
            queryDB('UPDATE `users` SET `is_admin` = 1 WHERE `id` = ?', ['i', $_GET['id']]);
        else
            queryDB('UPDATE `users` SET `is_admin` = 0 WHERE `id` = ?', ['i', $_GET['id']]);
        // Redirect
        header('Location: users.php');
    } else
        $error = $edit;
}

includeAdminHead();
?>

<div class="container">

    <h1>Éditer un utilisateur</h1>

    <?php
    if (isset($error))
        echo "<div class='alert alert-error'><b>Erreur :</b> $error</div>";
    ?>

    <form action="" method="post">

        <div class="form-group">
            <label>Prénom</label>
            <input type="text" name="first_name" value="<?= $user['first_name'] ?>">
        </div>

        <div class="form-group">
            <label>Nom</label>
            <input type="text" name="name" value="<?= $user['name'] ?>">
        </div>

        <div class="form-group">
            <label>Email</label>
            <input type="email" name="email" value="<?= $user['email'] ?>">
        </div>

        <div class="form-group">
            <label>Mot de passe</label>
            <input type="password" name="password" placeholder="Laisser vider pour ne pas éditer">
        </div>

        <div class="form-group">
            <label>Mot de passe (confirmation)</label>
            <input type="password" name="password_confirmation" placeholder="Laisser vider pour ne pas éditer">
        </div>

        <div class="form-group">
            <label>
                <input type="checkbox" name="is_admin" <?= ($user['is_admin'] ? 'checked' : '') ?>>
                Administrateur
            </label>
        </div>

        <br>

        <button class="button button-info" type="submit">Sauvegarder</button>

    </form>

</div>

<?php
includeAdminFooter();
?>
