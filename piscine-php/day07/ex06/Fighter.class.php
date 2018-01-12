<?php

class Fighter
{

    private $type = NULL;

    public function __construct($type)
    {
        $this->type = $type;
    }

    public function getType()
    {
        return $this->type;
    }

}