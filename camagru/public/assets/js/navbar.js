var dropdowns = document.querySelectorAll('.navbar-item.has-dropdown')
for (var i = 0; i < dropdowns.length; i++) {
    dropdowns[i].addEventListener('click', function (event) {
        var dropdown = this
        if (dropdown.classList.contains('is-active'))
            dropdown.classList.remove('is-active')
        else
            dropdown.classList.add('is-active')
    })
}

document.querySelector('.navbar-burger.burger').addEventListener('click', function (e) {
    e.preventDefault();
    var nav = document.querySelector('.navbar-menu#navbar');

    if (window.getComputedStyle(nav).display === 'none')
        nav.style.display = 'block';
    else
        nav.style.display = 'none';
});