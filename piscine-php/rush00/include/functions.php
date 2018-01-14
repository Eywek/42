<?php
/*
 * Validation
 */

function validate(array $rulesByInput = [], array $data = [])
{
    // Each of rules
    foreach ($rulesByInput as $input => $values) {
        $name = $values['name']; // Get name for user
        $rules = $values['rules']; // List rules
        // Each of rules by input
        foreach ($rules as $rule => $value) {
            // If the rule as no value
            if (is_int($rule))
                $rule = $value;
            // Each type of rules available
            switch ($rule) {
                case 'not_empty':
                    if (!isset($data[$input]) || empty($data[$input]))
                        return "Le champ $name ne peut pas être vide !";
                    break;
                case 'min_length':
                    if (strlen($data[$input]) < $value)
                        return "Le champ $name doit avoir au minimum $value caractères !";
                    break;
                case 'max_length':
                    if (strlen($data[$input]) > $value)
                        return "Le champ $name doit avoir au maximum $value caractères !";
                    break;
                case 'email':
                    $email = htmlentities($data[$input]);
                    if (!filter_var($email, FILTER_VALIDATE_EMAIL))
                        return "Le champ $name doit être un email valide !";
                    break;
                case 'is_numeric':
                    if (!is_numeric($data[$input]))
                        return "Le champ $name doit être un nombre valide !";
                    break;
                case 'in':
                    foreach ($data[$input] as $datum)
                        if (!in_array($datum, $value))
                            return "Le champ $name doit être une catégorie valide !";
                    break;
                case 'url':
                    $url = htmlentities($data[$input]);
                    if (!filter_var($url, FILTER_VALIDATE_URL))
                        return "Le champ $name doit être une URL valide !";
                    break;
            }
        }
    }
    return true;
}

/*
 * Security
 */

function hashPassword($password)
{
    return hash('sha512', $password);
}

function sanitize($data = [])
{
    if (!is_array($data))
        return htmlentities($data);
    foreach ($data as $key => $value)
        $data[$key] = htmlentities($value);
    return $data;
}

/*
 * DEBUG
 */

function debug()
{
    echo '<pre>';
    call_user_func_array('var_dump', func_get_args());
    echo '</pre>';
}