$('#ft_list button').on('click', function (event) {
    event.preventDefault();
    var value;
    var button = $(this);

    if ((value = prompt('Ajouter un nouveau to do'))) {
        if (value.length === 0)
            return;
        // Create element
        $.post('insert.php', {message: value}, function (data) {
            data = JSON.parse(data);
            var id = data.id;
            addTodo(value, id);
            initDelEvent();
        });
    }
});

function addTodo(value, id)
{
    $('#ft_list').prepend($('<div data-id="' + id + '">' + value + '</div>'));
}

function initDelEvent()
{
    $('#ft_list div').unbind('click');
    $('#ft_list div').on('click', function (event) {
        event.preventDefault();
        var id = $(this).attr('data-id');

        $.post('delete.php', {id: id});
        $(this).remove();
    });
}

// INIT
$.get('select.php', function (data) {
    data = JSON.parse(data);
    var list = data.list;
    for (var id in list)
        addTodo(list[id], id);
    initDelEvent();
});