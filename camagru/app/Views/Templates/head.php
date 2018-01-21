<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <title><?= $title ?> | InstaGru</title>
        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/bulma/0.6.2/css/bulma.min.css">
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css">
        <link rel="stylesheet" href="<?= $this->url('/assets/css/modals.css') ?>">
        <link rel="stylesheet" href="<?= $this->url('/assets/css/custom.css') ?>">
    </head>
    <body>
        <?= $this->template('navbar') ?>