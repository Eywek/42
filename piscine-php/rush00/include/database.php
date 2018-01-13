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
    $db = mysqli_connect("149.202.102.52", "rush00", "N8dNpRJRqZLcxwyG", "rush00");

    // Check if failed
    if (mysqli_connect_errno()) {
        printf("Échec de la connexion à la base de données : %s\n", mysqli_connect_error());
        exit();
    }
}

function refValues($arr){
    $refs = array();
    foreach($arr as $key => $value)
        $refs[$key] = &$arr[$key];
    return $refs;
}

function queryDB($queryString, array $params = [], $close = false)
{
    global $db;
    initDB();
    $results = [];

    // Prepare
    $query = mysqli_prepare($db, $queryString);

    // Add params
    $params = array_merge([$query], $params);
    call_user_func_array('mysqli_stmt_bind_param', refValues($params));

    // Execute and get result
    mysqli_stmt_execute($query);
    $result = mysqli_stmt_get_result($query);
    $results = [];
    if ($result)
        while ($row = mysqli_fetch_array($result, MYSQLI_ASSOC))
            $results[] = $row;

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