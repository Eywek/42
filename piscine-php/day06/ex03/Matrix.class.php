<?php

require_once 'Vector.class.php';

class Matrix
{

    const IDENTITY = 'IDENTITY';
    const SCALE = 'SCALE';
    const RX = 'Ox ROTATION';
    const RY = 'Oy ROTATION';
    const RZ = 'Oz ROTATION';
    const TRANSLATION = 'TRANSLATION';
    const PROJECTION = 'PROJECTION';

    private $_coords = ['x', 'y', 'z', 'w'];
    private $_matrix = [
        [0.00, 0.00, 0.00, 0.00],
        [0.00, 0.00, 0.00, 0.00],
        [0.00, 0.00, 0.00, 0.00],
        [0.00, 0.00, 0.00, 0.00],
    ];
    private $_data = [];

    static public $verbose = false;

    /*
     * Global functions
     */

    public function __construct(array $data, $new = true)
    {
        // Validation
        if (!isset($data['preset']) || !in_array($data['preset'], [
            self::IDENTITY, self::SCALE, self::RX, self::RY, self::RZ, self::TRANSLATION, self::PROJECTION
        ]))
            return false;
        if (!isset($data['scale']) && $data['preset'] === self::SCALE)
            return false;
        if (!isset($data['angle']) && in_array($data['preset'], [self::RY, self::RX, self::RZ]))
            return false;
        if ((!isset($data['vtc']) || !($data['vtc'] instanceof Vector)) && $data['preset'] === self::TRANSLATION)
            return false;
        if ((!isset($data['fov']) || !isset($data['ratio']) || !isset($data['near']) || !isset($data['far'])) && $data['preset'] === self::PROJECTION)
            return false;
        // Verbose
        if (self::$verbose && $new)
            echo "Matrix {$data['preset']} " . ($data['preset'] !== self::IDENTITY ? 'preset ' : '') . "instance constructed" . PHP_EOL;
        // Process
        $functionName = '_generate' . str_replace(' ', '', ucwords(strtolower($data['preset']))) . 'Preset';
        $this->{$functionName}($data);
        $this->_data = $data;
        return true;
    }

    public function __destruct()
    {
        if (self::$verbose)
            echo 'Matrix instance destructed' . PHP_EOL;
    }

    public function __toString()
    {
        $string = 'M | vtcX | vtcY | vtcZ | vtxO' . PHP_EOL;
        $string .= '-----------------------------';
        for ($i = 0; $i < count($this->_matrix); $i++)
        {
            $string .= PHP_EOL . "{$this->_coords[$i]}";
            for ($j = 0; $j < count($this->_matrix[$i]); $j++)
                $string .= ' | ' . number_format($this->_matrix[$i][$j], 2, '.', '');
        }
        return $string;
    }

    public function __get($name)
    {
        return false;
    }

    public function __set($name, $value)
    {
        return false;
    }

    static public function doc()
    {
        return file_get_contents('Matrix.doc.txt') . PHP_EOL;
    }

    /*
     * General functions
     */

    public function mult(Matrix $rhs)
    {
        // Calcul
        $coords = [];
        for ($i = 0; $i < count($this->_matrix); $i++)
        {
            $coords[$i] = [];
            for ($j = 0; $j < count($this->_matrix[$i]); $j++)
            {
                $sum = 0;
                for ($k = 0; $k < count($rhs->get()); $k++) {
                    $sum += $this->_matrix[$i][$k] * $rhs->get()[$k][$j];
                }
                $coords[$i][$j] = $sum;
            }
        }
        // Instance
        $matrix = new Matrix($this->_data, false);
        $matrix->set($coords);
        return $matrix;
    }

