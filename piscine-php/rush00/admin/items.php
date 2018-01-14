<?php
require '../include/app.php';
redirectIfNotAdmin();

$items = queryDB('SELECT * FROM `items` ORDER BY `id` ASC;');
$categories = queryDB('SELECT * FROM `categories` ORDER BY `id` ASC;');

includeAdminHead();
?>

    <div class="container">

        <h1>Liste des articles</h1>

        <table class="table">
            <thead>
            <tr>
                <th>Nom</th>
                <th>Prix</th>
                <th>Date d'ajout</th>
                <th>Actions</th>
            </tr>
            </thead>
            <tbody>
                <?php
                foreach ($items as $item) {
                    echo '<tr>';
                        echo '<td>' . $item['name'] . '</td>';
                        echo '<td>' . $item['price'] . '</td>';
                        echo '<td>' . $item['created_at'] . '</td>';
                        echo '<td>';
                            echo '<a class="button button-info" href="edit_item.php?id=' . $item['id'] . '">Éditer</a>&nbsp;';
                            echo '<a class="button button-danger" href="delete_item.php?id=' . $item['id'] . '">Supprimer</a>';
                        echo '</td>';
                    echo '</tr>';
                }
                ?>
                <tr>
                    <td></td>
                    <td></td>
                    <td></td>
                    <td>
                        <a class="button button-success" href="edit_item.php">Ajouter</a>
                    </td>
                </tr>
            </tbody>
        </table>

        <h1>Liste des catégories</h1>

        <table class="table">
            <thead>
            <tr>
                <th>Nom</th>
                <th>Date d'ajout</th>
                <th>Actions</th>
            </tr>
            </thead>
            <tbody>
            <?php
            foreach ($categories as $category) {
                echo '<tr>';
                echo '<td>' . $category['name'] . '</td>';
                echo '<td>' . $category['created_at'] . '</td>';
                echo '<td>';
                echo '<a class="button button-info" href="edit_category.php?id=' . $category['id'] . '">Éditer</a>&nbsp;';
                echo '<a class="button button-danger" href="delete_category.php?id=' . $category['id'] . '">Supprimer</a>';
                echo '</td>';
                echo '</tr>';
            }
            ?>
            <tr>
                <td></td>
                <td></td>
                <td>
                    <a class="button button-success" href="edit_category.php">Ajouter</a>
                </td>
            </tr>
            </tbody>
        </table>

    </div>

<?php
includeAdminFooter();
?>