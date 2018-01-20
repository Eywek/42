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