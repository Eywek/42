<?php

namespace Controllers;

use Routing\Request;
use Routing\Response;

class IndexController extends Controller
{

    public function index(Request $req, Response $res)
    {
        debug($req, $req->custom);
        $this->set(['path' => 'path']);
    }

}