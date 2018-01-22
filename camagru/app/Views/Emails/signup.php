<?= $this->template('email-head') ?>
<!-- START CENTERED WHITE CONTAINER -->
<span class="preheader">Merci de votre inscription !</span>
<table class="main">

    <!-- START MAIN CONTENT AREA -->
    <tr>
        <td class="wrapper">
            <table border="0" cellpadding="0" cellspacing="0">
                <tr>
                    <td>
                        <p>Bonjour <b><?= $username ?></b>,</p>
                        <p>Nous avons besoin que vous validiez votre email pour pouvoir vous connecter à notre site.</p>
                        <table border="0" cellpadding="0" cellspacing="0" class="btn btn-primary">
                            <tbody>
                            <tr>
                                <td align="left">
                                    <table border="0" cellpadding="0" cellspacing="0">
                                        <tbody>
                                        <tr>
                                            <td> <a href="<?= $url ?>" target="_blank">Valider mon email.</a> </td>
                                        </tr>
                                        </tbody>
                                    </table>
                                </td>
                            </tr>
                            </tbody>
                        </table>
                    </td>
                </tr>
            </table>
        </td>
    </tr>

    <!-- END MAIN CONTENT AREA -->
</table>
<?= $this->template('email-footer') ?>
