var modalsButtons = document.querySelectorAll('.toggle-modal');
for (var i = 0; i < modalsButtons.length; i++) {
    modalsButtons[i].addEventListener('click', function (e) {
        e.preventDefault();
        var button = this;
        var modalSelector = button.getAttribute('href');
        var modal = document.querySelector(modalSelector);
        var linksToOthersModals = modal.querySelectorAll('a.toggle-modal');

        for (var j = 0; j < linksToOthersModals.length; j++)
            setModalCloseEvent(linksToOthersModals[j], modal);

        modal.classList.add('active');
        setTimeout(function () {
            modal.style.opacity = '1';
        }, 10);
    })
}

function setModalCloseEvent(element, modal)
{
    element.addEventListener('click', function (e) {
        e.preventDefault();
        var btn = this;
        if (!modal)
            modal = btn.parentElement;

        modal.style.opacity = '0';
        setTimeout(function () {
            modal.classList.remove('active');
        }, 250);
    })
}

var modalsCloses = document.querySelectorAll('.modal-close');
for (i = 0; i < modalsCloses.length; i++)
    setModalCloseEvent(modalsCloses[i]);