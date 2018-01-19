<?php

namespace Models;

class Model
{

    protected $_fields = [];
    private $_validationError = NULL;

    static public function getTableName()
    {
        $model = get_called_class();
        $model = explode('\\', $model);
        $model = $model[count($model) - 1]; // remove namespace
        $model = substr($model, 0, strlen('Model') - 1); // remove model
        $model = lcfirst($model); // remove first upper

        $model = preg_replace_callback('/([a-z])([A-Z])/', function ($matches) {
            return $matches[1] . '_' . strtolower($matches[2]);
        }, $model); // camel case to snake case

        // to plural
        if (substr($model, -1) == 'y')
            $model = substr($model, 0, -1) . 'ies';
        else
            $model .= 's';

        return $model;
    }

    static public function create(array $fields)
    {
        $keys = array_keys($fields);
        $keysString = implode(', ', array_merge($keys, ['created_at']));
        $values = array_merge(array_values($fields), [date('Y-m-d H:i:s')]);
        $valuesString = implode(', ', array_map(function () {
            return '?';
        }, $values));

        $query = 'INSERT INTO ' . self::getTableName() . " ($keysString) VALUES($valuesString)";
        return Database::query($query, $values, false);
    }

    static private function _makeWhereQuery(array $data)
    {
        if (!isset($data['conditions']))
            return '';
        return ' WHERE ' . implode(', ', array_map(function ($field) {
            return "$field=?";
        }, array_keys($data['conditions'])));
    }

    static private function _makeJoinQuery(array $data)
    {
        // TODO
        return '';
    }

    static private function _makeGroupQuery(array $data)
    {
        if (!isset($data['group']))
            return '';
        return ' GROUP BY ' . implode(', ', array_values($data['group']));
    }

    static private function _makeOrderQuery(array $data)
    {
        if (!isset($data['order']))
            return '';
        $orders = [];
        foreach ($data['order'] as $field => $type)
            $orders[] = "$field $type";
        return ' ORDER BY ' . implode(', ', $orders);
    }

    static private function _makeLimitQuery(array $data)
    {
        if (!isset($data['limit']))
            return '';
        return ' LIMIT ' . $data['limit'];
    }

    static public function find(array $data = [])
    {
        $fields = '*';
        if (isset($data['fields']))
            $fields = implode(',', $data['fields']);
        $values = [];
        if (isset($data['conditions']))
            $values = array_values($data['conditions']);

        $query = "SELECT $fields FROM " . self::getTableName();
        $query .= self::_makeWhereQuery($data);
        $query .= self::_makeJoinQuery($data);
        $query .= self::_makeGroupQuery($data);
        $query .= self::_makeOrderQuery($data);
        $query .= self::_makeLimitQuery($data);
        return Database::query($query, $values, true, get_called_class());
    }

    static public function findFirst(array $data)
    {
        $data = array_merge($data, ['limit' => 1]);
        $result = self::find($data);
        if (!empty($result))
            return $result[0];
        return NULL;
    }

    static public function update(array $data, array $conditions)
    {
        $fields = implode(',', array_map(function ($key) {
            return "$key=?";
        }, array_keys($data)));
        $values = array_merge(array_values($data), array_values($conditions));

        $query = 'UPDATE ' . self::getTableName() . " SET $fields";
        $query .= self::_makeWhereQuery(['conditions' => $conditions]);
        return Database::query($query, $values, true, get_called_class());
    }

    public function save()
    {
        $vars = [];
        foreach ($this->_fields as $name => $type)
            $vars[$name] = $this->{$name};
        if (isset($this->id))
            return self::update($vars, ['id' => $this->id]);
        else
            return self::create($vars);
    }

    public function validate(array $data = [])
    {
        foreach ($this->_fields as $name => $types) {
            foreach (explode(':', $types) as $type) {
                list($type, $value) = explode('=', $type);

                switch ($type) {
                    case 'required':
                        if (!isset($data[$name]) || empty($data[$name]))
                            return $this->_setValidationError("Le champ $name ne peut pas être vide.");
                        break;
                    case 'unique':
                        if (!empty(self::find(['conditions' => [$name => $data[$name]]])))
                            return $this->_setValidationError("La valeur du champ $name est déjà utilisée.");
                        break;
                    case 'email':
                        if (!filter_var($data[$name], FILTER_VALIDATE_EMAIL))
                            return $this->_setValidationError("Le champ $name doit être un email valide.");
                        break;
                    case 'password':
                        if (strlen($data[$name]) <= '8')
                            return $this->_setValidationError("Le champ $name doit avoir un minimum de 8 caractères.");
                        else if (!preg_match("#[0-9]+#", $data[$name]))
                            return $this->_setValidationError("Le champ $name doit contenir au minimum un chiffre.");
                        else if (!preg_match("#[A-Z]+#", $data[$name]))
                            return $this->_setValidationError("Le champ $name doit contenir au minimum une lettre majuscule.");
                        else if (!preg_match("#[a-z]+#", $data[$name]))
                            return $this->_setValidationError("Le champ $name doit contenir au minimum une lettre minuscule.");
                        break;
                    case 'min':
                        if (strlen($data[$name]) < $value)
                            return $this->_setValidationError("Le champ $name doit avoir un minimum de $value caractères.");
                        break;
                    case 'max':
                        if (strlen($data[$name]) > $value)
                            return $this->_setValidationError("Le champ $name doit avoir un maximum de $value caractères.");
                        break;
                    case 'alpha_num':
                        if (!preg_match('/^[0-9a-zA-Z]+$/', $data[$name]))
                            return $this->_setValidationError("Le champ $name doit être uniquement alphanumérique.");
                        break;
                }
            }
        }
        return true;
    }

    private function _setValidationError($error)
    {
        $this->_validationError = $error;
        return false;
    }

    public function getValidationError()
    {
        return $this->_validationError;
    }

}