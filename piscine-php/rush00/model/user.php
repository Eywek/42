<?php
function signup($data)
{
    // Validate data
    if (!($error = validate([
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
    ], $data)))
        return $error;
    if ($data['password'] !== $data['password_confirmation'])
        return "Le champ Mot de passe doit être identique au contenu du champ Confirmation de mot de passe !";
    // TODO: Check if email is unique
    // Prepare data
    $user = sanitize([
        'first_name' => $data['first_name'],
        'name' => $data['name'],
        'email' => $data['email'],
        'password' => hashPassword($data['password']),
        'created_at' => date('Y-m-d H:i:s')
    ]);
    // TODO: Save the user
    // TODO: Return the user id
    return 1;
}

function login($userId, $password = NULL) // TODO
{
    // Check if userId exist
    $user = queryDB('SELECT id, password FROM users WHERE id = ? LIMIT 1', ['i' => $userId]);
    if (!$user)
        return false;
    // If password !== NULL, check if valid
    if ($password !== NULL && hashPassword($password) !== $user[0]['password'])
        return false;
    // Log the user with the session
    $_SESSION['user'] = $user[0]['id'];
    return true;
}

function logout()
{
    session_destroy();
}