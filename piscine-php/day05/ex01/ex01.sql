CREATE TABLE ft_table
(
  id INT AUTO_INCREMENT,
  login VARCHAR(8) DEFAULT 'toto',
  groupe ENUM('staff', 'student', 'other'),
  date_de_creation DATE
);