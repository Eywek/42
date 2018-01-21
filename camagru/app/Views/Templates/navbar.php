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

                <a class="navbar-item" href="<?= $this->url('/') ?>">
                    Home
                </a>

                <div class="navbar-item has-dropdown">
                    <a class="navbar-link">
                        Docs
                    </a>

                    <div class="navbar-dropdown">
                        <a class="navbar-item">
                            Overview
                        </a>
                        <a class="navbar-item">
                            Elements
                        </a>
                        <a class="navbar-item">
                            Components
                        </a>
                        <hr class="navbar-divider">
                        <div class="navbar-item">
                            Version 0.6.2
                        </div>
                    </div>
                </div>

            </div>
            <div class="navbar-end">
                <div class="navbar-item">
                    <div class="field is-grouped">
                        <p class="control">
                            <a href="#loginModal" class="bd-tw-button button is-link toggle-modal">
                                <span>Se connecter</span>
                            </a>
                        </p>
                        <p class="control">
                            <a class="bd-tw-button button is-info">
                                <span>S'inscrire</span>
                            </a>
                        </p>
                    </div>
                </div>
            </div>
        </div>

    </div>
</nav>