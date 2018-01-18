<?php

namespace Core;

class Autoloader
{

    public static function register(){
        spl_autoload_register(array(__CLASS__, 'autoload'));
    }

    public static function autoload($class){
        $parts = preg_split('#\\\#', $class);
        $className = array_pop($parts);

        $path = implode(DS, $parts);
        $file = $className . '.class.php';
        $filepath = APP_PATH . $path . DS . $file;

        require $filepath;
    }

}