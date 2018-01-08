#!/usr/bin/php
<?php
if ($argc < 2 || !file_exists($argv[1]))
    exit(1);
$content = file_get_contents($argv[1]);
echo preg_replace_callback('/<a [^>]+.*<\/a>/i', function ($matches) {
    var_dump($matches);
    // Setup a
    $result = $matches[0];

    // Replace title
    $result = preg_replace_callback('/title="(.*)"/i', function ($matches) {
        var_dump($matches);
        return 'title="' . strtoupper($matches[1]) . '"';
    }, $result);

    // Replace content
//    $result = preg_replace_callback('/>.*</i', function ($matches) {
//        var_dump($matches);
//        return strtoupper($matches[0]);
//    }, $result);

    $result = preg_replace_callback('/>.*</i', function ($matches) {
        $callback = function ($match) {
            return strtoupper($match[1]);
        };
        $regex = '/(\w+(?=&)|(?<=;)\w+)/';
        return preg_replace_callback($regex, $callback, $matches[0]);
    }, $result);

    return ($result);
}, $content);