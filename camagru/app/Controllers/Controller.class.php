<?php


namespace Controllers;


class Controller
{

    private $_vars = [];

    /**
     * @return array
     */
    public function getVars(): array
    {
        return $this->_vars;
    }

    protected function set($vars = [])
    {
        foreach ($vars as $name => $value)
            $this->_vars[$name] = $value;
    }

}