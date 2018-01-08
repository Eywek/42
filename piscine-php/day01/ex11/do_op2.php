#!/usr/bin/php
<?php
if ($argc != 2) {
    echo "Incorrect Parameters\n";
    exit(1);
}

function syntax_error()
{
    echo "Syntax Error\n";
    exit(1);
}

$operationString = trim(preg_replace('/ +/', ' ', $argv[1]));
$operationString = explode(' ', $operationString);
if (count($operationString) != 3 || !is_numeric($operationString[0]) || !is_numeric($operationString[2]))
    syntax_error();
$first = intval($operationString[0]);
$operation = $operationString[1];
$second = intval($operationString[2]);

if (!in_array($operation, ['+', '-', '*', '/', '%']))
    syntax_error();
if ($second === 0 && in_array($operation, ['/', '%']))
    syntax_error();

switch ($operation) {
    case '+':
        echo $first + $second . "\n";
        break;
    case '-':
        echo $first - $second . "\n";
        break;
    case '*':
        echo $first * $second . "\n";
        break;
    case '%':
        echo $first % $second . "\n";
        break;
    case '/':
        echo $first / $second . "\n";
        break;
    default:
        exit(1);
}
