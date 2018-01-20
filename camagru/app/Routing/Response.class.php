<?php


namespace Routing;


class Response
{

    private $_content;
    private $_type;
    private $_headers = [];

    public function __construct($content = '', $type = 'text/html')
    {
        $this->_content = $content;
        $this->_type = $type;
    }

    public function send()
    {
        $this->_sendHeaders();
        $this->_displayContent();
        exit();
    }

    private function _sendHeaders()
    {
        if ($this->_type != 'text/html')
            header('Content-Type: ' . $this->_type);
        foreach ($this->_headers as $name => $value)
            header("$name: $value");
    }

    private function _displayContent()
    {
        echo $this->_content;
    }

    public function setStatus($code)
    {
        http_response_code($code);
        return $this;
    }

    public function redirect($location = '/')
    {
        $this->_headers['Location'] = \url($location);
        $this->send();
    }

    public function sendJSON($array = [])
    {
        $this->setType('application/json');
        $this->_content = json_encode($array);
        return $this;
    }

    public function view($name, $vars = [])
    {
        $this->_content = new View($name, $vars);
        return $this;
    }

    public function getViewFromController($controller, $action)
    {
        $controller = explode('\\', $controller);
        $controller = $controller[count($controller) - 1];
        $controller = substr($controller, 0, -strlen('Controller'));
        return $controller . DS . strtolower($action);
    }

    /**
     * @return mixed
     */
    public function getContent()
    {
        return $this->_content;
    }

    /**
     * @param mixed $content
     */
    public function setContent($content)
    {
        $this->_content = $content;
    }

    /**
     * @return mixed
     */
    public function getType()
    {
        return $this->_type;
    }

    /**
     * @param mixed $type
     */
    public function setType($type)
    {
        $this->_type = $type;
    }

}