#!/usr/bin/php
<?php
if ($argc < 2 || !file_exists($argv[1]))
    exit(1);
$content = file_get_contents($argv[1]);
echo preg_replace_callback('/<a [^>]+((?!<\/a>).|\n)*<\/a>/i', function ($matches) {
    // Setup a
    $result = $matches[0];

    // Replace content
    $result = preg_replace_callback('/>(.|\n)*</i', function ($matches) {
        // To upper
        $result = strtoupper($matches[0]);
        if (strpos(substr($matches[0], 1, strlen($matches[0]) - 2), '<') !== false) {
            // With html tags we need to lower html tags
            $result = preg_replace_callback('/<([^>]+)(>([^<>]*)<\/|)([^>]*)>/i', function ($matches) {
                $return = "<" . strtolower($matches[1]) . ">";
                if (!empty($matches[4]))
                    $return .= "$matches[3]</" . strtolower($matches[4]) . ">";
                return $return;
            }, $result);
        }

        // Return
        return $result;
    }, $result);

    // Replace title
    $result = preg_replace_callback('/title="(.*)"/i', function ($matches) {
        return 'title="' . strtoupper($matches[1]) . '"';
    }, $result);

    return ($result);
}, $content);