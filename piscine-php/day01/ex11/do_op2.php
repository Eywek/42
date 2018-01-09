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

$operationString = trim(preg_replace('/ +/', '', $argv[1]));
if (strpos($operationString, '+') !== false)
    $operation = '+';
else if (strpos($operationString, '-') !== false)
    $operation = '-';
else if (strpos($operationString, '*') !== false)
    $operation = '*';
else if (strpos($operationString, '/') !== false)
    $operation = '/';
else if (strpos($operationString, '%') !== false)
    $operation = '%';
else
    syntax_error();
$operationString = explode($operation, $operationString);
if (count($operationString) != 2 || !is_numeric($operationString[0]) || !is_numeric($operationString[1]))
    syntax_error();
$first = intval($operationString[0]);
$second = intval($operationString[1]);

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
