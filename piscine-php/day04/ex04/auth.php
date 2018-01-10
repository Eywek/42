<?php
function auth($login, $passwd) {
    // Get users
    $users = @file_get_contents('../private/passwd');
    if (!$users)
        return false;
    $users = unserialize($users);

    // Find user
    foreach ($users as $i => $user) {
        if ($user['login'] != $login)
            continue;
        if ($user['passwd'] !== hash('sha256', $passwd))
            return false;
        return true;
    }
    return false;
}