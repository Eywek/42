<?php
require '../include/app.php';
redirectIfNotAdmin();
if (isset($_GET['id']))
{
    $item = queryDB('SELECT * FROM `items` WHERE `id` = ?', ['i', $_GET['id']]);
    if (empty($item))
    {
        header('Location: users.php');
        exit();
    }
    $item = $item[0];
    $itemCategories = array_map(function ($category) {
        return $category['category_id'];
    }, queryDB('SELECT `category_id` FROM `items_categories` WHERE `item_id` = ?', ['i', $item['id']]));
}
$categories = queryDB('SELECT `id`, `name` FROM `categories`');

if ($_POST) {
    if (($validate = validate([
        'name' => [
            'name' => 'Nom',
            'rules' => ['not_empty', 'min_length' => 3, 'max_length' => 255]
        ],
        'price' => [
            'name' => 'Prix',
            'rules' => ['not_empty', 'is_numeric']
        ],
        'description' => [
            'name' => 'Description',
            'rules' => ['not_empty', 'min_length' => 20, 'max_length' => 1500]
        ],
        'image_url' => [
            'name' => 'URL d\'image',
            'rules' => ['not_empty', 'url']
        ],
        'categories' => [
            'name' => 'Catégories',
            'rules' => ['not_empty', 'in' => array_map(function ($category) {
                return $category['id'];
            }, $categories)]
        ]
    ], $_POST)) === true)
    {
        // Handle item
        if (isset($_GET['id'])) {
            queryDB('UPDATE `items` SET `name` = ?, `price` = ?, `description` = ?, `image_url` = ? WHERE `id` = ?', ['sdssi', sanitize($_POST['name']), $_POST['price'], sanitize($_POST['description']), sanitize($_POST['image_url']), $_GET['id']]);
            $itemId = $_GET['id'];
        } else {
            queryDB('INSERT INTO `items` SET `name` = ?, `price` = ?, `description` = ?, `image_url` = ?, `created_at` = ?', ['sdsss', sanitize($_POST['name']), $_POST['price'], sanitize($_POST['description']), sanitize($_POST['image_url']), date('Y-m-d H:i:s')]);
            $itemId = mysqli_insert_id($db);
        }

        // Handle categories
        queryDB('DELETE FROM `items_categories` WHERE `item_id` = ?', ['i', $itemId]);
        foreach ($_POST['categories'] as $category)
            queryDB('INSERT INTO `items_categories` SET `item_id` = ?, `category_id` = ?, `created_at` = ?', ['iis', $itemId, $category, date('Y-m-d H:i:s')]);

        // Redirect
        header('Location: items.php');
    } else
        $error = $validate;
}

includeAdminHead();
?>

<div class="container">

    <h1><?= (isset($item) ? 'Éditer' : 'Ajouter') ?> un article</h1>

    <?php
    if (isset($error))
        echo "<div class='alert alert-error'><b>Erreur :</b> $error</div>";
    ?>

    <form action="" method="post">

        <div class="form-group">
            <label>Nom</label>
            <input type="text" name="name" value="<?= displayPost('name', isset($item) ? $item['name'] : '') ?>">
        </div>

        <div class="form-group">
            <label>Description</label>
            <textarea rows="5" name="description"><?= displayPost('description', isset($item) ? $item['description'] : '') ?></textarea>
        </div>

        <div class="form-group">
            <label>Prix</label>
            <input type="number" step="0.01" name="price" value="<?= displayPost('price', isset($item) ? $item['price'] : '') ?>">
        </div>

        <div class="form-group">
            <label>URL d'image</label>
            <input type="text" name="image_url" value="<?= displayPost('image_url', isset($item) ? $item['image_url'] : '') ?>">
        </div>

        <div class="form-group">
            <label>Catégories</label>
            <select name="categories[]" multiple>
                <?php
                foreach ($categories as $category) {
                    echo '<option value="' . $category['id'] . '" ' . (isset($item) && in_array($category['id'], $itemCategories) ? 'selected' : '') . '>' . $category['name'] . '</option>';
                }
                ?>
            </select>
        </div>

        <br>

        <button class="button button-info" type="submit">Sauvegarder</button>

    </form>

</div>

<?php
includeAdminFooter();
?>
