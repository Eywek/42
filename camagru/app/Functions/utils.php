<?php

function getIP()
{
    return $_SERVER['REMOTE_ADDR'];
}

function sendMail($email, $title, $content)
{
    $headers = "From: camagru@42.fr\r\n";
    $headers .= "MIME-Version: 1.0\r\n";
    $headers .= "Content-Type: text/html; charset=UTF-8\r\n";

    return mail($email, $title, $content, $headers);
}

function toPlural($str)
{
    if (substr($str, -1) == 'y')
        $str = substr($str, 0, -1) . 'ies';
    else
        $str .= 's';
    return $str;
}

function url($path = '/')
{
    $currentUrl = "http" . (isset($_SERVER['HTTPS']) ? 's' : '') . "://$_SERVER[HTTP_HOST]$_SERVER[REQUEST_URI]";
    if (!isset($_GET['path']))
        $_GET['path'] = '';
    $_GET['path'] = '/' . $_GET['path'];
    $currentUrl = substr($currentUrl, 0, -strlen($_GET['path']));
    if ($path[0] === '/')
        $path = substr($path, 1);
    if (REWRITE_URL)
        return $currentUrl . $path;
    if (strpos($currentUrl, '?path=') !== false)
        $currentUrl = substr($currentUrl, 0, -strlen(substr($currentUrl, strpos($currentUrl, '?path='))));
    return $currentUrl . '?path=' . $path;
}