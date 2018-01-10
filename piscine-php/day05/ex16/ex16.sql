SELECT COUNT(`id_film`) AS `films`
FROM `historique_membre`
WHERE (`date` >= '2006-10-30' AND `date` <= '2007-07-27') OR DATE(`date`) LIKE '%-12-24';