SELECT MD5(REPLACE(CONCAT(`telephone`, '42'), '7', '9')) AS `ft5`
FROM `distrib`
WHERE `id_distrib` = 84;