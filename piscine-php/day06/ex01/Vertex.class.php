<?php

require_once 'Color.class.php';

class Vertex
{

    static public $verbose = false;

    private $_x;
    private $_y;
    private $_z;
    private $_w = 1.0;
    private $_color = false;

    public function __construct(array $data)
    {
        if (!isset($data['x']) || !isset($data['y']) || !isset($data['z']))
            return false;
        if (isset($data['color']) && !($data['color'] instanceof Color))
            return false;
        if (!isset($data['color']))
            $data['color'] = new Color(['red' => 255, 'green' => 255, 'blue' => 255]);
        foreach (['x', 'y', 'z', 'w', 'color'] as $var)
            if (isset($data[$var]))
                $this->{"_$var"} = $data[$var];
        if (self::$verbose)
            echo $this->__toString() . ' constructed' . PHP_EOL;
        return true;
    }

    public function __destruct()
    {
        if (self::$verbose)
            echo $this->__toString() . ' destructed' . PHP_EOL;
    }

    public function __toString()
    {
        return "Vertex( x: " . number_format($this->_x, 2, ".", "") .
                ", y: " . number_format($this->_y, 2, ".", "") .
                ", z:" . number_format($this->_z, 2, ".", "") .
                ", w:" . number_format($this->_w, 2, ".", "") .
                (self::$verbose ? ", $this->_color" : '') . " )";
    }

    static public function doc()
    {
        return file_get_contents('Vertex.doc.txt') . PHP_EOL;
    }

    public function getX()
    {
        return $this->_x;
    }

    public function setX($x)
    {
        $this->_x = $x;
    }

    public function getY()
    {
        return $this->_y;
    }

    public function setY($y)
    {
        $this->_y = $y;
    }

    public function getZ()
    {
        return $this->_z;
    }

    public function setZ($z)
    {
        $this->_z = $z;
    }

    public function getW()
    {
        return $this->_w;
    }

    public function setW($w)
    {
        $this->_w = $w;
    }

    public function getColor()
    {
        return $this->_color;
    }

    public function setColor(Color $color)
    {
        $this->_color = $color;
    }

    public function __get($name)
    {
        return false;
    }

    public function __set($name, $value)
    {
        return false;
    }

}