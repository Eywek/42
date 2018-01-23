<nav class="navbar" role="navigation" aria-label="dropdown navigation">
    <div class="container">

        <div class="navbar-brand">
            <a href="<?= $this->url('/') ?>" class="navbar-item">
                InstaGru
            </a>
            <div class="navbar-burger burger" data-target="navbar">
                <span></span>
                <span></span>
                <span></span>
            </div>
        </div>

        <div class="navbar-menu" id="navbar">
            <div class="navbar-start">

                <div class="navbar-item">
                    <a class="button is-primary <?= \Models\UserModel::isLogged() ? '' : 'toggle-modal' ?>" href="<?= \Models\UserModel::isLogged() ? $this->url('/post') : '#signinModal' ?>">
                        <i class="fa fa-plus"></i>&nbsp;&nbsp;
                        Poster une image
                    </a>
                </div>

            </div>
            <div class="navbar-end">
                <div class="navbar-item">
                    <div class="field is-grouped">
                        <?php if (\Models\UserModel::isLogged()): ?>
                            <p class="control">
                                <a href="<?= $this->url('/account') ?>" class="bd-tw-button button is-link">
                                    <span><i class="fa fa-user"></i> &nbsp;Mon compte</span>
                                </a>
                            </p>
                            <p class="control">
                                <a href="<?= $this->url('/user/signout') ?>" class="bd-tw-button button">
                                    <span>Se déconnecter</span>
                                </a>
                            </p>
                        <?php else: ?>
                            <p class="control">
                                <a href="#signinModal" class="bd-tw-button button is-link toggle-modal">
                                    <span>Se connecter</span>
                                </a>
                            </p>
                            <p class="control">
                                <a href="#signupModal" class="bd-tw-button button is-info toggle-modal">
                                    <span>S'inscrire</span>
                                </a>
                            </p>
                        <?php endif; ?>
                    </div>
                </div>
            </div>
        </div>

    </div>
</nav>