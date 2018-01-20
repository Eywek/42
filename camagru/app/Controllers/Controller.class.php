<?php


namespace Controllers;


class Controller
{

    private $_vars = [];

    public function getVars()
    {
        return $this->_vars;
    }

    protected function set($vars = [])
    {
        foreach ($vars as $name => $value)
            $this->_vars[$name] = $value;
    }

}