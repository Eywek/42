<?= $this->template('email-head') ?>
<!-- START CENTERED WHITE CONTAINER -->
<span class="preheader">Changez votre mot de passe !</span>
<table class="main">

    <!-- START MAIN CONTENT AREA -->
    <tr>
        <td class="wrapper">
            <table border="0" cellpadding="0" cellspacing="0">
                <tr>
                    <td>
                        <p>Bonjour <b><?= $username ?></b>,</p>
                        <p>Vous avez demandé un lien de rénitialisation pour votre mot de passe.</p>
                        <table border="0" cellpadding="0" cellspacing="0" class="btn btn-primary">
                            <tbody>
                            <tr>
                                <td align="left">
                                    <table border="0" cellpadding="0" cellspacing="0">
                                        <tbody>
                                        <tr>
                                            <td> <a href="<?= $url ?>" target="_blank">Changer mon mot de passe.</a> </td>
                                        </tr>
                                        </tbody>
                                    </table>
                                </td>
                            </tr>
                            </tbody>
                        </table>
                        <p>Vous avez fait la demander depuis l'IP <b><?= $ip ?></b> le <b><?= $date ?></b>.</p>
                    </td>
                </tr>
            </table>
        </td>
    </tr>

    <!-- END MAIN CONTENT AREA -->
</table>
<?= $this->template('email-footer') ?>
