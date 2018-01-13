<?php
function getItemCategories()
{
    $categories = queryDB('SELECT `name` FROM categories');
    return array_map(function ($category) {
        return $category['name'];
    }, $categories);
}

function getItems()
{
    return queryDB('SELECT `items`.`id` AS `id`, `items`.`name` AS `name`, `items`.`price` AS `price`, `items`.`image_url` AS `image_url`, `items`.`description` AS `description`, `items`.`created_at` AS `created_at` 
                FROM `items`');
}

function getItemsFromCategory($category)
{
    return queryDB('SELECT `items`.`id` AS `id`, `items`.`name` AS `name`, `items`.`price` AS `price`, `items`.`image_url` AS `image_url`, `items`.`description` AS `description`, `items`.`created_at` AS `created_at` 
                FROM `items`
                INNER JOIN `items_categories` ON `items_categories`.`item_id` = `items`.`id`
                INNER JOIN `categories` ON `categories`.`id` = `items_categories`.`category_id`
                WHERE `categories`.`name` = ?', ['s', $category]);
}

function getMostPurchasedItems()
{
    return queryDB('SELECT `items`.`id` AS `id`, `items`.`name` AS `name`, `items`.`image_url` AS `image_url`, `items`.`price` AS `price`, `items`.`description` AS `description`, `orders`.`purchases` AS `purchases`, `items`.`created_at` AS `created_at` 
                    FROM `items` 
                    INNER JOIN (SELECT `orders`.`item_id`, COUNT(`orders`.`id`) AS `purchases` FROM `orders`) AS `orders` ON `orders`.`item_id` = `items`.`id`
                    ORDER BY `purchases` DESC
                    LIMIT 10');
}

function purchaseCart($items, $address)
{
    foreach ($items as $item)
        if (($error = purchaseItem($item, $address)) !== true)
            return $error;
    return true;
}

function purchaseItem($itemId, $address)
{
    if (!preg_match('/^\d+ [a-zA-Z ]+, \d+ [a-zA-Z ]+, [a-zA-Z ]+$/', $address))
        return "L'addresse est invalide";
    if (empty(queryDB('SELECT `id` FROM `items` WHERE `id` = ?', ['i', $itemId])))
        return "L'article n'existe pas";
    queryDB('INSERT INTO `orders` SET `item_id` = ?, `user_id` = ?, `address` = ?, `created_at` = ?', [
       'iiss', $itemId, getUser()['id'], $address, date('Y-m-d H:i:s')
    ]);
    return true;
}