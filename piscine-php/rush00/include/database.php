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
    $config = getConfig();
    $db = @mysqli_connect($config['database']['host'], $config['database']['user'], $config['database']['password'], $config['database']['database']);

    // Check if failed
    if (mysqli_connect_errno()) {
        printf("Échec de la connexion à la base de données : %s\n", mysqli_connect_error());
        exit();
    }
    mysqli_set_charset($db, "utf8");
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

    // Prepare
    if (!($query = mysqli_prepare($db, $queryString)))
        return new Error('MYSQL ERROR CODE: ' . mysqli_errno($db));

    // Add params
    if (!empty($params)) {
        $params = array_merge([$query], $params);
        call_user_func_array('mysqli_stmt_bind_param', refValues($params));
    }

    // Execute and get result
    if (!mysqli_stmt_execute($query))
        return new Error('MYSQL ERROR CODE: ' . mysqli_errno($db));
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
    $db = NULL;
}