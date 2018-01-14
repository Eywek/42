--
-- Structure de la table `categories`
--

CREATE TABLE `categories` (
  `id` int(11) NOT NULL,
  `name` varchar(50) CHARACTER SET latin1 NOT NULL,
  `created_at` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `items`
--

CREATE TABLE `items` (
  `id` int(11) NOT NULL,
  `name` varchar(150) NOT NULL,
  `price` float NOT NULL,
  `description` text NOT NULL,
  `image_url` varchar(255) NOT NULL,
  `created_at` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Structure de la table `items_categories`
--

CREATE TABLE `items_categories` (
  `id` int(11) NOT NULL,
  `item_id` int(11) NOT NULL,
  `category_id` int(11) NOT NULL,
  `created_at` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Structure de la table `orders`
--

CREATE TABLE `orders` (
  `id` int(11) NOT NULL,
  `item_id` int(11) NOT NULL,
  `quantity` int(11) NOT NULL DEFAULT '1',
  `user_id` int(11) NOT NULL,
  `address` text NOT NULL,
  `created_at` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Structure de la table `users`
--

CREATE TABLE `users` (
  `id` int(11) NOT NULL,
  `first_name` varchar(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `email` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `is_admin` tinyint(1) NOT NULL DEFAULT '0',
  `created_at` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Index pour les tables exportées
--

--
-- Index pour la table `categories`
--
ALTER TABLE `categories`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `items`
--
ALTER TABLE `items`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `items_categories`
--
ALTER TABLE `items_categories`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `orders`
--
ALTER TABLE `orders`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT pour les tables exportées
--

--
-- AUTO_INCREMENT pour la table `categories`
--
ALTER TABLE `categories`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT pour la table `items`
--
ALTER TABLE `items`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT pour la table `items_categories`
--
ALTER TABLE `items_categories`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT pour la table `orders`
--
ALTER TABLE `orders`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT pour la table `users`
--
ALTER TABLE `users`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1;


INSERT INTO `categories` (`id`, `name`, `created_at`) VALUES
  (NULL, 'League Of Legends', '2018-01-14 17:07:35'),
  (NULL, 'Overwatch', '2018-01-14 17:12:01'),
  (NULL, 'HearthStone', '2018-01-14 17:12:15'),
  (NULL, 'Cs:Go', '2018-01-14 17:20:02');

--
-- Contenu de la table `items`
--

INSERT INTO `items` (`id`, `name`, `price`, `description`, `image_url`, `created_at`) VALUES
  (NULL, 'Peluche Blitzcrank', 20, 'Peluche trop douce blitz', 'http://img11.hostingpics.net/pics/305293IMG0010.jpg', '2018-01-14 17:08:34'),
  (NULL, 'Peluche Gnar', 22, 'Gnar Gnar Gnar Gnar Gnar', 'https://euw.merch.riotgames.com/media/catalog/product/cache/61/image/570x/9df78eab33525d08d6e5fb8d27136e95/i/m/image_49.png', '2018-01-14 17:11:50'),
  (NULL, 'Choppe &agrave; bi&egrave;re', 8, 'Choppe &agrave; bi&egrave;re HearthStone une fois !', 'https://img0.etsystatic.com/199/0/14294785/il_fullxfull.1320621716_qi68.jpg', '2018-01-14 17:13:36'),
  (NULL, 'Tapis de souris Windowsmaker', 12, 'Tapis de souris Windowsmaker', 'https://i2.cdscdn.com/pdt2/7/8/5/1/700x700/auc0669321478785/rw/overwatch-tracer-vs-widowmaker-tapis-de-souris-sur.jpg', '2018-01-14 17:14:50'),
  (NULL, 'Sac &agrave; dos Cs:Go', 16, 'Sac &agrave; dos Cs:Go trololol', 'https://geekmaroc.com/wp-content/uploads/2017/08/csgo-2.png', '2018-01-14 17:18:00');

--
-- Contenu de la table `items_categories`
--

INSERT INTO `items_categories` (`id`, `item_id`, `category_id`, `created_at`) VALUES
  (NULL, 1, 1, '2018-01-30 11:32:49'),
  (NULL, 3, 3, '2018-01-14 16:28:15'),
  (NULL, 2, 1, '2018-01-14 16:28:21'),
  (NULL, 2, 3, '2018-01-14 16:28:21'),
  (NULL, 4, 5, '2018-01-14 17:08:34'),
  (NULL, 5, 5, '2018-01-14 17:11:50'),
  (NULL, 7, 6, '2018-01-14 17:14:50'),
  (NULL, 6, 7, '2018-01-14 17:15:20'),
  (NULL, 8, 8, '2018-01-14 17:18:00');