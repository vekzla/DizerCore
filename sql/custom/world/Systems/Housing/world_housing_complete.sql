-- Player Housing System - World DB (static definitions/templates - COMPLETE)

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

-- Neighborhood templates (layout, size, capacity)
CREATE TABLE IF NOT EXISTS `housing_neighborhood_template` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  `neighborhood_type` tinyint unsigned NOT NULL,
  `total_plots` tinyint unsigned NOT NULL DEFAULT '55',
  `cornerstone_plots` tinyint unsigned NOT NULL DEFAULT '1',
  `min_level_requirement` smallint unsigned NOT NULL DEFAULT '1',
  `creation_cost` int unsigned NOT NULL DEFAULT '0',
  `monthly_upkeep` int unsigned NOT NULL DEFAULT '0',
  `max_residents` smallint unsigned NOT NULL DEFAULT '55',
  `description` text,
  PRIMARY KEY (`id`),
  KEY `neighborhood_type` (`neighborhood_type`),
  CONSTRAINT `fk_neighborhood_template_type` FOREIGN KEY (`neighborhood_type`) REFERENCES `housing_neighborhood_type` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- ============================================
-- HOUSE SYSTEM (definitions)
-- ============================================

-- House templates/styles
CREATE TABLE IF NOT EXISTS `housing_house_template` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  `faction` tinyint unsigned NOT NULL COMMENT '0=Alliance, 1=Horde, 2=Neutral',
  `size` tinyint unsigned NOT NULL COMMENT '1=small, 2=medium, 3=large',
  `base_cost` int unsigned NOT NULL,
  `base_xp_requirement` int unsigned NOT NULL DEFAULT '100',
  `max_rooms` tinyint unsigned NOT NULL DEFAULT '3',
  `exterior_decor_slots` smallint unsigned NOT NULL DEFAULT '20',
  `description` text,
  PRIMARY KEY (`id`),
  KEY `faction` (`faction`),
  KEY `size` (`size`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- House upgrades (progression system)
CREATE TABLE IF NOT EXISTS `housing_house_upgrade` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  `house_template_id` int unsigned NOT NULL,
  `level` tinyint unsigned NOT NULL,
  `xp_required` int unsigned NOT NULL,
  `cost_to_upgrade` int unsigned DEFAULT NULL,
  `max_rooms` tinyint unsigned NOT NULL,
  `exterior_slots` smallint unsigned NOT NULL,
  `description` text,
  PRIMARY KEY (`id`),
  KEY `house_template_id` (`house_template_id`),
  CONSTRAINT `fk_house_upgrade_template` FOREIGN KEY (`house_template_id`) REFERENCES `housing_house_template` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- ============================================
-- ROOM SYSTEM (definitions)
-- ============================================

-- Room templates
CREATE TABLE IF NOT EXISTS `housing_room_template` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  `room_type` tinyint unsigned NOT NULL COMMENT '0=generic, 1=bedroom, 2=kitchen, 3=bathroom, 4=storage, 5=library, 6=workshop',
  `width` float NOT NULL,
  `length` float NOT NULL,
  `height` float NOT NULL,
  `max_decor_slots` smallint unsigned NOT NULL,
  `placement_model_id` int unsigned NOT NULL,
  `requires_house_level` tinyint unsigned NOT NULL DEFAULT '1',
  `description` text,
  PRIMARY KEY (`id`),
  KEY `room_type` (`room_type`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- Room customization options
CREATE TABLE IF NOT EXISTS `housing_room_customization` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `room_template_id` int unsigned NOT NULL,
  `customization_type` tinyint unsigned NOT NULL COMMENT '0=ceiling, 1=door, 2=flooring, 3=wall_color',
  `name` varchar(100) NOT NULL,
  `visual_id` int unsigned NOT NULL,
  `cost` int unsigned DEFAULT NULL,
  `description` text,
  PRIMARY KEY (`id`),
  KEY `room_template_id` (`room_template_id`),
  CONSTRAINT `fk_room_customization_template` FOREIGN KEY (`room_template_id`) REFERENCES `housing_room_template` (`id`)
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
  `decor_type` tinyint unsigned NOT NULL COMMENT '0=furniture, 1=lighting, 2=rug, 3=wall_decoration, 4=plant, 5=special, 6=crafted',
  `placement_type` tinyint unsigned NOT NULL COMMENT '0=interior_only, 1=exterior_only, 2=both',
  `model_id` int unsigned NOT NULL,
  `icon_id` int unsigned NOT NULL,
  `is_dyeable` tinyint unsigned NOT NULL DEFAULT '0',
  `dye_slot_count` tinyint unsigned NOT NULL DEFAULT '0',
  `xp_reward` smallint unsigned NOT NULL DEFAULT '10' COMMENT 'XP granted when first learned',
  `rarity` tinyint unsigned NOT NULL DEFAULT '1' COMMENT '1=common, 2=uncommon, 3=rare, 4=epic',
  `required_house_level` tinyint unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`),
  KEY `item_id` (`item_id`),
  KEY `decor_type` (`decor_type`),
  KEY `rarity` (`rarity`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- Decor loot tables (how decor is obtained)
CREATE TABLE IF NOT EXISTS `housing_decor_source` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `decor_definition_id` int unsigned NOT NULL,
  `source_type` tinyint unsigned NOT NULL COMMENT '0=quest_reward, 1=npc_vendor, 2=chest_loot, 3=crafted, 4=vendor_currency, 5=achievement',
  `source_id` int unsigned NOT NULL COMMENT 'Quest/NPC/Crafting ID',
  `quantity` tinyint unsigned NOT NULL DEFAULT '1',
  `cost` int unsigned DEFAULT NULL COMMENT 'For vendor sources',
  `currency_type` tinyint unsigned DEFAULT NULL COMMENT '0=gold, 1=residual_anima, 2=flightstones, etc.',
  PRIMARY KEY (`id`),
  KEY `decor_definition_id` (`decor_definition_id`),
  CONSTRAINT `fk_decor_source_definition` FOREIGN KEY (`decor_definition_id`) REFERENCES `housing_decor_definition` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- ============================================
-- FIXTURE SYSTEM (definitions)
-- ============================================

-- Fixture definitions (permanent house parts)
CREATE TABLE IF NOT EXISTS `housing_fixture_definition` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  `fixture_type` tinyint unsigned NOT NULL COMMENT '0=core_fixture, 1=door, 2=window, 3=roof, 4=foundation',
  `model_id` int unsigned NOT NULL,
  `icon_id` int unsigned NOT NULL,
  `required_house_level` tinyint unsigned NOT NULL DEFAULT '1',
  `customizable` tinyint unsigned NOT NULL DEFAULT '0',
  `description` text,
  PRIMARY KEY (`id`),
  KEY `fixture_type` (`fixture_type`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- Fixture customization options
CREATE TABLE IF NOT EXISTS `housing_fixture_customization` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `fixture_definition_id` int unsigned NOT NULL,
  `customization_name` varchar(100) NOT NULL,
  `visual_id` int unsigned NOT NULL,
  `cost` int unsigned DEFAULT NULL,
  `unlock_level` tinyint unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`),
  KEY `fixture_definition_id` (`fixture_definition_id`),
  CONSTRAINT `fk_fixture_customization_definition` FOREIGN KEY (`fixture_definition_id`) REFERENCES `housing_fixture_definition` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- ============================================
-- ENDEAVOR/CHALLENGE SYSTEM (definitions)
-- ============================================

-- Endeavor templates
CREATE TABLE IF NOT EXISTS `housing_endeavor_template` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(200) NOT NULL,
  `description` text,
  `endeavor_type` tinyint unsigned NOT NULL COMMENT '0=daily, 1=weekly, 2=repeatable',
  `objective_type` tinyint unsigned NOT NULL COMMENT '0=kill_creature, 1=complete_quest, 2=collect_item, 3=place_decor, 4=player_interaction',
  `objective_id` int unsigned NOT NULL,
  `objective_count` smallint unsigned NOT NULL DEFAULT '1',
  `xp_reward` int unsigned NOT NULL DEFAULT '250',
  `gold_reward` int unsigned DEFAULT NULL,
  `item_reward_id` int unsigned DEFAULT NULL,
  `difficulty_level` tinyint unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`),
  KEY `endeavor_type` (`endeavor_type`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- ============================================
-- DEFAULT DATA POPULATION
-- ============================================

-- Insert neighborhood templates
INSERT IGNORE INTO `housing_neighborhood_template` (`name`, `neighborhood_type`, `total_plots`, `cornerstone_plots`, `min_level_requirement`, `creation_cost`, `monthly_upkeep`, `max_residents`, `description`) VALUES
('Public Neighborhood - Starter', 1, 55, 1, 1, 0, 0, 55, 'First neighborhood for new housing players'),
('Public Neighborhood - Main', 1, 55, 1, 10, 0, 0, 55, 'Main public housing district'),
('Guild Haven', 2, 30, 1, 5, 10000, 5000, 30, 'Guild-exclusive housing area'),
('Private Estate', 3, 15, 1, 20, 50000, 10000, 15, 'Private charter neighborhood');

-- Insert house templates
INSERT IGNORE INTO `housing_house_template` (`name`, `faction`, `size`, `base_cost`, `base_xp_requirement`, `max_rooms`, `exterior_decor_slots`, `description`) VALUES
('Cozy Cottage', 0, 1, 1000, 100, 2, 10, 'Small alliance house - perfect for beginners'),
('Cozy Cottage', 1, 1, 1000, 100, 2, 10, 'Small horde house - perfect for beginners'),
('Elegant Manor', 0, 2, 5000, 500, 5, 25, 'Medium alliance house - room for expansion'),
('Elegant Manor', 1, 2, 5000, 500, 5, 25, 'Medium horde house - room for expansion'),
('Grand Estate', 0, 3, 15000, 2000, 10, 50, 'Large alliance house - ultimate luxury'),
('Grand Estate', 1, 3, 15000, 2000, 10, 50, 'Large horde house - ultimate luxury'),
('Neutral Haven', 2, 2, 7500, 750, 6, 30, 'Neutral house available to all');

-- Insert house upgrades
INSERT IGNORE INTO `housing_house_upgrade` (`name`, `house_template_id`, `level`, `xp_required`, `cost_to_upgrade`, `max_rooms`, `exterior_slots`, `description`) VALUES  
('Level 2 Expansion',   1, 2, 100,  500,   2, 15, 'Expand to 2 rooms'),  
('Level 3 Enhancement', 1, 3, 500,  1500,  3, 20, 'Add third room'),  
('Level 2 Expansion',   2, 2, 250,  1000,  5, 30, 'Expand to 5 rooms'),  
('Level 3 Enhancement', 2, 3, 1500, 2000,  7, 40, 'Unlock 7 rooms'),  
('Level 2 Expansion',   3, 2, 1000, 5000, 10, 60, 'Large expansion'),  
('Level 3 Enhancement', 3, 3, 5000, 10000, 15, 80, 'Massive upgrade');

-- Insert room templates
INSERT IGNORE INTO `housing_room_template` (`name`, `room_type`, `width`, `length`, `height`, `max_decor_slots`, `placement_model_id`, `requires_house_level`, `description`) VALUES
('Master Bedroom', 1, 8.0, 10.0, 3.5, 15, 1001, 1, 'Large bedroom for the house owner'),
('Cozy Bedroom', 1, 6.0, 7.0, 3.0, 10, 1002, 1, 'Smaller bedroom'),
('Gourmet Kitchen', 2, 7.0, 9.0, 3.5, 12, 1003, 1, 'Full-featured kitchen'),
('Luxury Bathroom', 3, 5.0, 6.0, 3.0, 8, 1004, 1, 'Elegant bathroom fixtures'),
('Storage Room', 4, 6.0, 8.0, 3.5, 20, 1005, 2, 'Extra storage for materials'),
('Library Study', 5, 7.0, 8.0, 3.5, 18, 1006, 2, 'Quiet study area'),
('Crafting Workshop', 6, 8.0, 10.0, 4.0, 25, 1007, 3, 'Full crafting station area');

-- Insert sample decor items
INSERT IGNORE INTO `housing_decor_definition` (`name`, `description`, `item_id`, `decor_type`, `placement_type`, `model_id`, `icon_id`, `is_dyeable`, `dye_slot_count`, `xp_reward`, `rarity`, `required_house_level`) VALUES
('Wooden Chair', 'Simple wooden chair', 200001, 0, 2, 2001, 3001, 0, 0, 10, 1, 1),
('Oak Table', 'Sturdy oak dining table', 200002, 0, 2, 2002, 3002, 0, 0, 15, 1, 1),
('Fireplace', 'Warm stone fireplace', 200003, 1, 0, 2003, 3003, 0, 0, 25, 2, 1),
('Candelabra', 'Elegant candle lighting', 200004, 1, 2, 2004, 3004, 1, 1, 20, 2, 1),
('Floral Rug', 'Decorative woven rug', 200005, 2, 0, 2005, 3005, 1, 2, 15, 2, 1),
('Bookshelf', 'Wooden bookshelf', 200006, 0, 0, 2006, 3006, 0, 0, 20, 1, 1),
('Potted Plant', 'Green house plant', 200007, 4, 2, 2007, 3007, 0, 0, 10, 1, 1),
('Gemstone Chandelier', 'Rare magical chandelier', 200008, 1, 0, 2008, 3008, 1, 3, 100, 4, 2);

-- Insert sample fixtures
INSERT IGNORE INTO `housing_fixture_definition` (`name`, `fixture_type`, `model_id`, `icon_id`, `required_house_level`, `customizable`, `description`) VALUES
('Front Door', 1, 3001, 4001, 1, 1, 'Main entry to house'),
('Bedroom Window', 2, 3002, 4002, 1, 1, 'Window for natural light'),
('Sloped Roof', 3, 3003, 4003, 1, 0, 'Standard house roof'),
('Stone Foundation', 4, 3004, 4004, 1, 0, 'Base foundation'),
('Ornate Door', 1, 3005, 4005, 2, 1, 'Upgraded decorative door');

-- Insert sample endeavors
INSERT IGNORE INTO `housing_endeavor_template` (`name`, `description`, `endeavor_type`, `objective_type`, `objective_id`, `objective_count`, `xp_reward`, `gold_reward`, `item_reward_id`, `difficulty_level`) VALUES
('Plant a Garden', 'Place 5 plants in your house', 0, 3, 200007, 5, 500, 100, NULL, 1),
('Book Collector', 'Place 3 bookshelves', 0, 3, 200006, 3, 400, 50, NULL, 1),
('Light It Up', 'Place 5 lighting fixtures', 1, 3, 200004, 5, 1000, 500, NULL, 2),
('Neighborly', 'Invite 3 players to your neighborhood', 0, 4, 0, 3, 600, 200, NULL, 2);
