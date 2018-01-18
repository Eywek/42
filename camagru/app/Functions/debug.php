<?php
/*
 * Debug functions, call var_dump
 */

function debug()
{
    echo '<pre>';
    call_user_func_array('var_dump', func_get_args());
    echo '</pre>';
}

function print_trace()
{
    debug_print_backtrace();
}