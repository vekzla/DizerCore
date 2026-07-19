-- SQL entries to world database to hold Steve
-- DizerCore V2.0 19/7/26

USE `world`;

-- 1. CLEANUP ALL OLD REMNANTS
DELETE FROM `npc_vendor` WHERE `entry` IN (20000003, 20000004);
DELETE FROM `creature_template` WHERE `entry` IN (20000003, 20000004);
DELETE FROM `creature_template_model` WHERE `CreatureID` IN (20000003, 20000004);
DELETE FROM `creature_template_gossip` WHERE `CreatureID` IN (20000003, 20000004);

-- 2. CREATE STEVE TEMPLATES (Standard NPC, friendly to all Faction 35, npcflag 0)
INSERT INTO `creature_template` (
    `entry`, `KillCredit1`, `KillCredit2`, `name`, `femaleName`, `subname`, 
    `TitleAlt`, `IconName`, `RequiredExpansion`, `VignetteID`, `faction`, 
    `npcflag`, `speed_walk`, `speed_run`, `scale`, `Classification`, 
    `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, 
    `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `unit_flags3`, 
    `family`, `trainer_class`, `type`, `VehicleId`, `AIName`, `MovementType`, 
    `ExperienceModifier`, `RacialLeader`, `movementId`, `WidgetSetID`, 
    `WidgetSetUnitConditionID`, `RegenHealth`, `CreatureImmunitiesId`, 
    `flags_extra`, `ScriptName`, `StringId`, `VerifiedBuild`
) VALUES 
(20000003, 0, 0, 'Steve', NULL, 'Floo Master', NULL, 'buy', 0, 0, 35, 0, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 7, 0, '', 0, 1, 0, 0, 0, 0, 1, 0, 0, '', NULL, 68453),
(20000004, 0, 0, 'Steve', NULL, 'Floo Master', NULL, 'buy', 0, 0, 35, 0, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 7, 0, '', 0, 1, 0, 0, 0, 0, 1, 0, 0, '', NULL, 68453);

-- 3. CREATE STEVE MODELS (Human 5549 for Alliance, Orc 1313 for Horde)
INSERT INTO `creature_template_model` (
    `CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`
) VALUES 
(20000003, 0, 5549, 1, 1, 68453), 
(20000004, 0, 1313, 1, 1, 68453);