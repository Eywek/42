INSERT INTO ft_table (`login`, `groupe`, `date_de_creation`)
  SELECT
    `nom` AS `login`,
    'other',
    IF(`id_perso` > 5, DATE_ADD(`date_naissance`, INTERVAL 20 YEAR), `date_naissance`) AS `date_de_creation`
  FROM `fiche_personne`
  WHERE CHAR_LENGTH(`nom`) < 9 AND `nom` LIKE '%a%'
  ORDER BY `nom`
  LIMIT 10
;
