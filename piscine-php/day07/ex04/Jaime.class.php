<?php

class Jaime extends Lannister
{

    public function sleepWith($user)
    {
        if ($user instanceof Cersei)
            echo 'With pleasure, but only in a tower in Winterfell, then.' . PHP_EOL;
        else
            parent::sleepWith($user);
    }

}