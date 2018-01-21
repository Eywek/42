<?= $this->template('head') ?>
<section class="hero is-info">
    <div class="container">
        <div class="hero-body">
            <p class="title">
                <?= $user->username ?>
            </p>
            <p class="subtitle has-text-weight-light is-italic">
                Inscrit depuis le <span class="has-text-weight-semibold	"><?= $user->created_at ?></span>
            </p>
        </div>
    </div>
</section>
<section class="section">
    <div class="container">

        <div class="box">

            <h3 class="title is-3">Modifier mes informations</h3>

            <hr>

            <form action="<?= $this->url('/user/edit') ?>" method="post" data-ajax>

                <div class="ajax-msg" style="margin-bottom: 10px"></div>

                <div class="field">
                    <label class="label">Pseudo</label>
                    <div class="control has-icons-left">
                        <input class="input" type="text" name="username" value="<?= $user->username ?>">
                        <span class="icon is-small is-left">
                      <i class="fa fa-user"></i>
                    </span>
                    </div>
                </div>

                <div class="field">
                    <label class="label">Email</label>
                    <div class="control has-icons-left">
                        <input class="input" type="email" name="email" value="<?= $user->email ?>">
                        <span class="icon is-small is-left">
                      <i class="fa fa-envelope"></i>
                    </span>
                    </div>
                </div>

                <button type="submit" class="button is-info is-pulled-right">
                    <i class="fa fa-save"></i>
                    &nbsp;Sauvegarder
                </button>

            </form>

            <div class="is-clearfix"></div>

        </div>

        <div class="box">

            <h3 class="title is-3">Modifier mon mot de passe</h3>

            <hr>

            <form action="<?= $this->url('/user/edit-password') ?>" method="post" data-ajax>

                <div class="ajax-msg" style="margin-bottom: 10px"></div>

                <div class="field">
                    <label class="label">Mot de passe</label>
                    <div class="control">
                        <input class="input" type="password" name="password" placeholder="Veuillez entrer un mot de passe sécurisé">
                    </div>
                </div>

                <div class="field">
                    <label class="label">Confirmation du mot de passe</label>
                    <div class="control">
                        <input class="input" type="password" name="password_confirmation" placeholder="Veuillez entrer un mot de passe sécurisé">
                    </div>
                </div>

                <button type="submit" class="button is-info is-pulled-right">
                    <i class="fa fa-save"></i>
                    &nbsp;Sauvegarder
                </button>

            </form>

            <div class="is-clearfix"></div>

        </div>

        <div class="box">

            <h3 class="title is-3">Mes préférences</h3>

            <hr>

            <label class="checkbox">
                <input type="checkbox" id="preferences-send-email" <?= $user->settings->email_notifications ? 'checked' : '' ?>>
                &nbsp;Me notifier par email quand quelqu'un commente ma publication
            </label>

        </div>

    </div>
</section>
<script>
    window.onload = function ()
    {
        document.querySelector('#preferences-send-email').addEventListener('change', function (e) {
            sendPOSTRequest('<?= $this->url('/user/edit-settings') ?>', {email_notifications: this.checked}, function () {});
        })
    }
</script>
<?= $this->template('footer') ?>
