<?php
if ($_GET && isset($_GET['action'])) {

    switch ($_GET['action']) {
        case 'set':
            if (!isset($_GET['name']) || !isset($_GET['value']))
                break;
            setcookie($_GET['name'], $_GET['value']);
            break;
        case 'get':
            if (!isset($_GET['name']) || !isset($_COOKIE[$_GET['name']]))
                break;
            echo $_COOKIE[$_GET['name']];
            break;
        case 'del':
            if (!isset($_GET['name']) || !isset($_COOKIE[$_GET['name']]))
                break;
            setcookie($_GET['name'], "", -1);
            break;
    }

}
