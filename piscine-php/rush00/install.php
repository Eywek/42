<?php
    require 'include/app.php';

    if (file_exists('installed') && strpos(file_get_contents('installed'), '1') !== false) {
        header('Location: index.php');
        exit();
    }
    if (!file_exists('installed'))
    {
        // Install database
        initDB();
        if (!mysqli_multi_query($db, file_get_contents(INCLUDE_DIR . 'rush00.sql')))
            exit("Impossible d'installer la base de donneés, avez-vous bien configuré le fichier config/app.php ? (CODE: " . mysqli_errno($db) . ")");
        file_put_contents('installed', '0');
    }
    if ($_POST) {
        $signup = signup($_POST, true);
        if (is_int($signup))
        {
            // Login
            login($signup);
            // Redirect
            file_put_contents('installed', '1');
            header('Location: index.php');
        } else
            $error = $signup;
    }
?>
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>Installation</title>
    <style>
        body {
            text-align: center;
            font-family: Arial, sans-serif;
        }

        div.input-group {
            display: block;
            margin: 5px;
        }

        input {
            display: inline-block;
            width: 20%;
            height: 20px;
            padding: 6px 12px;
            font-size: 14px;
            line-height: 1.42857143;
            color: #555;
            background-color: #fff;
            border: 1px solid #ccc;
            border-radius: 4px;
        }
        input:focus {
            outline: 0;
        }
        label {
            font-weight: bold;
            margin-top: 10px;
            display: block;
        }

        button {
            display: inline-block;
            padding: 6px 12px;
            margin-bottom: 0;
            font-size: 14px;
            font-weight: 400;
            line-height: 1.42857143;
            text-align: center;
            white-space: nowrap;
            vertical-align: middle;
            -ms-touch-action: manipulation;
            touch-action: manipulation;
            cursor: pointer;
            -webkit-user-select: none;
            -moz-user-select: none;
            -ms-user-select: none;
            user-select: none;
            background-image: none;
            border-radius: 4px;
            color: #333;
            background-color: #fff;
            border: 1px solid #ccc;
        }

        button:focus {
            outline: 0;
        }

        div.alert {
            padding: 10px;
            -webkit-border-radius: 5px;
            -moz-border-radius: 5px;
            border-radius: 5px;
            width: 20%;
            margin-left: auto;
            margin-right: auto;
        }

        div.alert.alert-error {
            background-color: #e74c3c;
            color: #5c060b;
            border: solid #c0392b 1px;
        }
    </style>
</head>
<body>
<h1>Création du compte administrateur</h1>

<?php
if (isset($error))
    echo "<div class='alert alert-error'><b>Erreur :</b> $error</div>";
?>
<form action="" method="post">

    <div class="input-group">
        <label for="first_name">Prénom :</label>
        <input type="text" name="first_name" value="" />
    </div>

    <div class="input-group">
        <label for="name">Nom :</label>
        <input type="text" name="name" value="" />
    </div>

    <div class="input-group">
        <label for="email">Email :</label>
        <input type="email" name="email" value="" />
    </div>

    <div class="input-group">
        <label for="password">Mot de passe :</label>
        <input type="password" name="password" value="" />
    </div>

    <div class="input-group">
        <label for="password_confirmation">Mot de passe :</label>
        <input type="password" name="password_confirmation" value="" />
    </div>

    <button type="submit">Créer</button>
</form>
</body>
</html>