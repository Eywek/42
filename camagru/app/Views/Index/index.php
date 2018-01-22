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
    <div class="container posts-list" data-current-post-index="<?= count($posts) ?>">

        <?php foreach ($posts as $post): ?>

            <div class="columns is-gapless">

                <div class="column post-column" data-post-id="<?= $post->id ?>">
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
                                <time class="is-pulled-right"><?= date('H\hi - d M Y', strtotime($post->created_at)) ?></time>
                            </div>
                        </div>
                        <?php if (\Models\UserModel::isLogged()): ?>
                            <footer class="card-footer">
                                <a href="#" class="card-footer-item see-post-comments" data-post-id="<?= $post->id ?>">Voir les commentaires</a>
                                <a href="#" class="card-footer-item like-post" data-state="<?= \Models\UserModel::hasLike($post) ? '1' : '0' ?>" data-post-id="<?= $post->id ?>"><?= \Models\UserModel::hasLike($post) ? "Je n'aime plus" : "J'aime" ?></a>
                            </footer>
                        <?php endif; ?>
                    </div>
                </div>

                <div class="column post-comments-column" data-post-id="<?= $post->id ?>">
                    <div class="card comment-card">
                        <header class="card-header">
                            <p class="card-header-title">
                                Commentaires
                            </p>
                        </header>
                        <div class="card-content">
                            <?php foreach ($post->comments as $comment): ?>
                                <div class="comment">
                                    <div class="head">
                                        <img src="https://www.gravatar.com/avatar/<?= md5($comment->users[0]->email) ?>" alt="Gravatar">
                                        <span><?= $comment->users[0]->username ?></span>
                                        <span class="date">
                                        <?= date('H\hi - d M Y', strtotime($comment->created_at)) ?>
                                    </span>
                                    </div>
                                    <p>
                                        <?= $comment->content ?>
                                    </p>
                                </div>
                            <?php endforeach; ?>
                            <?php if (empty($post->comments)): ?>
                                <article class="message is-danger">
                                    <div class="message-body">
                                        Aucun commentaire pour le moment
                                    </div>
                                </article>
                            <?php endif; ?>
                        </div>
                        <footer class="card-footer">
                            <form action="<?= $this->url('/posts/' . $post->id . '/comment') ?>" method="post" data-ajax data-ajax-callback="afterPostComment">
                                <div class="ajax-msg" style="margin-bottom: 5px"></div>

                                <div class="field">
                                    <label class="label">Message</label>
                                    <div class="control">
                                        <textarea class="textarea" name="content" placeholder="Votre commentaire"></textarea>
                                    </div>
                                </div>

                                <div class="field is-pulled-right">
                                    <div class="control">
                                        <button type="submit" class="button is-link">Commenter</button>
                                    </div>
                                </div>

                            </form>
                            <div class="is-clearfix"></div>
                        </footer>
                    </div>
                </div>

            </div>

        <?php endforeach; ?>

    </div>
</section>
<script type="text/html" id="comment-template">
    <div class="comment">
        <div class="head">
            <img src="https://www.gravatar.com/avatar/<?= md5(\Models\UserModel::getCurrent()->email) ?>" alt="Gravatar">
            <span><?= \Models\UserModel::getCurrent()->username ?></span>
            <span class="date">{DATE}</span>
        </div>
        <p>
            {CONTENT}
        </p>
    </div>
</script>
<script type="text/html" id="post-template">
    <div class="columns is-gapless">

        <div class="column post-column" data-post-id="{POST_ID}">
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
                        <a href="#" class="card-footer-item see-post-comments" data-post-id="{POST_ID}">Voir les commentaires</a>
                        <a href="#" class="card-footer-item like-post" data-state="{LIKE_STATE}" data-post-id="{POST_ID}">{LIKE_TEXT}</a>
                    </footer>
                <?php endif; ?>
            </div>
        </div>

        <div class="column post-comments-column" data-post-id="{POST_ID}">
            <div class="card comment-card">
                <header class="card-header">
                    <p class="card-header-title">
                        Commentaires
                    </p>
                </header>
                <div class="card-content">
                    {COMMENTS}
                </div>
                <footer class="card-footer">
                    <form action="<?= $this->url('/posts/{POST_ID}/comment') ?>" method="post" data-ajax data-ajax-callback="afterPostComment" data-ajax-id="{AJAX_ID}">
                        <div class="ajax-msg" style="margin-bottom: 5px"></div>

                        <div class="field">
                            <label class="label">Message</label>
                            <div class="control">
                                <textarea class="textarea" name="content" placeholder="Votre commentaire"></textarea>
                            </div>
                        </div>

                        <div class="field is-pulled-right">
                            <div class="control">
                                <button type="submit" class="button is-link">Commenter</button>
                            </div>
                        </div>

                    </form>
                    <div class="is-clearfix"></div>
                </footer>
            </div>
        </div>

    </div>
</script>
<script type="text/javascript">
    var ROOT_URL = '<?= $this->url('/') ?>';
</script>
<script type="text/javascript" src="<?= $this->url('/assets/js/posts.js') ?>"></script>
<?= $this->template('footer') ?>
