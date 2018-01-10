<?php
// Utils
function in_array_r($needle, $haystack) {
    foreach ($haystack as $item)
        if ($item == $needle || (is_array($item) && in_array_r($needle, $item)))
            return true;
    return false;
}

// Validation
if (!$_POST || !isset($_POST['submit']) || $_POST['submit'] !== "OK")
    exit("ERROR\n");
if (!isset($_POST['login']) || empty($_POST['login']) || !isset($_POST['passwd']) || empty($_POST['passwd']))
    exit("ERROR\n");

// Get users
$users = @file_get_contents('../private/passwd');
if (!$users) {
    $users = [];
    mkdir('../private');
}
else
    $users = unserialize($users);

// Check if already registered
if (in_array_r($_POST['login'], $users))
    exit("ERROR\n");

// Add user
$users[] = [
    'login' => $_POST['login'],
    'passwd' => hash('sha256', $_POST['passwd'])
];

// Save
file_put_contents('../private/passwd', serialize($users));

// OK
header('Location: index.html');
echo "OK\n";