<?= $this->template('head') ?>
<section class="hero is-info">
    <div class="container">
        <div class="hero-body">
            <p class="title">
                <?= $user->username ?>
            </p>
        </div>
    </div>
</section>
<section class="section">
    <div class="container">

        <div class="box">

            <h3 class="title is-3"><?= $title ?></h3>

            <hr>

            <form action="" method="post" data-ajax>

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

    </div>

</section>
<?= $this->template('footer') ?>