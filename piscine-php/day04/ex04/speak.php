<?php
session_start();

if ($_POST && isset($_POST['msg']) && !empty($_POST['msg']) && isset($_SESSION['loggued_on_user']) && !empty($_SESSION['loggued_on_user'])) {

    if (!file_exists('../private/chat')) {
        if (!is_dir('../private'))
            mkdir('../private');
        file_put_contents('../private/chat', serialize([]));
    }
    $fd = fopen('../private/chat', 'r');
    if (flock($fd, LOCK_EX)) {
        $messages = unserialize(file_get_contents('../private/chat'));
        if (!$messages)
            $messages = [];
        $messages[] = [
            'login' => $_SESSION['loggued_on_user'],
            'time' => time(),
            'msg' => htmlentities($_POST['msg'])
        ];
        file_put_contents('../private/chat', serialize($messages));
        flock($fd, LOCK_UN);
        fclose($fd);
    }
}
?>
<!DOCTYPE html>
<html>
    <head>
        <script language="javascript">
            top.frames['chat'].location = 'chat.php';
        </script>
    </head>
    <body>
        <form action="" method="post">
            <input type="text" name="msg" placeholder="Message">
            <button type="submit">Envoyer le message</button>
        </form>
    </body>
</html>