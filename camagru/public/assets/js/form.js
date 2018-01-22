
/* =================================
    AJAX METHODS
 ================================= */
function sendPOSTRequest(url, data, callback, errorCallback)
{
    ajax('POST', url, data, callback, errorCallback);
}

function sendGETRequest(url, callback, errorCallback)
{
    ajax('GET', url, [], callback, errorCallback);
}

function ajax(method, url, data, callback, errorCallback)
{
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState === 4) {
            var res = this.responseText;
            var isJson = false;
            try {
                res = JSON.parse(this.responseText);
                isJson = true;
            } catch (e) {
                console.error(e);
            }
            if (this.status === 200 && isJson)
                callback(res);
            else if (errorCallback)
                errorCallback(res)
        }
    };
    xhttp.open(method, url, true);
    xhttp.setRequestHeader('Content-Type', 'application/json');
    xhttp.setRequestHeader('Accept', 'application/json');
    xhttp.send(JSON.stringify(data));
}

/* =================================
    FORMS HANDLE
 ================================= */
var forms = document.querySelectorAll('form[data-ajax]');
for (var i = 0; i < forms.length; i++)
    handleForm(forms[i]);

function handleForm(form)
{
    form.removeEventListener('submit', onFormSubmit);
    form.addEventListener('submit', onFormSubmit);
}

function onFormSubmit (e) {
    e.preventDefault();
    var form = this;
    var button = form.querySelector('button[type="submit"]');
    var callback = form.getAttribute('data-ajax-callback');

    // Disable button
    button.classList.add('is-loading');

    // Get inputs
    var data = serialize(form);

    // Disable inputs
    editInputsState(form, false);

    // Request
    ajax(form.getAttribute('method'), form.getAttribute('action'), data, function (res) {
        if (res.status)
            displayResponseAlert(res.success, true, form);
        else
            displayResponseAlert(res.error, false, form);
        if (res.redirect)
            document.location = res.redirect;
        if (res.status && callback)
            window[callback](data, res);
    }, function (error) {
        console.error(error);
        displayResponseAlert('Une erreur interne est survenue', false, form);
    });
}

function displayResponseAlert(content, state, form)
{
    // Display alert
    var className = (state) ? 'is-success' : 'is-danger';
    content = '<b>' + (state ? 'Succès' : 'Erreur') + ' : </b>' + content;
    var html = '<div class="notification ' + className + '">' + content + '</div>';
    var element = form.querySelector('.ajax-msg');
    if (element)
        element.innerHTML = html;
    else {
        element = document.createElement('div');
        element.innerHTML = html;
        form.insertBefore(element.firstChild, form.childNodes[0]);
    }

    // Enable btn
    var button = form.querySelector('button[type="submit"]');
    button.classList.remove('is-loading');

    // Enable inputs
    editInputsState(form, true);
}

function editInputsState(form, state)
{
    var inputs = form.querySelectorAll('input, select, textarea');
    for (var i = 0; i < inputs.length; i++) {
        if (state)
            inputs[i].parentElement.classList.remove('is-loading');
        else
            inputs[i].parentElement.classList.add('is-loading');
        inputs[i].disabled = !state;
    }
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