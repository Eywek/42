<?php

namespace Routing;

class View
{

    private $_name;
    private $_vars;

    public function __construct($name, $vars)
    {
        $this->_name = $name;
        $this->_vars = $vars;
    }

    public function render($viewName)
    {
        // VARS
        foreach ($this->_vars as $name => $value)
            $$name = $value;

        // TO STRING
        ob_start();
        require VIEW_PATH . $viewName . '.php';
        $html = ob_get_clean();
        return $html;
    }

    public function url($path = '/')
    {
        $currentUrl = "http" . (isset($_SERVER['HTTPS']) ? 's' : '') . "://$_SERVER[HTTP_HOST]$_SERVER[REQUEST_URI]";
        if ($path[0] === '/')
            $path = substr($path, 1);
        return $currentUrl . $path;
    }

    public function __toString()
    {
        return $this->render($this->_name);
    }

    public function template($name)
    {
        return $this->render('Templates' . DS . $name);
    }

}