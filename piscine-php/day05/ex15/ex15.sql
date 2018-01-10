SELECT REVERSE(SUBSTRING(`telephone`, 2)) AS `enohpelet`
FROM `distrib`
WHERE `telephone` LIKE '05%';