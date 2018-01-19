<?php

function hashPassword($password)
{
    return hash('sha512', $password);
}

function sanitize($data)
{
    return htmlentities($data);
}