<?php

namespace Models;

class Model
{

    protected $_fields = [];
    static protected $_from = [];
    static protected $_fromDefault = false;
    private $_validationError = NULL;

    static public function getTableNameFrom($model, $plural = true)
    {
        $model = explode('\\', $model);
        $model = $model[count($model) - 1]; // remove namespace
        $model = substr($model, 0, -strlen('Model')); // remove model
        $model = lcfirst($model); // remove first upper

        $model = preg_replace_callback('/([a-z])([A-Z])/', function ($matches) {
            return $matches[1] . '_' . strtolower($matches[2]);
        }, $model); // camel case to snake case

        // to plural
        if ($plural)
            $model = \toPlural($model);

        return $model;
    }

    static public function getTableName($plural = true)
    {
        return self::getTableNameFrom(get_called_class(), $plural);
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
        return ' WHERE ' . implode(' AND ', array_map(function ($field) use ($data) {
            if ($data['conditions'][$field] !== NULL)
                return "$field=?";
            else
                return "$field IS NULL";
        }, array_keys($data['conditions'])));
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

    static private function _generateModelJoinName($model, $prefix = false)
    {
        if ($prefix === false)
            $prefix = \toPlural(get_called_class());
        $name = substr($model, strlen($prefix) - strlen('Model'), -strlen('Model'));
        $name = strtolower(\toPlural($name));
        return $name;
    }

    static private function _getJoinData($results, array $data)
    {
        if (!isset($data['join']))
            $data['join'] = [];
        if (!isset($data['from']))
            if (get_called_class()::$_fromDefault)
                $data['from'] = array_keys(get_called_class()::$_from);
            else
                $data['from'] = [];
        foreach ($results as $key => $result) {
            foreach ($data['join'] as $model) {
                $modelJoinName = self::_generateModelJoinName($model);
                $results[$key]->$modelJoinName = $model::find(['conditions' => [self::getTableName(false) . '_id' => $result->id]]);
            }
            foreach ($data['from'] as $model) {
                $modelJoinName = self::_generateModelJoinName($model, 'ModelModels\\');
                $params = ['conditions' => ['id' => $result->{self::getTableNameFrom($model,false) . "_id"}]];
                if (isset(get_called_class()::$_from[$model]))
                    $params['fields'] = get_called_class()::$_from[$model];
                $results[$key]->$modelJoinName = $model::find($params);
            }
        }
        return $results;
    }

    static public function find(array $data = [])
    {
        $fields = '*';
        if (isset($data['fields']))
            $fields = implode(',', $data['fields']);
        $values = [];
        if (isset($data['conditions']))
            $values = array_values(array_filter($data['conditions'], function ($value) {
                return ($value !== NULL);
            }));

        $query = "SELECT $fields FROM " . self::getTableName();
        $query .= self::_makeWhereQuery($data);
        $query .= self::_makeGroupQuery($data);
        $query .= self::_makeOrderQuery($data);
        $query .= self::_makeLimitQuery($data);
        if (!isset($data['join']) && !get_called_class()::$_fromDefault && !isset($data['from']))
            return Database::query($query, $values, true, get_called_class());
        else
            return self::_getJoinData(Database::query($query, $values, true, get_called_class()), $data);
    }

    static public function findFirst(array $data)
    {
        $data = array_merge($data, ['limit' => 1]);
        $result = self::find($data);
        if (!empty($result) && !($result instanceof \Exception))
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
        return Database::query($query, $values, false);
    }

    static public function delete(array $data)
    {
        $values = [];
        if (!empty($data))
            $data['conditions'] = $data;
        if (isset($data['conditions']))
            $values = array_values($data['conditions']);

        $query = "DELETE FROM " . self::getTableName();
        $query .= self::_makeWhereQuery($data);
        return Database::query($query, $values, false);
    }

    public function save()
    {
        $vars = [];
        foreach ($this->_fields as $name => $type)
            if (isset($this->{$name}))
                $vars[$name] = $this->{$name};
        if (isset($this->id)) {
            self::update($vars, ['id' => $this->id]);
            return $this;
        } else {
            self::create($vars);
            $this->id = Database::getLastInsertId();
            return $this;
        }
    }

    public function validate(array $data = [], array $requireds = NULL, $uniqueBypassIds = [])
    {
        foreach ($this->_fields as $name => $types) {
            if ($requireds !== NULL && !in_array($name, $requireds))
                continue;
            foreach (explode(':', $types) as $type) {
                if (strpos($type, '='))
                    list($type, $value) = explode('=', $type);

                switch ($type) {
                    case 'required':
                        if ((!isset($data[$name]) || empty($data[$name])))
                            return $this->_setValidationError("Le champ $name ne peut pas être vide.");
                        break;
                    case 'unique':
                        if (!empty(Database::query('SELECT `id` FROM `' . self::getTableName() . "` WHERE `$name` = ? ". ($uniqueBypassIds ? "AND `id` NOT IN (" . implode(', ', $uniqueBypassIds) .")" : ''), [$data[$name]])))
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
                    case 'model':
                        $model = "{$value}Model";
                        if (!($model::findFirst(['conditions' => ['id' => $data[$name]]])))
                            return $this->_setValidationError("Le champ $name doit correspondre à une entrée dans $value.");
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