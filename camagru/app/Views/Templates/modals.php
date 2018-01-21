<div class="modal" id="loginModal">
    <div class="modal-background"></div>
    <div class="modal-content">

        <div class="modal-card">
            <header class="modal-card-head">
                <p class="modal-card-title">Se connecter</p>
            </header>
            <form method="post" action="<?= $this->url('/user/signin') ?>" data-ajax>
                <section class="modal-card-body">

                    <div class="ajax-msg" style="margin-bottom: 5px"></div>

                    <div class="field">
                        <label class="label">Identifiant</label>
                        <div class="control">
                            <input class="input" type="text" name="username">
                        </div>
                    </div>

                    <div class="field">
                        <label class="label">
                            Mot de passe
                            <small><em><a href="#lostPasswordModal" class="toggle-modal has-text-weight-light">Vous avez oublié votre mot de passe ?</a></em></small>
                        </label>
                        <div class="control">
                            <input class="input" type="password" name="password">
                        </div>
                    </div>

                </section>
                <footer class="modal-card-foot">
                    <button class="button is-link">S'inscire</button>
                    <button class="button is-info is-pulled-right" type="submit">Se connecter</button>
                </footer>
            </form>
        </div>

    </div>
    <button class="modal-close is-large" aria-label="close"></button>
</div>