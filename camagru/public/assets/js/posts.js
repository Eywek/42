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

    sendGETRequest(ROOT_URL + 'posts/limit/10/5', function (posts) {
        console.log(posts);
        console.log(getPostHtml(posts.data.posts[0]));
    });
};

/*
    INFINITE SCROLL
 */

function getPostHtml(post)
{
    var html = document.querySelector('#post-template').innerHTML;
    html = html.replace(new RegExp('{POST_ID}', 'g'), post.id);
    html = html.replace('{TITLE}', post.title);
    html = html.replace('{USERNAME}', post.users[0].username);
    html = html.replace('{LIKES_COUNT}', post.likes.length);
    html = html.replace('{COMMENTS_COUNT}', post.comments.length);
    html = html.replace('{LIKE_STATE}', post.hasLiked ? '1' : '0');
    html = html.replace('{LIKE_TEXT}', post.hasLiked ? "Je n'aime plus" : "J'aime");
    html = html.replace('{CREATED_AT}', post.created_at);

    return html;
}