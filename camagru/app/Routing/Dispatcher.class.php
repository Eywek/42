<?php

namespace Routing;

class Dispatcher
{

    private $_req;
    private $_res;

    private $_routes = [
        'GET' => [],
        'POST' => [],
        'PUT' => [],
        'DELETE' => [],
        'HEAD' => []
    ];
    private $_errorsHandlers = [
        404 => NULL,
        500 => NULL,
        403 => NULL
    ];

    public function __construct(Request $req, Response $res)
    {
        $this->_req = $req;
        $this->_res = $res;
    }

    public function addRoute($method = 'GET', $path = '/', $class, $action = 'index')
    {
        $this->_routes[$method][$path] = [$class, $action];
    }

    public function addErrorHandler($errorCode, $callable)
    {
        $this->_errorsHandlers[$errorCode] = $callable;
    }

    public function dispatch()
    {
        $route = $this->_findRoute($this->_req);
        if (!$route)
            return $this->_errorsHandlers[404]($this->_req);
        return $this->_callRoute($route);
    }

    private function _findRoute(Request $req)
    {
        // TODO: Args
        if (isset($this->_routes[$req->getMethod()][$req->getPath()]))
            return $this->_routes[$req->getMethod()][$req->getPath()];
        return false;
    }

    private function _callRoute($route)
    {
        // Call controller
        $controller = new $route[0]();
        $res = $controller->{$route[1]}($this->_req, $this->_res);
        // Display
        if (empty($res)) {
            $res = new Response();
            $res->view($res->getViewFromController($route[0], $route[1]), $controller->getVars())->send();
        }
        else if ($res instanceof Response)
            $res->send();
        else
            (new Response($res))->send();
        return true;
    }

}