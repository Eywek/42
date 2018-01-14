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
            <div>
			<?php
            if (empty($items)):
                echo '<div class="alert alert-error">Aucun article disponible sur cette page !</div>';
            else:?>
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
            ?>
                    <tr>
                        <th><img class="img_category" src="<?= $item['image_url']?>" title="<?= $item['name']?>"></th>
                        <th><span style="display:block"><?= $item['name']?></span></th>
                        <th><?= $item['price']?>€</th>
                        <th><?= $item['description']?></th>
                        <th>
                            <a class="button add-to-cart <?= isInCart($item['id']) ? 'disabled' : '' ?>" data-item-id="<?= $item['id'] ?>"><?= isInCart($item['id']) ? 'Ajouté' : 'Ajouter' ?> au panier</a>
                        </th>
                    </tr>
            <?php
                }
            ?>
            </table>
            <?php
                endif;
            ?>
    </div>
		</div>
		<div class="hr"></div>
<?php
includeFooter();
?>
		
