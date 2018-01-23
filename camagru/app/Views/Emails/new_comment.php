<?= $this->template('email-head') ?>
<!-- START CENTERED WHITE CONTAINER -->
<span class="preheader">Un nouveau commentaire !</span>
<table class="main">

    <!-- START MAIN CONTENT AREA -->
    <tr>
        <td class="wrapper">
            <table border="0" cellpadding="0" cellspacing="0">
                <tr>
                    <td>
                        <p>Bonjour,</p>
                        <p>Un nouveau commentaire a été posté sur votre post <b><?= $title ?></b> par <b><?= $author ?></b>.</p>
                        <table border="0" cellpadding="0" cellspacing="0" class="btn btn-primary">
                            <tbody>
                            <tr>
                                <td align="left">
                                    <table border="0" cellpadding="0" cellspacing="0">
                                        <tbody>
                                        <tr>
                                            <td> <a href="<?= $this->url('/') ?>" target="_blank">Se rendre sur le site.</a> </td>
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
