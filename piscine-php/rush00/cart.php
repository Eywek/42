<?php
require 'include/app.php';
loadModel('item');

if ($_POST && isset($_POST['buy']) && isset($_SESSION['cart']) && !empty($_SESSION['cart']))
{
    if (($status = purchaseCart($_SESSION['cart'], sanitize($_POST['address']))) === true) {
        // reset cart
        $_SESSION['cart'] = [];
    } else
        $error = $status;

}

includeHead();
?>
<?php
if (isset($error))
    echo "<div class='alert alert-error'><b>Erreur :</b> $error</div>";
if (isset($status) && $status === true)
    echo "<div class='alert alert-success'><b>Succès :</b> Votre commande a bien été validée ! Vous recevrez vos goodies bientôt !</div>";
?>
--> Afficher (dans une table?) les articles présents dans $_SESSION['cart'], mettre un bouton pour acheter dans un form POST avec le nom "buy" et ajouter un input pour renseigner l'addresse au format XX Rue de XXXX, CODE VILLE, France
<?php
includeFooter();
?>
