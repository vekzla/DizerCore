-- Player Housing System - Characters DB (per-character/account runtime state)  
-- Requires World of Warcraft: Midnight expansion  
  
-- ============================================  
-- NEIGHBORHOOD SYSTEM (runtime state)  
-- ============================================  
  
-- Neighborhoods  
CREATE TABLE IF NOT EXISTS `housing_neighborhood` (  
  `id` int unsigned NOT NULL AUTO_INCREMENT,  
  `name` varchar(100) NOT NULL,  
  `type` tinyint unsigned NOT NULL DEFAULT '1',  
  `faction` tinyint unsigned NOT NULL COMMENT '0=Alliance, 1=Horde',  
  `map_id` int unsigned NOT NULL COMMENT 'Map ID for the neighborhood instance',  
  `guild_id` int unsigned DEFAULT NULL COMMENT 'Guild ID for guild neighborhoods',  
  `owner_account_id` int unsigned DEFAULT NULL COMMENT 'Account ID for private neighborhoods',  
  `created_by` bigint unsigned NOT NULL COMMENT 'Character GUID who created the neighborhood',  
  `creation_time` bigint NOT NULL,  
  `is_active` tinyint unsigned NOT NULL DEFAULT '1',  
  PRIMARY KEY (`id`),  
  KEY `type` (`type`),  
  KEY `faction` (`faction`),  
  KEY `guild_id` (`guild_id`),  
  KEY `owner_account_id` (`owner_account_id`)  
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;  
  
-- Neighborhood plots (55 plots per neighborhood)  
CREATE TABLE IF NOT EXISTS `housing_neighborhood_plot` (  
  `id` int unsigned NOT NULL AUTO_INCREMENT,  
  `neighborhood_id` int unsigned NOT NULL,  
  `plot_number` tinyint unsigned NOT NULL COMMENT '1-55',  
  `position_x` float NOT NULL,  
  `position_y` float NOT NULL,  
  `position_z` float NOT NULL,  
  `orientation` float NOT NULL,  
  `is_cornerstone` tinyint unsigned NOT NULL DEFAULT '0' COMMENT '1 if this is a cornerstone plot',  
  `owner_character_guid` bigint unsigned DEFAULT NULL COMMENT 'Current owner of this plot',  
  `house_id` int unsigned DEFAULT NULL COMMENT 'Associated house ID',  
  PRIMARY KEY (`id`),  
  UNIQUE KEY `neighborhood_plot` (`neighborhood_id`, `plot_number`),  
  KEY `owner_character_guid` (`owner_character_guid`),  
  KEY `house_id` (`house_id`),  
  CONSTRAINT `fk_neighborhood_plot_neighborhood` FOREIGN KEY (`neighborhood_id`) REFERENCES `housing_neighborhood` (`id`) ON DELETE CASCADE  
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;  
  
-- Neighborhood members (for guild and private neighborhoods)  
CREATE TABLE IF NOT EXISTS `housing_neighborhood_member` (  
  `id` int unsigned NOT NULL AUTO_INCREMENT,  
  `neighborhood_id` int unsigned NOT NULL,  
  `character_guid` bigint unsigned NOT NULL,  
  `rank` tinyint unsigned NOT NULL DEFAULT '0' COMMENT '0=resident, 1=officer, 2=owner',  
  `join_time` bigint NOT NULL,  
  PRIMARY KEY (`id`),  
  UNIQUE KEY `neighborhood_character` (`neighborhood_id`, `character_guid`),  
  KEY `character_guid` (`character_guid`),  
  CONSTRAINT `fk_neighborhood_member_neighborhood` FOREIGN KEY (`neighborhood_id`) REFERENCES `housing_neighborhood` (`id`) ON DELETE CASCADE  
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;  
  
-- Neighborhood invitations  
CREATE TABLE IF NOT EXISTS `housing_neighborhood_invitation` (  
  `id` int unsigned NOT NULL AUTO_INCREMENT,  
  `neighborhood_id` int unsigned NOT NULL,  
  `inviter_character_guid` bigint unsigned NOT NULL,  
  `invitee_character_guid` bigint unsigned NOT NULL,  
  `invitation_time` bigint NOT NULL,  
  `expiration_time` bigint NOT NULL,  
  `status` tinyint unsigned NOT NULL DEFAULT '0' COMMENT '0=pending, 1=accepted, 2=declined, 3=cancelled',  
  PRIMARY KEY (`id`),  
  KEY `neighborhood_id` (`neighborhood_id`),  
  KEY `invitee_character_guid` (`invitee_character_guid`),  
  CONSTRAINT `fk_neighborhood_invitation_neighborhood` FOREIGN KEY (`neighborhood_id`) REFERENCES `housing_neighborhood` (`id`) ON DELETE CASCADE  
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;  
  
-- ============================================  
-- HOUSE SYSTEM (runtime state)  
-- ============================================  
  
-- Player houses  
CREATE TABLE IF NOT EXISTS `housing_house` (  
  `id` int unsigned NOT NULL AUTO_INCREMENT,  
  `owner_account_id` int unsigned NOT NULL,  
  `owner_character_guid` bigint unsigned NOT NULL,  
  `template_id` int unsigned NOT NULL,  
  `neighborhood_id` int unsigned NOT NULL,  
  `plot_id` int unsigned NOT NULL,  
  `house_level` tinyint unsigned NOT NULL DEFAULT '1',  
  `purchase_time` bigint NOT NULL DEFAULT '0',  
  `house_xp` int unsigned NOT NULL DEFAULT '0',  
  `xp_needed_for_next_level` int unsigned NOT NULL DEFAULT '100',  
  `name` varchar(100) DEFAULT NULL,  
  `creation_time` bigint NOT NULL DEFAULT '0',  
  `last_modified` bigint NOT NULL DEFAULT '0',  
  `exterior_lock_state` tinyint unsigned NOT NULL DEFAULT '0',  
  `interior_lock_state` tinyint unsigned NOT NULL DEFAULT '0',  
  PRIMARY KEY (`id`),  
  KEY `owner_account_id` (`owner_account_id`),  
  KEY `owner_character_guid` (`owner_character_guid`),  
  KEY `neighborhood_id` (`neighborhood_id`),  
  KEY `plot_id` (`plot_id`),  
  KEY `template_id` (`template_id`)  
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;  
  
-- House secondary owners (for shared ownership)  
CREATE TABLE IF NOT EXISTS `housing_house_secondary_owner` (  
  `id` int unsigned NOT NULL AUTO_INCREMENT,  
  `house_id` int unsigned NOT NULL,  
  `character_guid` bigint unsigned NOT NULL,  
  `added_time` bigint NOT NULL,  
  PRIMARY KEY (`id`),  
  UNIQUE KEY `house_character` (`house_id`, `character_guid`),  
  CONSTRAINT `fk_house_secondary_owner_house` FOREIGN KEY (`house_id`) REFERENCES `housing_house` (`id`) ON DELETE CASCADE  
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;  
  
-- ============================================  
-- ROOM SYSTEM (runtime state)  
-- ============================================  
  
CREATE TABLE IF NOT EXISTS `housing_house_room` (  
  `id` int unsigned NOT NULL AUTO_INCREMENT,  
  `house_id` int unsigned NOT NULL,  
  `room_template_id` int unsigned NOT NULL,  
  `position_x` float NOT NULL,  
  `position_y` float NOT NULL,  
  `position_z` float NOT NULL,  
  `orientation` float NOT NULL,  
  `ceiling_type` tinyint unsigned NOT NULL DEFAULT '0',  
  `door_type` tinyint unsigned NOT NULL DEFAULT '0',  
  `component_theme` tinyint unsigned NOT NULL DEFAULT '0',  
  PRIMARY KEY (`id`),  
  KEY `house_id` (`house_id`),  
  KEY `room_template_id` (`room_template_id`),  
  CONSTRAINT `fk_house_room_house` FOREIGN KEY (`house_id`) REFERENCES `housing_house` (`id`) ON DELETE CASCADE  
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;  
  
-- ============================================  
-- DECOR SYSTEM (runtime state)  
-- ============================================  
  
CREATE TABLE IF NOT EXISTS `housing_player_decor` (  
  `id` int unsigned NOT NULL AUTO_INCREMENT,  
  `account_id` int unsigned NOT NULL,  
  `decor_definition_id` int unsigned NOT NULL,  
  `learn_time` bigint NOT NULL,  
  `quantity` smallint unsigned NOT NULL DEFAULT '1',  
  PRIMARY KEY (`id`),  
  UNIQUE KEY `account_decor` (`account_id`, `decor_definition_id`),  
  KEY `decor_definition_id` (`decor_definition_id`)  
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;  
  
CREATE TABLE IF NOT EXISTS `housing_decor_placement` (  
  `id` int unsigned NOT NULL AUTO_INCREMENT,  
  `house_id` int unsigned NOT NULL,  
  `room_id` int unsigned DEFAULT NULL COMMENT 'NULL if placed on exterior plot',  
  `decor_definition_id` int unsigned NOT NULL,  
  `position_x` float NOT NULL,  
  `position_y` float NOT NULL,  
  `position_z` float NOT NULL,  
  `orientation` float NOT NULL,  
  `scale` float NOT NULL DEFAULT '1.0',  
  `is_exterior` tinyint unsigned NOT NULL DEFAULT '0',  
  `dye_slot_1` int unsigned DEFAULT NULL,  
  `dye_slot_2` int unsigned DEFAULT NULL,  
  `dye_slot_3` int unsigned DEFAULT NULL,  
  `is_locked` tinyint unsigned NOT NULL DEFAULT '0',  
  `placement_time` bigint NOT NULL,  
  PRIMARY KEY (`id`),  
  KEY `house_id` (`house_id`),  
  KEY `room_id` (`room_id`),  
  KEY `decor_definition_id` (`decor_definition_id`),  
  CONSTRAINT `fk_decor_placement_house` FOREIGN KEY (`house_id`) REFERENCES `housing_house` (`id`) ON DELETE CASCADE,  
  CONSTRAINT `fk_decor_placement_room` FOREIGN KEY (`room_id`) REFERENCES `housing_house_room` (`id`) ON DELETE CASCADE  
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;  
  
CREATE TABLE IF NOT EXISTS `housing_decor_storage` (  
  `id` int unsigned NOT NULL AUTO_INCREMENT,  
  `house_id` int unsigned NOT NULL,  
  `decor_definition_id` int unsigned NOT NULL,  
  `quantity` smallint unsigned NOT NULL DEFAULT '1',  
  `added_time` bigint NOT NULL,  
  PRIMARY KEY (`id`),  
  KEY `house_id` (`house_id`),  
  KEY `decor_definition_id` (`decor_definition_id`),  
  CONSTRAINT `fk_decor_storage_house` FOREIGN KEY (`house_id`) REFERENCES `housing_house` (`id`) ON DELETE CASCADE  
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;  
  
-- ============================================  
-- BLUEPRINT SYSTEM (characters DB)  
-- ============================================  
  
CREATE TABLE IF NOT EXISTS `housing_blueprint` (  
  `id` int unsigned NOT NULL AUTO_INCREMENT,  
  `account_id` int unsigned NOT NULL,  
  `name` varchar(100) NOT NULL,  
  `description` text,  
  `template_id` int unsigned NOT NULL,  
  `created_time` bigint NOT NULL,  
  `last_modified` bigint NOT NULL,  
  `is_public` tinyint unsigned NOT NULL DEFAULT '0',  
  `share_code` varchar(20) DEFAULT NULL,  
  PRIMARY KEY (`id`),  
  KEY `account_id` (`account_id`),  
  KEY `share_code` (`share_code`)  
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;  
  
CREATE TABLE IF NOT EXISTS `housing_blueprint_room` (  
  `id` int unsigned NOT NULL AUTO_INCREMENT,  
  `blueprint_id` int unsigned NOT NULL,  
  `room_template_id` int unsigned NOT NULL,  
  `position_x` float NOT NULL,  
  `position_y` float NOT NULL,  
  `position_z` float NOT NULL,  
  `orientation` float NOT NULL,  
  `ceiling_type` tinyint unsigned NOT NULL DEFAULT '0',  
  `door_type` tinyint unsigned NOT NULL DEFAULT '0',  
  `component_theme` tinyint unsigned NOT NULL DEFAULT '0',  
  PRIMARY KEY (`id`),  
  KEY `blueprint_id` (`blueprint_id`),  
  CONSTRAINT `fk_blueprint_room_blueprint` FOREIGN KEY (`blueprint_id`) REFERENCES `housing_blueprint` (`id`) ON DELETE CASCADE  
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;  
  
CREATE TABLE IF NOT EXISTS `housing_blueprint_decor` (  
  `id` int unsigned NOT NULL AUTO_INCREMENT,  
  `blueprint_id` int unsigned NOT NULL,  
  `room_id` int unsigned DEFAULT NULL,  
  `decor_definition_id` int unsigned NOT NULL,  
  `position_x` float NOT NULL,  
  `position_y` float NOT NULL,  
  `position_z` float NOT NULL,  
  `orientation` float NOT NULL,  
  `scale` float NOT NULL DEFAULT '1.0',  
  `is_exterior` tinyint unsigned NOT NULL DEFAULT '0',  
  `dye_slot_1` int unsigned DEFAULT NULL,  
  `dye_slot_2` int unsigned DEFAULT NULL,  
  `dye_slot_3` int unsigned DEFAULT NULL,  
  PRIMARY KEY (`id`),  
  KEY `blueprint_id` (`blueprint_id`),  
  CONSTRAINT `fk_blueprint_decor_blueprint` FOREIGN KEY (`blueprint_id`) REFERENCES `housing_blueprint` (`id`) ON DELETE CASCADE  
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;  
  
-- ============================================  
-- PERMISSIONS SYSTEM  
-- ============================================  
  
CREATE TABLE IF NOT EXISTS `housing_house_permissions` (  
  `id` int unsigned NOT NULL AUTO_INCREMENT,  
  `house_id` int unsigned NOT NULL,  
  `permission_type` tinyint unsigned NOT NULL COMMENT '0=neighbors, 1=guild members, 2=party members, 3=friends, 4=specific character',  
  `target_id` bigint unsigned DEFAULT NULL COMMENT 'Character GUID if permission_type=4',  
  `exterior_access` tinyint unsigned NOT NULL DEFAULT '0',  
  `interior_access` tinyint unsigned NOT NULL DEFAULT '0',  
  `can_edit` tinyint unsigned NOT NULL DEFAULT '0',  
  `set_time` bigint NOT NULL,  
  PRIMARY KEY (`id`),  
  KEY `house_id` (`house_id`),  
  KEY `permission_type` (`permission_type`),  
  KEY `target_id` (`target_id`),  
  CONSTRAINT `fk_house_permissions_house` FOREIGN KEY (`house_id`) REFERENCES `housing_house` (`id`) ON DELETE CASCADE  
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;  
  
-- ============================================  
-- ENDEAVOR/CHALLENGE SYSTEM  
-- ============================================  
  
CREATE TABLE IF NOT EXISTS `housing_neighborhood_endeavor` (  
  `id` int unsigned NOT NULL AUTO_INCREMENT,  
  `neighborhood_id` int unsigned NOT NULL,  
  `endeavor_type` tinyint unsigned NOT NULL COMMENT '0=daily, 1=weekly',  
  `title` varchar(200) NOT NULL,  
  `description` text,  
  `requirement_type` tinyint unsigned NOT NULL COMMENT '0=kill creature, 1=complete quest, 2=collect item, etc.',  
  `requirement_id` int unsigned NOT NULL,  
  `requirement_count` smallint unsigned NOT NULL,  
  `xp_reward` int unsigned NOT NULL DEFAULT '250',  
  `start_time` bigint NOT NULL,  
  `end_time` bigint NOT NULL,  
  `is_active` tinyint unsigned NOT NULL DEFAULT '1',  
  PRIMARY KEY (`id`),  
  KEY `neighborhood_id` (`neighborhood_id`),  
  KEY `endeavor_type` (`endeavor_type`),  
  CONSTRAINT `fk_neighborhood_endeavor_neighborhood` FOREIGN KEY (`neighborhood_id`) REFERENCES `housing_neighborhood` (`id`) ON DELETE CASCADE  
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;  
  
CREATE TABLE IF NOT EXISTS `housing_player_endeavor` (  
  `id` int unsigned NOT NULL AUTO_INCREMENT,  
  `character_guid` bigint unsigned NOT NULL,  
  `house_id` int unsigned NOT NULL,  
  `endeavor_id` int unsigned NOT NULL,  
  `progress` smallint unsigned NOT NULL DEFAULT '0',  
  `is_completed` tinyint unsigned NOT NULL DEFAULT '0',  
  `completion_time` bigint DEFAULT NULL,  
  `is_active` tinyint unsigned NOT NULL DEFAULT '1' COMMENT 'Character active endeavor for this house',  
  PRIMARY KEY (`id`),  
  UNIQUE KEY `character_house_endeavor` (`character_guid`, `house_id`, `endeavor_id`),  
  KEY `house_id` (`house_id`),  
  KEY `endeavor_id` (`endeavor_id`),  
  CONSTRAINT `fk_player_endeavor_house` FOREIGN KEY (`house_id`) REFERENCES `housing_house` (`id`) ON DELETE CASCADE,  
  CONSTRAINT `fk_player_endeavor_endeavor` FOREIGN KEY (`endeavor_id`) REFERENCES `housing_neighborhood_endeavor` (`id`) ON DELETE CASCADE  
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;  
  
-- ============================================  
-- FIXTURE SYSTEM  
-- ============================================  
  
CREATE TABLE IF NOT EXISTS `housing_house_fixture` (  
  `id` int unsigned NOT NULL AUTO_INCREMENT,  
  `house_id` int unsigned NOT NULL,  
  `fixture_type` tinyint unsigned NOT NULL COMMENT '0=core fixture, 1=door, 2=window, 3=other',  
  `fixture_definition_id` int unsigned NOT NULL,  
  `position_x` float NOT NULL,  
  `position_y` float NOT NULL,  
  `position_z` float NOT NULL,  
  `orientation` float NOT NULL,  
  `is_core_fixture` tinyint unsigned NOT NULL DEFAULT '0',  
  PRIMARY KEY (`id`),  
  KEY `house_id` (`house_id`),  
  CONSTRAINT `fk_house_fixture_house` FOREIGN KEY (`house_id`) REFERENCES `housing_house` (`id`) ON DELETE CASCADE  
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;