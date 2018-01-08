<?php

function ft_is_sort($array)
{
    $dup = array_merge([], $array);
    sort($dup);
    return $array === $dup;
}