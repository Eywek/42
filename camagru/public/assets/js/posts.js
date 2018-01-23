function initPostEventListeners()
{
    // Like
    var likeButtons = document.querySelectorAll('.like-post');
    for (var i = 0; i < likeButtons.length; i++) {
        likeButtons[i].removeEventListener('click', onLikePost);
        likeButtons[i].addEventListener('click', onLikePost);
    }

    // Comment button
    var commentsButtons = document.querySelectorAll('.see-post-comments');
    for (i = 0; i < commentsButtons.length; i++) {
        commentsButtons[i].removeEventListener('click', onSeeComment);
        commentsButtons[i].addEventListener('click', onSeeComment);
    }

    // Post a comment
}

function onSeeComment(e) {
    e.preventDefault();
    var button = this;
    var postId = button.getAttribute('data-post-id');
    var postColum = document.querySelector('.post-column[data-post-id="' + postId + '"]');
    var postCommentsColumn = document.querySelector('.post-comments-column[data-post-id="' + postId + '"]');
    var isActive = postCommentsColumn.classList.contains('active');

    if (!isActive) {
        postColum.classList.add('is-three-quarters');
        postCommentsColumn.classList.add('active');
        button.innerHTML = 'Cacher les commentaires';
    } else {
        postColum.classList.remove('is-three-quarters');
        postCommentsColumn.classList.remove('active');
        button.innerHTML = 'Afficher les commentaires';
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

function getCommentHtml(comment)
{
    var commentHtml = document.querySelector('#comment-template').innerHTML;

    commentHtml = commentHtml.replace('{CONTENT}', comment.content);
    var date = new Date(comment.created_at);
    var monthNames = ["Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    ];
    var dateText = date.getHours() + 'h' + date.getMinutes() + ' - ' + date.getDate() + ' ' + monthNames[date.getMonth()] + ' ' + date.getFullYear();
    commentHtml = commentHtml.replace('{DATE}', dateText);
    return commentHtml;
}

function afterPostComment(req, res)
{
    res.data.comment.created_at = new Date();
    var message = document.querySelector('.post-comments-column[data-post-id="' + res.data.post.id + '"] .comment-card .card-content .message');

    if (message)
        message.remove();
    document.querySelector('.post-comments-column[data-post-id="' + res.data.post.id + '"] .comment-card .card-content').innerHTML += getCommentHtml(res.data.comment);
    document.querySelector('.post-comments-column[data-post-id="' + res.data.post.id + '"] .ajax-msg').innerHTML = '';
    document.querySelector('.post-comments-column[data-post-id="' + res.data.post.id + '"] textarea[name="content"]').value = '';
}

window.onload = function ()
{
    initPostEventListeners();
};

/*
    INFINITE SCROLL
 */

function getPostHtml(post)
{
    var html = document.querySelector('#post-template').innerHTML;
    html = html.replace(new RegExp('{POST_ID}', 'g'), post.id);
    html = html.replace('{TITLE}', post.title);
    html = html.replace('{TITLE}', post.title);
    html = html.replace('{USERNAME}', post.users[0].username);
    html = html.replace('{LIKES_COUNT}', post.likes.length);
    html = html.replace('{COMMENTS_COUNT}', post.comments.length);
    html = html.replace('{LIKE_STATE}', post.hasLiked ? '1' : '0');
    html = html.replace('{LIKE_TEXT}', post.hasLiked ? "Je n'aime plus" : "J'aime");

    var date = new Date(post.created_at);
    var monthNames = ["Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    ];
    var dateText = date.getHours() + 'h' + date.getMinutes() + ' - ' + date.getDate() + ' ' + monthNames[date.getMonth()] + ' ' + date.getFullYear();
    html = html.replace('{CREATED_AT}', dateText);

    // comments
    var comments = '';
    for (var i = 0; i < post.comments.length; i++)
        comments += getCommentHtml(post.comments[i]);
    if (post.comments.length === 0)
        comments = '<article class="message is-danger">\n' +
                '<div class="message-body">' +
                    'Aucun commentaire pour le moment\n' +
                '</div>\n' +
            '</article>';
    html = html.replace('{COMMENTS}', comments);

    return html;
}

function getScrollXY() {
    var scrOfX = 0, scrOfY = 0;
    if(typeof( window.pageYOffset ) === 'number') {
        //Netscape compliant
        scrOfY = window.pageYOffset;
        scrOfX = window.pageXOffset;
    } else if( document.body && ( document.body.scrollLeft || document.body.scrollTop ) ) {
        //DOM compliant
        scrOfY = document.body.scrollTop;
        scrOfX = document.body.scrollLeft;
    } else if( document.documentElement && ( document.documentElement.scrollLeft || document.documentElement.scrollTop ) ) {
        //IE6 standards compliant mode
        scrOfY = document.documentElement.scrollTop;
        scrOfX = document.documentElement.scrollLeft;
    }
    return [ scrOfX, scrOfY ];
}

function getDocHeight() {
    var D = document;
    return Math.max(
        D.body.scrollHeight, D.documentElement.scrollHeight,
        D.body.offsetHeight, D.documentElement.offsetHeight,
        D.body.clientHeight, D.documentElement.clientHeight
    );
}

function debounce(func, wait, immediate) {
    var timeout;
    return function() {
        var context = this, args = arguments;
        var later = function() {
            timeout = null;
            if (!immediate) func.apply(context, args);
        };
        var callNow = immediate && !timeout;
        clearTimeout(timeout);
        timeout = setTimeout(later, wait);
        if (callNow) func.apply(context, args);
    };
}

var continueLoading = true;
var infiniteLoad = debounce(function () {
    if (getDocHeight() - 300 <= getScrollXY()[1] + window.innerHeight) {
        console.log('Loading new content...');
        if (!continueLoading) {
            console.log('No more content.');
            return;
        }
        var postsIndex = parseInt(document.querySelector('.posts-list').getAttribute('data-current-post-index'));

        sendGETRequest(ROOT_URL + 'posts/limit/10/' + postsIndex, function (posts) {
            var list = document.querySelector('.posts-list');
            if (posts.data.count === 0)
                continueLoading = false;
            posts = posts.data.posts;
            postsIndex += 10;
            document.querySelector('.posts-list').setAttribute('data-current-post-index', postsIndex);

            for (var i = 0; i < posts.length; i++)
                list.innerHTML += getPostHtml(posts[i]);
            initPostEventListeners();

            var forms = document.querySelectorAll('form[data-ajax]');
            for (i = 0; i < forms.length; i++)
                handleForm(forms[i]);
        });
    }
}, 250);

document.addEventListener("scroll", infiniteLoad);