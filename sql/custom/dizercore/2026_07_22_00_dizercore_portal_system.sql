-- [[
--     Steve Portal Network Master Teleportation System
--     Provides capital city portal room teleportation databse enteries
--     V5.6.2 22.7.26
--     DizerCore
-- ]]

USE `dizercore`;

-- Recreate the portal_system table inside your custom dizercore database
DROP TABLE IF EXISTS `portal_system`;

CREATE TABLE `portal_system` (
  `id` INT(11) NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(100) NOT NULL,
  `faction` TINYINT(4) NOT NULL COMMENT '0 = Alliance, 1 = Horde',
  `map` INT(11) NOT NULL,
  `x` FLOAT NOT NULL,
  `y` FLOAT NOT NULL,
  `z` FLOAT NOT NULL,
  `o` FLOAT NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- Insert only the two major faction portal room coordinates
INSERT INTO `portal_system` (`id`, `name`, `faction`, `map`, `x`, `y`, `z`, `o`) VALUES
(1, 'Stormwind', 0, 0, -9041.286133, 917.609558, 66.687698, 2.261651), -- Alliance Portal Room
(2, 'Orgrimmar', 1, 1, 1446.000610, -4505.048828, 18.443838, 4.856142); -- Horde Portal Room