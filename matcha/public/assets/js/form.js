function initFormEvents()
{
    var form = $('form[data-ajax]');
    form.unbind('submit');
    form.on('submit', function (e) {
        e.preventDefault();
        var form = $(this);
        var button = form.find('button[type="submit"]');
        var callback = form.attr('data-ajax-callback');

        // Disable button
        button.attr('disabled', true);
        button.addClass('disabled');

        // Get inputs
        var data;
        if (form.attr('enctype') === 'multipart/form-data')
            data = (window.FormData) ? new FormData(form[0]) : null;
        else
            data = JSON.stringify(serialize(this));

        // Disable inputs
        editInputsState(form, false);

        // Request
        $.ajax({
            method: form.attr('method'),
            url: form.attr('action'),
            data: data,
            dataType: 'json',
            contentType: (form.attr('enctype') === 'multipart/form-data') ? false : 'application/json',
            processData: (form.attr('enctype') === 'multipart/form-data') ? false : undefined,
            success: function (res) {
                if (res.status)
                    displayResponseAlert(res.success, true, form);
                else
                    displayResponseAlert(res.error, false, form);
                if (res.redirect)
                    document.location = res.redirect;
                if (res.status && callback)
                    window[callback](data, res);
            },
            error: function (jqXHR, textStatus, errorThrown) {
                console.error(jqXHR, textStatus, errorThrown);
                displayResponseAlert('Une erreur interne est survenue', false, form);
            }
        });
    });
}
initFormEvents();

function displayResponseAlert(content, state, form)
{
    // Display alert
    var className = (state) ? 'alert-success' : 'alert-danger';
    content = '<b>' + (state ? 'Succès' : 'Erreur') + ' : </b>' + content;
    var html = '<div class="alert ' + className + '">' + content + '</div>';
    if (!form.find('.ajax-msg').length)
        form.prepend('<div class="ajax-msg"></div>');
    form.find('.ajax-msg').html(html);

    // Enable btn
    form.find('button[type="submit"]').attr('disabled', false).removeClass('disabled');

    // Enable inputs
    editInputsState(form, true);
}

function editInputsState(form, state)
{
    if (state)
        form.find('input, select, textarea').addClass('disabled');
    else
        form.find('input, select, textarea').removeClass('disabled');
}

/* =================================
       UTILS
 ================================= */
function serialize(form)
{
    // Check if i'ts a form
    if (!form || form.nodeName !== "FORM")
        return;
    // Each elements
    var data = {};
    for (var i = form.elements.length - 1; i >= 0; i = i - 1) {
        if (form.elements[i].name === "")
            continue;
        switch (form.elements[i].nodeName) {
            case 'INPUT': // INPUTS
                switch (form.elements[i].type) {
                    case 'text':
                    case 'hidden':
                    case 'password':
                    case 'email':
                    case 'number':
                    case 'submit':
                        data[form.elements[i].name] = (form.elements[i].value);
                        break;
                    case 'checkbox':
                    case 'radio':
                        if (form.elements[i].checked)
                            data[form.elements[i].name] = (form.elements[i].value);
                        break;
                }
                break;
            case 'TEXTAREA': // TEXTAREA
                data[form.elements[i].name] = (form.elements[i].value);
                break;
            case 'SELECT': // SELECTS
                switch (form.elements[i].type) {
                    case 'select-one':
                        data[form.elements[i].name] = (form.elements[i].value);
                        break;
                    case 'select-multiple': // Multiple select
                        for (var j = form.elements[i].options.length - 1; j >= 0; j = j - 1) {
                            if (form.elements[i].options[j].selected) {
                                data[form.elements[i].name] = (form.elements[i].options[j].value);
                            }
                        }
                        break;
                }
                break;
        }
    }
    return data;
}