function launchWebcamStreaming()
{

    var video = document.querySelector('#webcamVideo video');
    var streaming = false;
    navigator.getMedia = (navigator.getUserMedia || navigator.webkitGetUserMedia || navigator.mozGetUserMedia || navigator.msGetUserMedia);

    navigator.getMedia({
        video: true,
        audio: false
    }, function(stream) {
        if (navigator.mozGetUserMedia)
                video.mozSrcObject = stream;
        else {
            var vendorURL = window.URL || window.webkitURL;
            video.src = vendorURL.createObjectURL(stream);
        }
        video.play();
    }, function(err) {
        if (err.name === 'PermissionDeniedError')
            document.querySelector('#webcamVideo').innerHTML = '<article class="message is-danger">' +
                '<div class="message-body">' +
                    'Le navigateur n\'a pas la permission d\'accéder à votre webcam.' +
                '</div>' +
            '</article>';
        else
            document.querySelector('#webcamVideo').innerHTML = '<article class="message is-danger">' +
                '<div class="message-body">' +
                    'Une erreur est survenue.' +
                '</div>' +
            '</article>';
        console.error(err);
        document.querySelector('#takePicture').remove();
    });

    video.addEventListener('canplay', function(e) {
        if (!streaming) {
            document.querySelector('#webcamVideo article.message.is-info').remove();
            document.querySelector('#webcamVideo video').style.display = 'block';
            streaming = true;
        }
    }, false);

}

/*
    WEBCAM
 */
document.querySelector('#useWebcam').addEventListener('click', function (e) {
    e.preventDefault();

    // Display
    document.querySelector('#chooseCaptureType').style.display = 'none';
    document.querySelector('#capture').style.display = 'block';

    // Launch webcam
    launchWebcamStreaming();
});

/*
    UPLOAD
 */
document.querySelector('input[type="file"]').addEventListener('change', function () {
    var input = this;

    if (!input.files || !input.files[0] || (input.files[0].type).indexOf('image') === -1)
        return false;
    if (input.files[0].size > 1000000) {// 1 Mo
        alert('Veuillez fournir une image moins volumineuse.');
        return false;
    }
    var reader = new FileReader();
    reader.onload = function (e) {
        document.querySelector('#chooseCaptureType').style.display = 'none';
        document.querySelector('#capture').style.display = 'block';
        document.querySelector('#webcamVideo .message').remove();
        document.querySelector('#webcamVideo video').remove();
        document.querySelector('#webcamVideo').innerHTML += '<img src="' + e.target.result + '">';
    };
    reader.readAsDataURL(input.files[0]);
});

/*
    TAKE PICTURE AND SAVE IT
 */

document.querySelector('#takePicture').addEventListener('click', function(e) {
    e.preventDefault();
    var mask = document.querySelector('#mask');
    if (!mask.getAttribute('mask-id'))
        return false;
    var button = this;
    var video = document.querySelector('#webcamVideo video');
    var canvas = document.querySelector('#webcamResult');
    var data;

    button.classList.add('is-loading');
    document.querySelector('input[name="title"]').disabled = true;
    document.querySelector('input[name="title"]').parentNode.classList.add('is-loading');

    if (video) {
        canvas.width = video.videoWidth;
        canvas.height = video.videoHeight;
        canvas.getContext('2d').drawImage(video, 0, 0, canvas.width, canvas.height);
        data = canvas.toDataURL('image/png');
    } else {
        data = document.querySelector('#webcamVideo img').getAttribute('src');
    }

    sendPOSTRequest(ROOT_URL + 'post', {
        title: document.querySelector('input[name="title"]').value,
        img: data,
        mask: mask.getAttribute('mask-id')
    }, function (res) {
        if (res.status) {
            var img = '<figure class="image post-image" data-post-id="' + res.data.post.id + '">\n' +
                '<img src="' + res.data.post.url + '">\n' +
                '</figure>';
            var history = document.querySelector('#history');
            var element = document.createElement('div');
            element.innerHTML = img;

            history.insertBefore(element.firstChild, history.childNodes[0]);
            initDeleteEvent();
            button.classList.remove('is-loading');
            document.querySelector('input[name="title"]').disabled = false;
            document.querySelector('input[name="title"]').parentNode.classList.remove('is-loading');
            document.querySelector('input[name="title"]').value = '';
            document.querySelector('#chooseCaptureType').style.display = 'flex';
            document.querySelector('#capture').style.display = 'none';
            document.querySelector('input[type="file"]').value = '';
            document.querySelector('#webcamVideo').innerHTML = '<div id="mask"></div>\n' +
                '                            <article class="message is-info">\n' +
                '                                <div class="message-body">\n' +
                '                                    Chargement en cours...\n' +
                '                                </div>\n' +
                '                            </article>\n' +
                '                            <video style="display: none"></video>';
            if (document.querySelector('#history .message.is-danger'))
                document.querySelector('#history .message.is-danger').remove();
        } else {
            alert(res.error)
            button.classList.remove('is-loading');
            document.querySelector('input[name="title"]').disabled = false;
            document.querySelector('input[name="title"]').parentNode.classList.remove('is-loading');
        }
    }, function (err) {
        alert('Une erreur est survenue lors de l\'envoie, veuillez réessayer.');
        button.classList.remove('is-loading');
        document.querySelector('input[name="title"]').disabled = false;
        document.querySelector('input[name="title"]').parentNode.classList.remove('is-loading');
    })
}, false);

/*
    DELETE
 */
function initDeleteEvent()
{
    var posts = document.querySelectorAll('.post-image');
    for (var i = 0; i < posts.length; i++)
        posts[i].addEventListener('click', function (e) {
            e.preventDefault();
            var post = this;
            var id = post.getAttribute('data-post-id');

            // send request
            ajax('DELETE', ROOT_URL + 'posts/' + id, [], function () {});

            // remove
            post.remove();
        })
}
initDeleteEvent();

/*
    MASK
 */
var buttonMask = document.querySelectorAll('.add-mask');
for (var i = 0; i < buttonMask.length; i++)
    buttonMask[i].addEventListener('click', function (e) {
        e.preventDefault();
        var button = this;
        var img = button.querySelector('img');
        var id = button.getAttribute('id');

        document.querySelector('#takePicture').disabled = false;
        document.querySelector('#mask').style.backgroundImage = 'url(' + img.getAttribute('src') + ')';
        document.querySelector('#mask').setAttribute('mask-id', id);
    })