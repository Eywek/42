SELECT UPPER(`fiche_personne`.`nom`) AS `NOM`, `fiche_personne`.`prenom`, `abonnement`.`prix`
FROM `membre`
INNER JOIN `fiche_personne` ON `fiche_personne`.`id_perso` = `membre`.`id_fiche_perso`
INNER JOIN `abonnement` ON `abonnement`.`id_abo` = `membre`.`id_abo`
WHERE `abonnement`.`prix` > 42
ORDER BY `fiche_personne`.`nom`, `fiche_personne`.`prenom`