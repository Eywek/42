<?php
require 'include/app.php';
loadModel('item');

$cart = getCart();
if ($_POST && isset($_POST['buy']) && !empty($cart['items']))
{
    if (($status = purchaseCart($_SESSION['cart'], sanitize(removeAccents($_POST['address'])))) === true) {
        // reset cart
        $_SESSION['cart'] = [];
    } else
        $error = $status;

}
$cart = getCart();

includeHead();
?>
<?php
if (isset($error))
    echo "<div class='alert alert-error'><b>Erreur :</b> $error</div>";
if (isset($status) && $status === true)
    echo "<div class='alert alert-success'><b>Succès :</b> Votre commande a bien été validée ! Vous recevrez vos goodies bientôt !</div>";
?>
        <div class="hr"></div>
        <div>
        	<?php 
        		if (empty($cart['items'])):
        			echo '<div class="alert alert-error">Pas d\'article dans votre panier !</div>';
        		else:?>
         <div>
            <table>
                <thead>
                    <tr>
                        <th>Photos</th>
                        <th>Nom</th>
                        <th>Prix</th>
                        <th>Quantité</th>
                        <th>Description</th>
                        <th>Actions</th>
                    </tr>
                </thead>
                <?php
                foreach ($cart['items'] as $elem) {
            ?>
                    <tr>
                        <th><img class="img_category" src="<?= $elem['image_url']?>" title="<?= $elem['name']?>"></th>
                        <th><span style="display:block"><?= $elem['name']?></span></th>
                        <th><span class="item-price" data-item-price="<?= $elem['price'] ?>" data-item-id="<?= $elem['id'] ?>"><?= $elem['price'] * $elem['quantity'] ?></span>€</th>
                        <th><input min="1" type="number" style="width: 30px" step="1" name="item_quantity" data-item-id="<?= $elem['id'] ?>" value="<?=  $elem['quantity'] ?>"></th>
                        <th><?= $elem['description']?></th>
                        <th><form action="set_quantity.php" method="get">
                            <input type="hidden" name="id" value="<?= $elem['id']?>">
                            <input type="hidden" name="quantity" value="0">
                            <input type="hidden" name="redirect" value="1">
                                <button class="button" type="submit">Supprimer du panier</button>
                            </form></th>
                        </tr>
            <?php
            } ?>
            <tr>
                <td></td>
                <td></td>
                <td></td>
                <td></td>
                <td>Total</td>
                <td><span class="total"><?= $cart['total'] ?></span>€</td>
            </tr>
        </table>

        <form method="post" style="text-align: center">
            <input type="text" name="address" style="width: 50%;" placeholder="XX Rue de XXXX, CP VILLE, PAYS">
            <button class="button" type="submit" name="buy">Valider le panier</button>
        </form>
             <br><br>
    <?php  endif; ?>
    </div>
		<div class="hr"></div>
<?php
includeFooter();
?>
