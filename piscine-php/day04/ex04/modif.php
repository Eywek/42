<?php
// Utils
function in_array_r($needle, $haystack) {
    foreach ($haystack as $item)
        if ($item == $needle || (is_array($item) && in_array_r($needle, $item)))
            return $haystack;
    return false;
}

// Validation
if (!$_POST || !isset($_POST['submit']) || $_POST['submit'] !== "OK")
    exit("ERROR\n");
if (!isset($_POST['login']) || empty($_POST['login']) || !isset($_POST['oldpw']) || empty($_POST['oldpw']) || !isset($_POST['newpw']) || empty($_POST['newpw']))
    exit("ERROR\n");

// Get users
$users = @file_get_contents('../private/passwd');
if (!$users)
    exit("ERROR\n");
$users = unserialize($users);

// Find user
$found = false;
foreach ($users as $i => $user) {
    if ($user['login'] != $_POST['login'])
        continue;
    if ($user['passwd'] !== hash('sha256', $_POST['oldpw']))
        exit("ERROR\n");
    $users[$i]['passwd'] = hash('sha256', $_POST['newpw']);
    $found = true;
}
if (!$found)
    exit("ERROR\n");

// Save
file_put_contents('../private/passwd', serialize($users));

// OK
header('Location: index.html');
echo "OK\n";