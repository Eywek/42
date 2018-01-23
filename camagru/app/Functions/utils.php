<?php

function getIP()
{
    return $_SERVER['REMOTE_ADDR'];
}

function sendMail($email, $title, $content)
{
    $headers = "From: InstaGru <instagru@42.fr>\r\n";
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
    $_GET['path'] = '/' . trim($_GET['path'], '/');
    $currentUrl = substr($currentUrl, 0, -strlen($_GET['path'])) . '/';
    if ($path[0] === '/')
        $path = substr($path, 1);
    if (REWRITE_URL)
        return $currentUrl . $path;
    if (strpos($currentUrl, '?path') !== false)
        $currentUrl = substr($currentUrl, 0, strpos($currentUrl, '?path'));
    if (strpos($path,'assets/') !== false)
        return $currentUrl . 'public/' . $path;
    return $currentUrl . '?path=' . $path;
}

function imagecopymerge_alpha($dst_im, $src_im, $dst_x, $dst_y, $src_x, $src_y, $src_w, $src_h, $pct) {
    $cut = imagecreatetruecolor($src_w, $src_h);
    imagecopy($cut, $dst_im, 0, 0, $dst_x, $dst_y, $src_w, $src_h);
    imagecopy($cut, $src_im, 0, 0, $src_x, $src_y, $src_w, $src_h);
    imagecopymerge($dst_im, $cut, $dst_x, $dst_y, 0, 0, $src_w, $src_h, $pct);
}

function mergeImage($a, $b)
{
    // COPY
    $b = imagescale($b, imagesx($a) / 2.6);
    imagecopymerge_alpha($a, $b, imagesx($a) / 2 - imagesx($b) / 2, imagesy($a) / 2 - imagesy($b) / 2, 0, 0, imagesx($b), imagesy($b), 100);

    // SAVE TO $a
    imagesavealpha($a, true);

    // SAVE OUTPUT
    ob_start();
    imagepng($a);
    $result =  ob_get_contents();
    ob_end_clean();

    // DESTROY AND RETURN
    imagedestroy($a);
    imagedestroy($b);
    return $result;
}