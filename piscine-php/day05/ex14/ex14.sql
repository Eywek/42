SELECT `etage_salle` AS `etage`, COUNT(`nbr_siege`) AS `sieges`
FROM `salle`
GROUP BY `etage_salle`
ORDER BY COUNT(`nbr_siege`) DESC;