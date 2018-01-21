function initPostEventListeners()
{
    var likeButtons = document.querySelectorAll('.like-post');
    for (var i = 0; i < likeButtons.length; i++) {
        likeButtons[i].removeEventListener('click', onLikePost);
        likeButtons[i].addEventListener('click', onLikePost);
    }
}

function onLikePost(e)
{
    e.preventDefault();
    var button = this;
    var state = parseInt(button.getAttribute('data-state'));
    var postId = button.getAttribute('data-post-id');
    var url = ROOT_URL + 'posts/' + postId + '/' + (state ? 'unlike' : 'like');
    var likeCount = document.querySelector('.like-count[data-post-id="' + postId + '"]');

    sendPOSTRequest(url, [], function () {});
    if (state) {
        button.innerHTML = "J'aime";
        likeCount.innerHTML = parseInt(likeCount.innerHTML) - 1;
    } else {
        button.innerHTML = "Je n'aime plus";
        likeCount.innerHTML = parseInt(likeCount.innerHTML) + 1;
    }
    button.setAttribute('data-state', (state ? '0' : '1'))
}

window.onload = function ()
{
    initPostEventListeners();
};