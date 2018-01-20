<?php


namespace Routing;


class Request
{

    private $_path;
    private $_method;
    private $_data;
    private $_args = [];

    public function __construct($path = '/', $method = 'GET', $data = [])
    {
        if (substr($path, 0, 1) != '/')
            $path = '/' . $path;
        $this->_path = $path;
        $this->_method = $method;
        $this->_data = $data;
    }

    public function __get($name)
    {
        if (isset($this->_args[$name]))
            return $this->_args[$name];
        return NULL;
    }

    /**
     * @return mixed
     */
    public function getPath()
    {
        return $this->_path;
    }

    /**
     * @return mixed
     */
    public function getMethod()
    {
        return $this->_method;
    }

    /**
     * @return mixed
     */
    public function getData()
    {
        return $this->_data;
    }

    /**
     * @return mixed
     */
    public function getArgs()
    {
        return $this->_args;
    }

    /**
     * @param mixed $args
     */
    public function setArgs($args)
    {
        $this->_args = $args;
    }

}