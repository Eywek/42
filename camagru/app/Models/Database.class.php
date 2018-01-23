<?php

namespace Models;

use PDO;

class Database
{

    static private $_connection = NULL;
    static private $_credentials = [
      'dsn' => NULL,
      'user' => NULL,
      'password' => NULL
    ];

    static private function _initCredentials()
    {
        if (self::$_credentials['dsn'])
            return;
        require CONFIG_PATH . 'database.php';
        self::$_credentials['dsn'] = $DB_DSN;
        self::$_credentials['user'] = $DB_USER;
        self::$_credentials['password'] = $DB_PASSWORD;
    }

    static public function getPDO()
    {
        return self::_getDatabase();
    }

    static private function _getDatabase()
    {
        if (self::$_connection)
            return self::$_connection;

        self::_initCredentials();
        try {
            self::$_connection = new PDO(self::$_credentials['dsn'], self::$_credentials['user'], self::$_credentials['password']);
            self::$_connection->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        } catch (\Exception $e) {
            die('Impossible de se connecter à la base de données');
        }

        return self::$_connection;
    }

   static public function query($query, $params, $fetch = true, $model = NULL)
   {
        try {
            $req = self::_getDatabase()->prepare($query);
            $req->execute($params);

            if (!$fetch)
                return $req->rowCount();
            if (!$model)
                return $req->fetchAll();
            else
                return $req->fetchAll(PDO::FETCH_CLASS, $model);
        } catch (\Exception $e) {
            return $e;
        }
   }

   static public function getLastInsertId()
   {
       return self::_getDatabase()->lastInsertId();
   }

}