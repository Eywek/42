<?php
function signup($data, $is_admin = false)
{
    // Validate data
    if (($error = validate([
        'first_name' => [
            'name' => 'Prénom',
            'rules' => ['not_empty', 'min_length' => 2, 'max_length' => 255]
        ],
        'name' => [
            'name' => 'Nom',
            'rules' => ['not_empty', 'min_length' => 2, 'max_length' => 255]
        ],
        'email' => [
            'name' => 'Email',
            'rules' => ['not_empty', 'min_length' => 6, 'max_length' => 255, 'email']
        ],
        'password' => [
            'name' => 'Mot de passe',
            'rules' => ['not_empty', 'min_length' => 8]
        ],
        'password_confirmation' => [
            'name' => 'Confirmation du mot de passe',
            'rules' => ['not_empty', 'min_length' => 8]
        ]
    ], $data)) !== true)
        return $error;
    if ($data['password'] !== $data['password_confirmation'])
        return "Le champ Mot de passe doit être identique au contenu du champ Confirmation de mot de passe !";
    $findUserWithThisEmail = queryDB('SELECT id FROM users WHERE email = ?', ['s', $data['email']]);
    if ($findUserWithThisEmail && !empty($findUserWithThisEmail))
        return "L'email est déjà utilisé par un autre utilisateur !";
    // Prepare data
    $user = sanitize([
        'first_name' => $data['first_name'],
        'name' => $data['name'],
        'email' => $data['email'],
        'password' => hashPassword($data['password']),
        'created_at' => date('Y-m-d H:i:s')
    ]);
    $req = queryDB('INSERT INTO users VALUES(NULL, ?, ?, ?, ?, ' . ($is_admin ? '1' : '0') . ', ?)', [
        'sssss',
        $user['first_name'], $user['name'], $user['email'], $user['password'], $user['created_at']
    ]);
    if ($req instanceof Error)
        return 'Une erreur interne est survenue';
    $user = queryDB('SELECT id FROM users WHERE email = ?', ['s', $data['email']]);
    return $user[0]['id'];
}

function edit($data, $userId = null)
{
    if (empty($userId))
        $userId = $_SESSION['user'];
    // Validate data
    if (($error = validate([
            'first_name' => [
                'name' => 'Prénom',
                'rules' => ['not_empty', 'min_length' => 2, 'max_length' => 255]
            ],
            'name' => [
                'name' => 'Nom',
                'rules' => ['not_empty', 'min_length' => 2, 'max_length' => 255]
            ],
            'email' => [
                'name' => 'Email',
                'rules' => ['not_empty', 'min_length' => 6, 'max_length' => 255, 'email']
            ]
        ], $data)) !== true)
        return $error;
    if (!empty($data['password']) && $data['password'] !== $data['password_confirmation'])
        return "Le champ Mot de passe doit être identique au contenu du champ Confirmation de mot de passe !";
    $findUserWithThisEmail = queryDB('SELECT id FROM users WHERE email = ? AND id != ?', ['si', $data['email'], $userId]);
    if ($findUserWithThisEmail && !empty($findUserWithThisEmail))
        return "L'email est déjà utilisé par un autre utilisateur !";
    // Prepare data
    $user = sanitize([
        'first_name' => $data['first_name'],
        'name' => $data['name'],
        'email' => $data['email']
    ]);
    if (!empty($data['password']))
        $user['password'] = hashPassword($data['password']);
    else
        $user['password'] = getUser()['password'];
    $req = queryDB('UPDATE users SET first_name = ?, name = ?, email = ?, password = ? WHERE id = ?', [
        'ssssi',
        $user['first_name'], $user['name'], $user['email'], $user['password'], $userId
    ]);
    if ($req instanceof Error)
        return 'Une erreur interne est survenue';
    return true;
}

function login($value, $password = NULL, $key = 'id')
{
    // Check if userId exist
    $user = queryDB("SELECT id, password FROM users WHERE $key = ? LIMIT 1", ['s', $value]);
    if (!$user)
        return false;
    // If password !== NULL, check if valid
    if ($password !== NULL && hashPassword($password) !== $user[0]['password'])
        return false;
    // Log the user with the session
    $_SESSION['user'] = $user[0]['id'];
    return true;
}

function redirectIfNotLogged()
{
    if (!getUser()) {
        header('Location: signin.php');
        exit();
    }
}

function redirectIfNotAdmin()
{
    if (!($user = getUser()) || !$user['is_admin']) {
        header('Location: ../index.php');
        exit();
    }
}

function getUser()
{
    if (!isset($_SESSION['user']))
        return false;
    $userId = $_SESSION['user'];
    $user = queryDB('SELECT * FROM users WHERE id = ? LIMIT 1', ['i', $userId]);
    if (!$user)
        return false;
    return $user[0];
}

function deleteUser($userId)
{
    return queryDB('DELETE FROM users WHERE `id` = ?', ['i', $userId]);
}

function logout()
{
    unset($_SESSION['user']);
}