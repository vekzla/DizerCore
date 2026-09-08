-- Player Housing System - World DB (static definitions/templates)  
-- Requires World of Warcraft: Midnight expansion  
  
-- ============================================  
-- NEIGHBORHOOD SYSTEM (definitions)  
-- ============================================  
  
-- Neighborhood types  
CREATE TABLE IF NOT EXISTS `housing_neighborhood_type` (  
  `id` tinyint unsigned NOT NULL AUTO_INCREMENT,  
  `name` varchar(50) NOT NULL,  
  `description` text,  
  PRIMARY KEY (`id`)  
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;  
  
INSERT INTO `housing_neighborhood_type` (`id`, `name`, `description`) VALUES  
(1, 'Public', 'Server-maintained neighborhoods with random players'),  
(2, 'Guild', 'Guild-specific neighborhoods created by guild masters'),  
(3, 'Private', 'Private neighborhoods created by charters');

-- ============================================  
-- HOUSE SYSTEM (definitions)  
-- ============================================  
  
-- House templates/styles  
CREATE TABLE IF NOT EXISTS `housing_house_template` (  
  `id` int unsigned NOT NULL AUTO_INCREMENT,  
  `name` varchar(100) NOT NULL,  
  `faction` tinyint unsigned NOT NULL COMMENT '0=Alliance, 1=Horde',  
  `size` tinyint unsigned NOT NULL COMMENT '1=small, 2=medium, 3=large',  
  `base_cost` int unsigned NOT NULL,  
  `description` text,  
  PRIMARY KEY (`id`),  
  KEY `faction` (`faction`)  
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;  
  
-- ============================================  
-- ROOM SYSTEM (definitions)  
-- ============================================  
  
-- Room templates  
CREATE TABLE IF NOT EXISTS `housing_room_template` (  
  `id` int unsigned NOT NULL AUTO_INCREMENT,  
  `name` varchar(100) NOT NULL,  
  `room_type` tinyint unsigned NOT NULL COMMENT '0=generic, 1=bedroom, 2=kitchen, 3=bathroom, 4=storage, etc.',  
  `width` float NOT NULL,  
  `length` float NOT NULL,  
  `height` float NOT NULL,  
  `max_decor_slots` smallint unsigned NOT NULL,  
  PRIMARY KEY (`id`)  
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;  
  
-- ============================================  
-- DECOR SYSTEM (definitions)  
-- ============================================  
  
-- Decor item definitions  
CREATE TABLE IF NOT EXISTS `housing_decor_definition` (  
  `id` int unsigned NOT NULL AUTO_INCREMENT,  
  `name` varchar(200) NOT NULL,  
  `description` text,  
  `item_id` int unsigned DEFAULT NULL COMMENT 'Associated item ID if learnable from items',  
  `decor_type` tinyint unsigned NOT NULL COMMENT '0=furniture, 1=lighting, 2=rug, 3=wall decoration, 4=plant, 5=special',  
  `placement_type` tinyint unsigned NOT NULL COMMENT '0=interior only, 1=exterior only, 2=both',  
  `model_id` int unsigned NOT NULL,  
  `icon_id` int unsigned NOT NULL,  
  `is_dyeable` tinyint unsigned NOT NULL DEFAULT '0',  
  `dye_slot_count` tinyint unsigned NOT NULL DEFAULT '0',  
  `xp_reward` tinyint unsigned NOT NULL DEFAULT '10' COMMENT 'XP granted when first learned',  
  `rarity` tinyint unsigned NOT NULL DEFAULT '1' COMMENT '1=common, 2=uncommon, 3=rare, 4=epic',  
  PRIMARY KEY (`id`),  
  KEY `item_id` (`item_id`)  
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;