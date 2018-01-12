<?php
$db = NULL;

/*
 * Utils functions
 */

function initDB()
{
    global $db;
    if (!empty($db))
        return $db;
    // TODO: use an env
    $db = mysqli_connect("localhost", "my_user", "my_password", "world");

    // Check if failed
    if (mysqli_connect_errno()) {
        printf("Échec de la connexion à la base de données : %s\n", mysqli_connect_error());
        exit();
    }
}

function queryDB($query, array $params = [], $close = false)
{
    global $db;
    initDB();
    $results = [];

    // Prepare
    $query = mysqli_prepare($db, $query);

    // Add params
    foreach ($params as $name => $value)
        mysqli_stmt_bind_param($query, $name, $value);

    // Execute and get result
    mysqli_stmt_execute($query);
    mysqli_stmt_bind_result($query, $results);
    mysqli_stmt_fetch($query);

    // Close
    mysqli_stmt_close($query);
    if ($close)
        closeDB();

    return $results;
}

function closeDB()
{
    global $db;
    mysqli_close($db);
}