<?php
include 'include/app.php';
redirectIfNotLogged();
logout();
deleteUser($_SESSION['user']);

$title = "delete_account";
includeHead();
?>
<meta http-equiv="refresh" content="3; url=index.php">
		<div class="hr"></div>
		<div id="milieu">
			Compte supprimé<br />
		</div>
		<div class="hr"></div>
<?php
includeFooter();
?>