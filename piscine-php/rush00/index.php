<?php
include 'include/app.php';
loadModel('item');

if (!isset($_GET['category']))
    $items = getMostPurchasedItems();
else
    $items = getItemsFromCategory($_GET['category']);

includeHead();
?>
		<div class="hr"></div>
		<div id="milieu">
			<?php
            if (empty($items)):
                echo '<div class="alert alert-error">Aucun article disponible sur cette page !</div>';
            else:
                foreach ($items as $item) {
                    // TODO
            ?>
                    <p><?= $item['name'] ?></p>
                    <p><?php var_dump($item) ?></p>
            <?php
                }
            endif;
            ?>
		</div>
		<div class="hr"></div>
<?php
includeFooter();
?>
		
