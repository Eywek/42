#!/usr/bin/php
<?php
if ($argc < 2)
    exit(1);

// First request
$req = curl_init();
$curl_options = [
    CURLOPT_URL => $argv[1],
    CURLOPT_HEADER => false,
    CURLOPT_RETURNTRANSFER => true,
    CURLOPT_FOLLOWLOCATION => true
];
curl_setopt_array($req, $curl_options);
$body = curl_exec($req);
curl_close($req);

// Failed
if (!$body)
    exit(1);
$website = $argv[1];
$website = substr($website, strlen('http://') + (strpos($website, 'https') !== false));
if (substr($website, -1) !== '/')
    $website .= '/';

// Get all images
if (!preg_match_all('/<img[^>]+\/?>/i', $body, $matches))
    exit(0);

// Each of them
foreach ($matches[0] as $match) {
    // Match src
    if (!preg_match('/src\s*=\s*("|\')(.+?)("|\')/i', $match, $url) || !isset($url[2]) || empty($url[2]))
        continue;
    // set url
    $url = $url[2];
    if (strpos($url, 'http') === false)
        $url = $argv[1] . '/' . $url;
    // get it
    $req = curl_init();
    $curl_options[CURLOPT_URL] = $url;
    curl_setopt_array($req, $curl_options);
    $body = curl_exec($req);
    curl_close($req);
    // Save
    if (!is_dir($website))
        mkdir($website);
    $img_name = basename($url);
    file_put_contents($website . $img_name, $body);
}
