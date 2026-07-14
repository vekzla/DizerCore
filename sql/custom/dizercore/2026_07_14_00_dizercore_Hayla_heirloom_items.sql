-- 1. Create the database schema if it doesn't exist (Optional safety)
CREATE SCHEMA IF NOT EXISTS `dizercore`;

-- 2. Create the table
CREATE TABLE IF NOT EXISTS `dizercore`.`hayla_heirloom_items` (
  `id` INT(11) NOT NULL AUTO_INCREMENT,
  `category` VARCHAR(50) NOT NULL,
  `item_id` INT(11) NOT NULL,
  `sort_order` INT(11) DEFAULT 0,
  PRIMARY KEY (`id`)
);

-- 3. Clear existing data to prevent duplicates if you run this multiple times
TRUNCATE TABLE `dizercore`.`hayla_heirloom_items`;

-- 4. Insert the data
INSERT INTO `dizercore`.`hayla_heirloom_items` (`category`, `item_id`, `sort_order`) VALUES
('Head', 122263, 1), ('Head', 122245, 2), ('Head', 127012, 3), ('Head', 122247, 4), ('Head', 122246, 5), ('Head', 122249, 6), ('Head', 122248, 7), ('Head', 122250, 8),
('Shoulders', 122388, 1), ('Shoulders', 122355, 2), ('Shoulders', 122373, 3), ('Shoulders', 122372, 4), ('Shoulders', 122375, 5), ('Shoulders', 122356, 6), ('Shoulders', 122357, 7), ('Shoulders', 122374, 8), ('Shoulders', 122376, 9), ('Shoulders', 122377, 10), ('Shoulders', 122359, 11), ('Shoulders', 122358, 12), ('Shoulders', 122378, 13), ('Shoulders', 122360, 14),
('Cloaks', 122262, 1), ('Cloaks', 122261, 2), ('Cloaks', 122266, 3), ('Cloaks', 122260, 4), ('Cloaks', 166752, 5), ('Cloaks', 166770, 6),
('Chest', 122387, 1), ('Chest', 122381, 2), ('Chest', 127010, 3), ('Chest', 122379, 4), ('Chest', 122380, 5), ('Chest', 122382, 6), ('Chest', 122383, 7), ('Chest', 122384, 8),
('Pants', 122264, 1), ('Pants', 122251, 2), ('Pants', 127011, 3), ('Pants', 122253, 4), ('Pants', 122252, 5), ('Pants', 122255, 6), ('Pants', 122254, 7), ('Pants', 122256, 8),
('1h_Weapons_Offhands', 122354, 1), ('1h_Weapons_Offhands', 122367, 2), ('1h_Weapons_Offhands', 122385, 3), ('1h_Weapons_Offhands', 122389, 4), ('1h_Weapons_Offhands', 122351, 5), ('1h_Weapons_Offhands', 122369, 6), ('1h_Weapons_Offhands', 122350, 7), ('1h_Weapons_Offhands', 122364, 8), ('1h_Weapons_Offhands', 122391, 9), ('1h_Weapons_Offhands', 122392, 10), ('1h_Weapons_Offhands', 122390, 11),
('2h_Weapons_Ranged', 122349, 1), ('2h_Weapons_Ranged', 122352, 2), ('2h_Weapons_Ranged', 122366, 3), ('2h_Weapons_Ranged', 122386, 4), ('2h_Weapons_Ranged', 140773, 5), ('2h_Weapons_Ranged', 122365, 6), ('2h_Weapons_Ranged', 122363, 7), ('2h_Weapons_Ranged', 122353, 8), ('2h_Weapons_Ranged', 122368, 9), ('2h_Weapons_Ranged', 131733, 10),
('Necklaces', 122663, 1), ('Necklaces', 122667, 2), ('Necklaces', 122664, 3), ('Necklaces', 122662, 4), ('Necklaces', 122668, 5), ('Necklaces', 122666, 6), ('Necklaces', 153130, 7),
('Rings', 128173, 1), ('Rings', 219325, 2), ('Rings', 128172, 3), ('Rings', 122529, 4), ('Rings', 128169, 5),
('Trinkets', 122362, 1), ('Trinkets', 122361, 2), ('Trinkets', 122371, 3), ('Trinkets', 122370, 4), ('Trinkets', 122530, 5), ('Trinkets', 166766, 6), ('Trinkets', 166756, 7), ('Trinkets', 166767, 8), ('Trinkets', 166755, 9), ('Trinkets', 166768, 10), ('Trinkets', 166754, 11), ('Trinkets', 166769, 12), ('Trinkets', 166753, 13), ('Trinkets', 126948, 14),
('Fair_Heirlooms', 126949, 1), ('Fair_Heirlooms', 122396, 2), ('Fair_Heirlooms', 133595, 3), ('Fair_Heirlooms', 133585, 4), ('Fair_Heirlooms', 133596, 5), ('Fair_Heirlooms', 133597, 6), ('Fair_Heirlooms', 133598, 7),
('Upgrades', 122338, 1), ('Upgrades', 122340, 2), ('Upgrades', 151614, 3), ('Upgrades', 167731, 4), ('Upgrades', 187997, 5), ('Upgrades', 204336, 6), ('Upgrades', 122339, 7), ('Upgrades', 122341, 8), ('Upgrades', 151615, 9), ('Upgrades', 167732, 10), ('Upgrades', 187998, 11), ('Upgrades', 204337, 12);