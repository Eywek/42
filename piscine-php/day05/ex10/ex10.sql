SELECT `film`.`titre` AS `Titre`, `film`.`resum` AS `Resume`, `film`.`annee_prod`
FROM `film`
INNER JOIN `genre` ON `genre`.`nom` = 'erotic'
WHERE `film`.`id_genre` = `genre`.`id_genre`
ORDER BY `annee_prod` DESC;