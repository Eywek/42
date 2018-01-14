<?php
require '../include/app.php';
redirectIfNotAdmin();
if (isset($_GET['id']))
{
    $category = queryDB('SELECT * FROM `categories` WHERE `id` = ?', ['i', $_GET['id']]);
    if (empty($category))
    {
        header('Location: users.php');
        exit();
    }
    $category = $category[0];
}

if ($_POST) {
    if (($validate = validate([
        'name' => [
            'name' => 'Nom',
            'rules' => ['not_empty', 'min_length' => 3, 'max_length' => 255]
        ]], $_POST)) === true)
    {
        if (isset($_GET['id']))
            queryDB('UPDATE `categories` SET `name` = ? WHERE `id` = ?', ['si', sanitize($_POST['name']), $_GET['id']]);
        else
            queryDB('INSERT INTO `categories` SET `name` = ?, `created_at` = ?', ['ss', sanitize($_POST['name']), date('Y-m-d H:i:s')]);
        // Redirect
        header('Location: items.php');
    } else
        $error = $validate;
}

includeAdminHead();
?>

<div class="container">

    <h1><?= (isset($category) ? 'Éditer' : 'Ajouter') ?> une catégorie</h1>

    <?php
    if (isset($error))
        echo "<div class='alert alert-error'><b>Erreur :</b> $error</div>";
    ?>

    <form action="" method="post">

        <div class="form-group">
            <label>Nom</label>
            <input type="text" name="name" value="<?= (isset($category) ? $category['name'] : '') ?>">
        </div>

        <br>

        <button class="button button-info" type="submit">Sauvegarder</button>

    </form>

</div>

<?php
includeAdminFooter();
?>
