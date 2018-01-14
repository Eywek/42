function confirmation(texte,page){
    if(confirm(texte))
        document.location.href = page;
}

var buttonsCart = document.querySelectorAll('.add-to-cart:not(.disabled)');
for (var i = 0; i < buttonsCart.length; i++) {
    buttonsCart[i].addEventListener('click', function (event) {
        event.preventDefault();
        var button = this;
        var itemId = button.getAttribute('data-item-id');

        var xmlhttp = new XMLHttpRequest();
        xmlhttp.onreadystatechange = function() {
            if (xmlhttp.readyState === XMLHttpRequest.DONE) {
                if (xmlhttp.status === 200) {
                    var response = JSON.parse(xmlhttp.responseText);
                    if (response.status) {
                        button.innerHTML = 'Ajouté au panier';
                        button.classList.add('disabled');
                    } else
                        alert('Une erreur est survenue lors de l\'ajout au panier.');
                }
            }
        };

        xmlhttp.open("GET", "add_to_cart.php?id=" + itemId, true);
        xmlhttp.send();
    });
}

function calculTotal()
{
    var total = 0;
    var inputQuantity = document.querySelectorAll('input[name="item_quantity"]');
    for (i = 0; i < inputQuantity.length; i++) {
        var quantity = parseInt(inputQuantity[i].value);
        var itemId = inputQuantity[i].getAttribute('data-item-id');
        var itemPrice = parseFloat(document.querySelector('span.item-price[data-item-id="' + itemId + '"]').getAttribute('data-item-price'));
        total += itemPrice * quantity;
    }
    document.querySelector('span.total').innerHTML = total;
}

var inputQuantity = document.querySelectorAll('input[name="item_quantity"]');
for (i = 0; i < inputQuantity.length; i++) {
    inputQuantity[i].addEventListener('change', function (event) {
        event.preventDefault();
        var input = this;
        var itemId = input.getAttribute('data-item-id');
        var quantity = parseInt(input.value);
        if (quantity < 0)
        {
            alert('La quantité ne peut pas être négative.');
            return false;
        }
        var itemPrice = parseFloat(document.querySelector('span.item-price[data-item-id="' + itemId + '"]').getAttribute('data-item-price'));

        var xmlhttp = new XMLHttpRequest();
        xmlhttp.onreadystatechange = function() {
            if (xmlhttp.readyState === XMLHttpRequest.DONE) {
                if (xmlhttp.status === 200) {
                    var response = JSON.parse(xmlhttp.responseText);
                    if (response.status) {
                        document.querySelector('span.item-price[data-item-id="' + itemId + '"]').innerHTML = itemPrice * parseInt(quantity);
                        calculTotal();
                    }
                    else
                        alert('Une erreur est survenue lors de la modification du panier.');
                }
            }
        };

        xmlhttp.open("GET", "set_quantity.php?id=" + itemId + "&quantity=" + quantity, true);
        xmlhttp.send();
    });
}