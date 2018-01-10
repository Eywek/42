SELECT `nom`, `prenom`
FROM `fiche_personne`
WHERE `nom` LIKE '%-%' OR `prenom` LIKE '%-%'
ORDER BY `nom`, `prenom`;