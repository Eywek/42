<?php
require '../include/app.php';
redirectIfNotAdmin();

$usersCount = queryDB('SELECT COUNT(`id`) AS `count` FROM `users`')[0]['count'];
$purchasesCount = queryDB('SELECT COUNT(`id`) AS `count` FROM `orders`')[0]['count'];
$profit = queryDB('SELECT SUM(`items`.`price` * `orders`.`quantity`) AS `sum` FROM `orders` INNER JOIN `items` ON `items`.`id` = `orders`.`item_id`');
if (empty($profit) || !isset($profit[0]['sum']))
    $profit = 0;
else
    $profit = $profit[0]['sum'];
$itemsCount = queryDB('SELECT COUNT(`id`) AS `count` FROM `items`')[0]['count'];

$orders = queryDB('SELECT `users`.`email`, `items`.`name`, `orders`.`created_at` FROM `orders` INNER JOIN `items` ON `items`.`id` = `orders`.`item_id` INNER JOIN `users` ON `users`.`id` = `orders`.`user_id` ORDER BY `orders`.`id` DESC LIMIT 15');

includeAdminHead();
?>

    <div class="container">

        <div class="block colored red">
            <i class="fa fa-users"></i>
            <span><?= $usersCount ?></span>
            utilisateurs
        </div>

        <div class="block colored green">
            <i class="fa fa-shopping-cart"></i>
            <span><?= $purchasesCount ?></span>
            ventes
        </div>

        <div class="block colored blue">
            <i class="fa fa-euro"></i>
            <span><?= $profit ?></span>
            profit
        </div>

        <div class="block colored yellow">
            <i class="fa fa-shopping-basket"></i>
            <span><?= $itemsCount ?></span>
            articles
        </div>

        <h3>Historique d'achats</h3>

        <table class="table">
            <thead>
                <tr>
                    <th>Article</th>
                    <th>Utilisateur</th>
                    <th>Date</th>
                </tr>
            </thead>
            <tbody>
                <?php
                foreach ($orders as $order) {
                    echo '<tr>';
                        echo '<td>' . $order['name'] . '</td>';
                        echo '<td>' . $order['email'] . '</td>';
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
