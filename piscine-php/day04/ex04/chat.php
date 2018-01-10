<!DOCTYPE html>
<html>
    <head>
    </head>
    <body>
        <?php
            date_default_timezone_set('Europe/Paris');

            if (!file_exists('../private/chat')) {
                if (!is_dir('../private'))
                    mkdir('../private');
                file_put_contents('../private/chat', serialize([]));
            }
            $fd = fopen('../private/chat', 'r');
            $messages = [];
            if (flock($fd, LOCK_SH)) {
                $messages = unserialize(file_get_contents('../private/chat'));
                if (!$messages)
                    $messages = [];
                flock($fd, LOCK_UN);
                fclose($fd);
            }

            foreach ($messages as $message)
                echo "<b>{$message['login']}:</b> {$message['msg']} <small><em>(" . date('H:i:s', $message['time']) . ")</em></small><br>";
        ?>
    </body>
</html>
