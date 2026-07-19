-- Starter kits providing new players with equipment
-- dizercore
-- V1.0 19.7.26
CREATE TABLE IF NOT EXISTS `dizercore`.`starter_kit` (
  `id` INT(11) NOT NULL AUTO_INCREMENT,
  `item_id` INT(11) NOT NULL,
  `type` VARCHAR(20) NOT NULL, -- 'mount' or 'bag'
  `count` INT(11) DEFAULT 1,
  PRIMARY KEY (`id`)
);

-- Populate it
INSERT INTO `dizercore`.`starter_kit` (`item_id`, `type`, `count`) VALUES
(97560, 'mount', 1),
(1235819, 'mount', 1),
(240161, 'bag', 4),
(222854, 'bag', 1);