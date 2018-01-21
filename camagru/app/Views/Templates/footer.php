        <?= $this->template('modals') ?>

        <footer class="footer">
            <div class="container">
                <div class="content has-text-centered">
                    <p>
                        <strong>© <?= date('Y') ?> InstaGru</strong> by <a href="https://valentin-tft.fr">Valentin T</a>.
                    </p>
                </div>
            </div>
        </footer>

        <script type="application/javascript" src="<?= $this->url('/assets/js/navbar.js') ?>"></script>
        <script type="application/javascript" src="<?= $this->url('/assets/js/modals.js') ?>"></script>
        <script type="application/javascript" src="<?= $this->url('/assets/js/form.js') ?>"></script>

    </body>
</html>