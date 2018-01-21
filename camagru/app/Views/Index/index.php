<?= $this->template('head') ?>
<section class="hero is-info">
    <div class="container">
        <div class="hero-body">
            <p class="title">
                Récentes publications
            </p>
        </div>
    </div>
</section>
<section class="section">
    <div class="container">

        <?php foreach ($posts as $post): ?>

            <div class="card">
                <div class="card-image">
                    <figure class="image is-4by3">
                        <img src="https://bulma.io/images/placeholders/1280x960.png" alt="Placeholder image">
                    </figure>
                </div>
                <div class="card-content">
                    <div class="media">
                        <div class="media-content">
                            <p class="title is-4"><?= $post->title ?></p>
                            <p class="subtitle is-6">@<?= $post->users[0]->username ?></p>
                        </div>
                    </div>

                    <div class="content">
                        <hr>
                        <span>
                            <span class="tag is-rounded is-medium"><i class="fa fa-thumbs-up"></i>&nbsp; <span class="like-count" data-post-id="<?= $post->id ?>"><?= count($post->likes) ?></span></span>
                            <span class="tag is-rounded is-medium"><i class="fa fa-comments"></i>&nbsp; <?= count($post->comments) ?></span>
                        </span>
                        <time class="is-pulled-right"><?= date('h\hm - d M Y') ?></time>
                    </div>
                </div>
                <?php if (\Models\UserModel::isLogged()): ?>
                    <footer class="card-footer">
                        <a href="#" class="card-footer-item">Commenter</a>
                        <a href="#" class="card-footer-item like-post" data-state="<?= \Models\UserModel::hasLike($post) ? '1' : '0' ?>" data-post-id="<?= $post->id ?>"><?= \Models\UserModel::hasLike($post) ? "Je n'aime plus" : "J'aime" ?></a>
                    </footer>
                <?php endif; ?>
            </div>

        <?php endforeach; ?>

    </div>
</section>
<script type="text/html" id="post-template">
    <div class="card">
        <div class="card-image">
            <figure class="image is-4by3">
                <img src="https://bulma.io/images/placeholders/1280x960.png" alt="Placeholder image">
            </figure>
        </div>
        <div class="card-content">
            <div class="media">
                <div class="media-content">
                    <p class="title is-4">{TITLE}</p>
                    <p class="subtitle is-6">@{USERNAME}</p>
                </div>
            </div>

            <div class="content">
                <hr>
                <span>
                            <span class="tag is-rounded is-medium"><i class="fa fa-thumbs-up"></i>&nbsp; <span class="like-count" data-post-id="{POST_ID}">{LIKES_COUNT}</span></span>
                            <span class="tag is-rounded is-medium"><i class="fa fa-comments"></i>&nbsp; {COMMENTS_COUNT}</span>
                        </span>
                <time class="is-pulled-right">{CREATED_AT}</time>
            </div>
        </div>
        <?php if (\Models\UserModel::isLogged()): ?>
            <footer class="card-footer">
                <a href="#" class="card-footer-item">Commenter</a>
                <a href="#" class="card-footer-item like-post" data-state="{LIKE_STATE}" data-post-id="{POST_ID}">{LIKE_TEXT}</a>
            </footer>
        <?php endif; ?>
    </div>
</script>
<script type="text/javascript">
    var ROOT_URL = '<?= $this->url('/') ?>';
</script>
<script type="text/javascript" src="<?= $this->url('/assets/js/posts.js') ?>"></script>
<?= $this->template('footer') ?>
