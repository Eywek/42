<?php

function ft_split($str)
{
    return (explode(' ', preg_replace('/ +/', ' ', trim($str))));
}