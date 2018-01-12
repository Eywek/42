<?php

class UnholyFactory
{

    private $types = [];

    public function absorb($fighter)
    {
        if (!($fighter instanceof Fighter)) {
            echo "(Factory can't absorb this, it's not a fighter)" . PHP_EOL;
            return false;
        }
        if (isset($this->types[$fighter->getType()])) {
            echo "(Factory already absorbed a fighter of type {$fighter->getType()})" . PHP_EOL;
            return false;
        }
        echo "(Factory absorbed a fighter of type {$fighter->getType()})" . PHP_EOL;
        $this->types[$fighter->getType()] = $fighter;
        return true;
    }

    public function fabricate($type)
    {
        if (!isset($this->types[$type]))
        {
            echo "(Factory hasn't absorbed any fighter of type $type)" . PHP_EOL;
            return false;
        }
        echo "(Factory fabricates a fighter of type $type)" . PHP_EOL;
        return $this->types[$type];
    }

}