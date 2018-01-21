<div class="modal" id="signinModal">
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
                    <a class="button is-info toggle-modal" href="#signupModal">S'inscire</a>
                    <button class="button is-link is-pulled-right" type="submit">Se connecter</button>
                </footer>
            </form>
        </div>

    </div>
    <button class="modal-close is-large" aria-label="close"></button>
</div>

<div class="modal" id="lostPasswordModal">
    <div class="modal-background"></div>
    <div class="modal-content">

        <div class="modal-card">
            <header class="modal-card-head">
                <p class="modal-card-title">J'ai oublié mon mot de passe</p>
            </header>
            <form method="post" action="<?= $this->url('/user/lost-password') ?>" data-ajax>
                <section class="modal-card-body">

                    <div class="notification is-info has-text-weight-light is-italic">
                        Un email de rénitialisation va vous être envoyé pour modifier votre mot de passe.
                    </div>

                    <div class="ajax-msg" style="margin-bottom: 5px"></div>

                    <div class="field">
                        <label class="label">Email</label>
                        <div class="control">
                            <input class="input" type="email" name="email">
                        </div>
                    </div>

                </section>
                <footer class="modal-card-foot">
                    <a class="button is-link toggle-modal" href="#signinModal">Se connecter</a>
                    <button class="button is-info is-pulled-right" type="submit">Envoyez moi un email</button>
                </footer>
            </form>
        </div>

    </div>
    <button class="modal-close is-large" aria-label="close"></button>
</div>

<div class="modal" id="signupModal">
    <div class="modal-background"></div>
    <div class="modal-content">

        <div class="modal-card">
            <header class="modal-card-head">
                <p class="modal-card-title">S'inscrire</p>
            </header>
            <form method="post" action="<?= $this->url('/user/signup') ?>" data-ajax>
                <section class="modal-card-body">

                    <div class="ajax-msg" style="margin-bottom: 5px"></div>

                    <div class="field">
                        <label class="label">Identifiant</label>
                        <div class="control">
                            <input class="input" type="text" name="username">
                        </div>
                    </div>

                    <div class="field">
                        <label class="label">Email</label>
                        <div class="control">
                            <input class="input" type="email" name="email">
                        </div>
                    </div>

                    <div class="field">
                        <label class="label">Mot de passe</label>
                        <div class="control">
                            <input class="input" type="password" name="password">
                        </div>
                    </div>

                    <div class="field">
                        <label class="label">Confirmation du mot de passe</label>
                        <div class="control">
                            <input class="input" type="password" name="password_confirmation">
                        </div>
                    </div>

                </section>
                <footer class="modal-card-foot">
                    <a class="button is-link toggle-modal" href="#signinModal">Se connecter</a>
                    <button class="button is-info is-pulled-right" type="submit">S'inscrire</button>
                </footer>
            </form>
        </div>

    </div>
    <button class="modal-close is-large" aria-label="close"></button>
</div>