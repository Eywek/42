<?php

require_once 'Vertex.class.php';

class Vector
{

    static public $verbose = false;

    private $_x;
    private $_y;
    private $_z;
    private $_w = 0.0;

    public function __construct(array $data)
    {
        if (!isset($data['dest']) || !($data['dest'] instanceof Vertex))
            return false;
        if (isset($data['orig']) && !($data['orig'] instanceof Vertex))
            return false;
        else if (!isset($data['orig']))
            $data['orig'] = new Vertex(['x' => 0, 'y' => 0, 'z' => 0, 'w' => 1]);
        $this->_x = $data['dest']->getX() - $data['orig']->getX();
        $this->_y = $data['dest']->getY() - $data['orig']->getY();
        $this->_z = $data['dest']->getZ() - $data['orig']->getZ();
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
        return 'Vector( x:' . number_format($this->_x, 2, ".", "") .
                ', y:' . number_format($this->_y, 2, ".", "") .
                ', z:' . number_format($this->_z, 2, ".", "") .
                ', w:' . number_format($this->_w, 2, ".", "") . ' )';
    }

    public function magnitude()
    {
        return sqrt($this->_x * $this->_x + $this->_y * $this->_y + $this->_z * $this->_z);
    }

    public function normalize()
    {
        return $this->div($this->magnitude());
    }

    public function add(Vector $rhs)
    {
        $x = $this->_x + $rhs->getX();
        $y = $this->_y + $rhs->getY();
        $z = $this->_z + $rhs->getZ();
        return new Vector(['dest' => new Vertex(compact('x', 'y', 'z'))]);
    }

    public function sub(Vector $rhs)
    {
        $x = $this->_x - $rhs->getX();
        $y = $this->_y - $rhs->getY();
        $z = $this->_z - $rhs->getZ();
        return new Vector(['dest' => new Vertex(compact('x', 'y', 'z'))]);
    }

    private function div($nb)
    {
        $nb = ($nb > 0 ? $nb : 1);
        $x = $this->_x / $nb;
        $y = $this->_y / $nb;
        $z = $this->_z / $nb;
        return new Vector(['dest' => new Vertex(compact('x', 'y', 'z'))]);
    }

    public function opposite()
    {
        $x = -1 * $this->_x;
        $y = -1 * $this->_y;
        $z = -1 * $this->_z;
        return new Vector(['dest' => new Vertex(compact('x', 'y', 'z'))]);
    }

    public function scalarProduct($k)
    {
        $x = $this->_x * $k;
        $y = $this->_y * $k;
        $z = $this->_z * $k;
        return new Vector(['dest' => new Vertex(compact('x', 'y', 'z'))]);
    }

    public function dotProduct(Vector $rhs)
    {
        return ($this->_x * $rhs->getX() + $this->_y * $rhs->getY() + $this->_z * $rhs->getZ());
    }

    public function cos(Vector $rhs)
    {
        return $this->dotProduct($rhs) / ($this->magnitude() * $rhs->magnitude());
    }

    public function crossProduct(Vector $rhs)
    {
        $x = $this->_y * $rhs->getZ() - $rhs->getY() * $this->_z;
        $y = $this->_z * $rhs->getX() - $this->_x * $rhs->getZ();
        $z = $this->_x * $rhs->getY() - $this->_y * $rhs->getX();
        return new Vector(['dest' => new Vertex(compact('x', 'y', 'z'))]);
    }

    static public function doc()
    {
        return file_get_contents('Vector.doc.txt') . PHP_EOL;
    }

    /**
     * @return float
     */
    public function getX()
    {
        return $this->_x;
    }

    /**
     * @return float
     */
    public function getY()
    {
        return $this->_y;
    }

    /**
     * @return float
     */
    public function getZ()
    {
        return $this->_z;
    }

    /**
     * @return float
     */
    public function getW()
    {
        return $this->_w;
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