    public function transformVertex(Vertex $vtx)
    {
        $matrix = $this->get();
        $x = ($vtx->getX() * $matrix[0][0]) + ($vtx->getY() * $matrix[0][1]) + ($vtx->getZ() * $matrix[2][2]) + ($vtx->getW() * $matrix[0][3]);
        $y = ($vtx->getX() * $matrix[1][0]) + ($vtx->getY() * $matrix[1][1]) + ($vtx->getZ() * $matrix[1][2]) + ($vtx->getW() * $matrix[1][3]);
        $z = ($vtx->getX() * $matrix[2][0]) + ($vtx->getY() * $matrix[2][1]) + ($vtx->getZ() * $matrix[2][2]) + ($vtx->getW() * $matrix[2][3]);
        $w = ($vtx->getX() * $matrix[2][3]) + ($vtx->getY() * $matrix[3][0]) + ($vtx->getZ() * $matrix[3][2]) + ($vtx->getW() * $matrix[3][3]);
        $color = $vtx->getColor();
        $vertex = new Vertex(compact('x', 'y', 'z', 'w', 'color'));
        return $vertex;
    }

    /*
     * Generate functions
     */

    private function _generateIdentityPreset(array $data)
    {
        $this->set([
            [1.00, 0.00, 0.00, 0.00],
            [0.00, 1.00, 0.00, 0.00],
            [0.00, 0.00, 1.00, 0.00],
            [0.00, 0.00, 0.00, 1.00],
        ]);
    }

    private function _generateScalePreset(array $data)
    {
        $this->set([
            [$data['scale'], 0.00, 0.00, 0.00],
            [0.00, $data['scale'], 0.00, 0.00],
            [0.00, 0.00, $data['scale'], 0.00],
            [0.00, 0.00, 0.00, 1.00],
        ]);
    }

    private function _generateOxRotationPreset(array $data)
    {
        $this->_generateIdentityPreset($data);
        $matrix = $this->get();
        $matrix[0][0] = 1;
        $matrix[1][1] = cos($data['angle']);
        $matrix[1][2] = -sin($data['angle']);
        $matrix[2][1] = sin($data['angle']);
        $matrix[2][2] = cos($data['angle']);
        $this->set($matrix);
    }

    private function _generateOyRotationPreset(array $data)
    {
        $this->_generateIdentityPreset($data);
        $matrix = $this->get();
        $matrix[0][0] = cos($data['angle']);
        $matrix[0][2] = sin($data['angle']);
        $matrix[1][1] = 1;
        $matrix[2][0] = -sin($data['angle']);
        $matrix[2][2] = cos($data['angle']);
        $this->set($matrix);
    }

    private function _generateOzRotationPreset(array $data)
    {
        $this->_generateIdentityPreset($data);
        $matrix = $this->get();
        $matrix[0][0] = cos($data['angle']);
        $matrix[0][1] = -sin($data['angle']);
        $matrix[1][0] = sin($data['angle']);
        $matrix[1][1] = cos($data['angle']);
        $matrix[2][2] = 1;
        $this->set($matrix);
    }

    private function _generateTranslationPreset(array $data)
    {
        $this->_generateIdentityPreset($data);
        $matrix = $this->get();
        $matrix[0][3] = $data['vtc']->getX();
        $matrix[1][3] = $data['vtc']->getY();
        $matrix[2][3] = $data['vtc']->getZ();
        $this->set($matrix);
    }

    private function _generateProjectionPreset(array $data)
    {
        $this->_generateIdentityPreset($data);
        $matrix = $this->get();
        $matrix[1][1] = 1 / tan(0.5 * deg2rad($data['fov']));
        $matrix[0][0] = $matrix[1][1] / $data['ratio'];
        $matrix[2][2] = -1 * (-$data['near'] - $data['far']) / ($data['near'] - $data['far']);
        $matrix[2][3] = (2 * $data['near'] * $data['far']) / ($data['near'] - $data['far']);
        $matrix[3][2] = -1;
        $matrix[3][3] = 0;
        $this->set($matrix);
    }

    /**
     * @param array $matrix
     */
    public function set($matrix)
    {
        $this->_matrix = $matrix;
    }

    /**
     * @return array
     */
    public function get()
    {
        return $this->_matrix;
    }

}
