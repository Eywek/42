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
        403 => NULL,
        400 => NULL
    ];
    private $_exceptions = [
        NotFoundException::class => 404,
        InternalErrorException::class => 500,
        ForbiddenException::class => 403,
        BadRequestException::class => 400
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
            return $this->_dispatchError(404);
        return $this->_callRoute($route);
    }

    private function _findRoute(Request $req)
    {
        if (isset($this->_routes[$req->getMethod()][$req->getPath()]))
            return $this->_routes[$req->getMethod()][$req->getPath()];

        // Generate routes
        $routes = [];
        foreach ($this->_routes[$req->getMethod()] as $route => $action) {
            preg_match_all('/[^{}]*({([A-Za-z]+):([^}]+)})[^{}]*/', $route, $matches);
            $result = [
                'args_name' => [],
                'route' => (empty($matches[0]) ? $route : ''),
                'action' => $action
            ];
            $count = count($matches[1]);
            for ($i = 0; $i < $count; $i++) {
                $result['route'] .= str_replace($matches[1][$i], '(' . $matches[3][$i] . ')', $matches[0][$i]);
                $result['args_name'][] = $matches[2][$i];
            }
            $routes[] = $result;
        }

        // Try to match one
        foreach ($routes as $route) {
            $match = '/^' . str_replace('/', '\\/', $route['route']) . '$/';
            if (preg_match($match, $req->getPath(), $matches)) {
                $matches = array_splice($matches, 1, count($route['args_name']));
                $args = array_combine($route['args_name'], $matches);
                $this->_req->setArgs($args);
                return $route['action'];
            }
        }

        return false;
    }

    private function _callRoute($route)
    {
        // Call controller
        $controller = new $route[0]();
        try {
            $res = $controller->{$route[1]}($this->_req, $this->_res);
        } catch (\Exception $e) {
            $this->_handleExceptions($e);
            return true;
        }
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

    private function _handleExceptions(\Exception $e)
    {
        if (isset($this->_exceptions[get_class($e)]))
            return $this->_dispatchError($this->_exceptions[get_class($e)]);
        return $this->_dispatchError(500);
    }

    private function _dispatchError($errorCode)
    {
        return $this->_errorsHandlers[$errorCode]($this->_req);
    }

}