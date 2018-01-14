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
		<div>
			<?php
            if (empty($items)):
                echo '<div class="alert alert-error">Aucun article disponible sur cette page !</div>';
            else:?>
            <div>
            <table>
                <thead>
                    <tr>
                        <th>Photos</th>
                        <th>Nom</th>
                        <th>Prix</th>
                        <th>Description</th>
                        <th>Actions</th>
                    </tr>
                </thead>
                <?php
                foreach ($items as $item) {
                    // TODO
            ?>
                    <tr>
                        <th><img class="img_category" src="<?= $item['image_url']?>" title="<?= $item['name']?>"></th>
                        <th><span style="display:block"><?= $item['name']?></span></th>
                        <th><?= $item['price']?>€</th>
                        <th><?= $item['description']?></th>
                        <th><form action="add_cart.php" method="get">
                                <input type="submit" value="Ajouter au panier">
                            </form></th>
                        </tr>
            <?php
                }
            endif;
            ?>
        </table>
    </div>
		</div>
		<div class="hr"></div>
<?php
includeFooter();
?>
		
