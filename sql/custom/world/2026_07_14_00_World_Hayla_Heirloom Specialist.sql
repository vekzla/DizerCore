USE world;

-- 1. CLEANUP (Remove existing templates, models, and already spawned NPCs to force a clean refresh)
DELETE FROM `creature_template` WHERE `entry` IN (20000001, 20000002);
DELETE FROM `creature_template_model` WHERE `CreatureID` IN (20000001, 20000002);
DELETE FROM `creature` WHERE `id` IN (20000001, 20000002);

-- 2. CREATE TEMPLATES (The Brains)
-- npcflag 129 = 1 (Gossip) + 128 (Vendor)
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
(20000001, 0, 0, 'Hayla', 'Hayla', 'Heirloom Specialist', NULL, 'buy', 0, 0, 35, 129, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 7, 0, 'SmartAI', 0, 1, 0, 0, 0, 0, 1, 0, 0, '', NULL, -66709),
(20000002, 0, 0, 'Hayla', 'Hayla', 'Heirloom Specialist', NULL, 'buy', 0, 0, 35, 129, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 33280, 2048, 0, 0, 0, 7, 0, 'SmartAI', 0, 1, 0, 0, 0, 0, 1, 0, 64, '', NULL, -66709);

-- 3. CREATE MODELS (The Bodies)
INSERT INTO `creature_template_model` (
    `CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`
) VALUES 
(20000001, 0, 5546, 1, 1, -66709),
(20000002, 0, 1358, 1, 1, -66709);