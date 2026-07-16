CREATE TABLE `account_warband_groups` (
  `id` BIGINT(20) UNSIGNED NOT NULL,
  `accountId` INT(10) UNSIGNED NOT NULL,
  `realmId` INT(10) UNSIGNED NOT NULL DEFAULT '1',
  `orderIndex` TINYINT(3) UNSIGNED NOT NULL,
  `name` VARCHAR(257) NOT NULL,
  `warbandSceneId` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `flags` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `idx_account` (`accountId`)
) ENGINE=INNODB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE `account_warband_group_members` (
  `groupId` BIGINT(20) UNSIGNED NOT NULL,
  `characterGuid` BIGINT(20) UNSIGNED NOT NULL,
  `placementId` INT(10) UNSIGNED NOT NULL,
  `type` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  PRIMARY KEY (`groupId`, `characterGuid`),
  CONSTRAINT `fk_warband_group` FOREIGN KEY (`groupId`) REFERENCES `account_warband_groups` (`id`) ON DELETE CASCADE
) ENGINE=INNODB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;