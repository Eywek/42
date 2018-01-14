<?php
require '../include/app.php';
redirectIfNotAdmin();

$users = queryDB('SELECT * FROM `users` ORDER BY `id` DESC;');

includeAdminHead();
?>

<div class="container">

    <h1>Liste des utilisateurs</h1>

    <table class="table">
        <thead>
        <tr>
            <th>Nom</th>
            <th>Email</th>
            <th>Administrateur</th>
            <th>Date d'inscription</th>
            <th>Actions</th>
        </tr>
        </thead>
        <tbody>
        <?php
        foreach ($users as $user) {
            echo '<tr>';
            echo '<td>' . strtoupper($user['name']) . ' ' . $user['first_name'] . '</td>';
            echo '<td>' . $user['email'] . '</td>';
            echo '<td>' . ($user['is_admin'] ? 'Oui' : 'Non') . '</td>';
            echo '<td>' . $user['created_at'] . '</td>';
            echo '<td>';
                echo '<a class="button button-info" href="edit_user.php?id=' . $user['id'] . '">Éditer</a>&nbsp;';
                echo '<a class="button button-danger" href="delete_user.php?id=' . $user['id'] . '">Supprimer</a>';
            echo '</td>';
            echo '</tr>';
        }
        ?>
        </tbody>
    </table>

</div>

<?php
includeAdminFooter();
?>

