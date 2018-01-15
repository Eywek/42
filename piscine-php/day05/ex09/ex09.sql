SELECT COUNT(`id_film`) AS 'nb_court-metrage'
FROM `film`
WHERE `duree_min` <= 42;