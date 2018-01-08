#!/usr/bin/php
<?php
if ($argc > 1)
    echo trim(preg_replace('/ +/', ' ', $argv[1])) . "\n";