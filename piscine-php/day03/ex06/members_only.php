<?php
function forbidden()
{
    header('WWW-Authenticate: Basic realm="Espace membre"');
    header('HTTP/1.0 401 Unauthorized');
    echo "<html><body>Cette zone est accessible uniquement aux membres du site</body></html>";
    die();
}
// Login
if (!isset($_SERVER['PHP_AUTH_USER']) || !isset($_SERVER['PHP_AUTH_PW']))
    forbidden();
if ($_SERVER['PHP_AUTH_USER'] !== 'zaz' || $_SERVER['PHP_AUTH_PW'] !== 'jaimelespetitsponeys')
    forbidden();
?>
<html>
    <body>
        Bonjour Zaz<br />
        <img src="data:image/png;base64,<?= base64_encode(file_get_contents('../img/42.png')) ?>" alt="">
    </body>
</html>
