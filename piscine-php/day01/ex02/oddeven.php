#!/usr/bin/php
<?php
while (42)
{
    echo "Entrez un nombre: ";
    $fd = fopen("php://stdin","r");
    $line = fgets($fd);
    if (!$line)
        break;
    $number = trim($line);
    fclose($fd);
    if (is_numeric($number))
        echo "Le chiffre $number est " . (intval($number) % 2 ? 'Impair' : 'Pair') . "\n";
    else
        echo "'$number' n'est pas un chiffre\n";
}
