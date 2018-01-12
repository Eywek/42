<?php

class NightsWatch
{

    private $recruits = [];

    public function recruit($recruit)
    {
        array_push($this->recruits, $recruit);
    }
    
    public function fight()
    {
        foreach ($this->recruits as $recruit) {
            if ($recruit instanceof IFighter)
                $recruit->fight();
        }
    }

}