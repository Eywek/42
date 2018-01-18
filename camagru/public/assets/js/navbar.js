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