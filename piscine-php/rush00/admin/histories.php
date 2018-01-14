<?php
require '../include/app.php';
redirectIfNotAdmin();

$orders = queryDB('SELECT `users`.`email`, `items`.`name`, `items`.`price`, `orders`.`created_at`, `orders`.`address`, `orders`.`quantity` FROM `orders` INNER JOIN `items` ON `items`.`id` = `orders`.`item_id` INNER JOIN `users` ON `users`.`id` = `orders`.`user_id` ORDER BY `orders`.`id` DESC');

includeAdminHead();
?>

<div class="container">

    <h1>Historique d'achats</h1>

    <table class="table">
        <thead>
        <tr>
            <th>Article</th>
            <th>Prix</th>
            <th>Utilisateur</th>
            <th>Adresse</th>
            <th>Date</th>
        </tr>
        </thead>
        <tbody>
        <?php
        foreach ($orders as $order) {
            echo '<tr>';
            echo '<td>x' . $order['quantity']. ' ' . $order['name'] . '</td>';
            echo '<td>' . $order['price'] . '</td>';
            echo '<td>' . $order['email'] . '</td>';
            echo '<td>' . $order['address'] . '</td>';
            echo '<td>' . $order['created_at'] . '</td>';
            echo '</tr>';
        }
        ?>
        </tbody>
    </table>

</div>

<?php
includeAdminFooter();
?>