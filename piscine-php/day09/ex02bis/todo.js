$('#ft_list button').on('click', function (event) {
    event.preventDefault();
    var value;

    if ((value = prompt('Ajouter un nouveau to do'))) {
        if (value.length === 0)
            return;
        // Create element
        addTodo(value);
        addToCookie(value);
        initDelEvent();
    }
});

function addTodo(value)
{
    $('#ft_list').prepend($('<div>' + value + '</div>'));
}

function initDelEvent()
{
    $('#ft_list div').unbind('click');
    $('#ft_list div').on('click', function (event) {
        event.preventDefault();
        removeFromCookie($(this).html());
        $(this).remove();
    });
}

function addToCookie(value)
{
    var cookies = getCookie('todo');
    cookies.push(value);
    document.cookie = 'todo=' + JSON.stringify(cookies);
}

function removeFromCookie(value)
{
    var cookies = getCookie('todo');
    cookies.splice(cookies.indexOf(value), 1);
    document.cookie = 'todo=' + JSON.stringify(cookies);
}

function getCookie(name) {
    var nameEQ = name + "=";
    var ca = document.cookie.split(';');
    for(var i=0;i < ca.length;i++) {
        var c = ca[i];
        while (c.charAt(0) === ' ')
            c = c.substring(1,c.length);
        if (c.indexOf(nameEQ) === 0)
            return JSON.parse(c.substring(nameEQ.length,c.length));
    }
    return [];
}

// INIT
var cookies = getCookie('todo');
for (var i = 0; i < cookies.length; i++) {
    addTodo(cookies[i]);
}
initDelEvent();