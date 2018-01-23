<?= $this->template('head') ?>
<section class="hero is-info">
    <div class="container">
        <div class="hero-body">
            <p class="title">
                Poster une publication
            </p>
        </div>
    </div>
</section>
<section class="section">
    <div class="container">

        <div class="columns">

            <div class="column is-three-quarters">
                <div class="box">

                    <div class="field">
                        <div class="control">
                            <input class="input" type="text" name="title" placeholder="Votre titre">
                        </div>
                    </div>

                    <hr>

                    <div class="columns" id="chooseCaptureType">

                        <div class="column">
                            <button class="button is-info is-large" id="useWebcam">Utiliser ma webcam</button>
                        </div>

                        <div class="column">
                            <div class="file is-large">
                                <label class="file-label">
                                    <input class="file-input" type="file" name="photo" accept="image/*">
                                    <span class="file-cta">
                                        <span class="file-icon">
                                            <i class="fa fa-upload"></i>
                                        </span>
                                        <span class="file-label">Choisir une photo…</span>
                                    </span>
                                </label>
                            </div>
                        </div>

                    </div>

                    <div id="capture">
                        <div id="webcamVideo">
                            <div id="mask"></div>
                            <article class="message is-info">
                                <div class="message-body">
                                    Chargement en cours...
                                </div>
                            </article>
                            <video style="display: none"></video>
                        </div>
                        <br>
                        <button class="button is-success is-pulled-right" id="takePicture" disabled>Prendre une photo</button>
                        <div class="is-clearfix"></div>
                        <canvas id="webcamResult"></canvas>
                    </div>

                    <hr>

                   <div id="filters">

                       <figure class="image is-128x128">
                           <a class="add-mask" href="" id="doge"><img src="<?= $this->url('/assets/img/masks/doge.png') ?>"></a>
                       </figure>

                       <figure class="image is-128x128">
                           <a class="add-mask" href="" id="grumpycat"><img src="<?= $this->url('/assets/img/masks/grumpycat.png') ?>"></a>
                       </figure>

                   </div>

                </div>
            </div>

            <div class="column">
                <div class="box">

                    <h3>Historique</h3>
                    <hr>

                    <div id="history">
                        <?php foreach ($posts as $post): ?>

                            <figure class="image post-image" data-post-id="<?= $post->id ?>">
                                <img src="<?= $this->url('/assets/img/uploads/post-' . $post->id . '.png') ?>">
                            </figure>

                        <?php endforeach; ?>
                        <?php if (empty($posts)): ?>
                            <article class="message is-danger">
                                <div class="message-body">
                                    Vous n'avez encore rien posté.
                                </div>
                            </article>
                        <?php endif; ?>
                    </div>

                </div>
            </div>

        </div>

    </div>
</section>
<script type="text/javascript">
    var ROOT_URL = '<?= $this->url('/') ?>';
</script>
<script type="text/javascript" src="<?= $this->url('/assets/js/post.js') ?>"></script>
<?= $this->template('footer') ?>