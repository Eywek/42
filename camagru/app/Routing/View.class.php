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

    public function render()
    {
        // VARS
        foreach ($this->_vars as $name => $value)
            $$name = $value;

        // TO STRING
        ob_start();
        require VIEW_PATH . $this->_name . '.php';
        $html = ob_get_clean();
        return $html;
    }

    public function __toString()
    {
        return $this->render();
    }

}