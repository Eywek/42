<?php

class Lannister
{

    public function sleepWith($user)
    {
        if (get_parent_class($user) === Lannister::class)
            echo 'Not even if I\'m drunk !' . PHP_EOL;
        else
            echo 'Let\'s do this.' . PHP_EOL;
    }

}