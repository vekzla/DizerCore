-- sql trigger to provide scenes to all new account on creation
DELIMITER //

DROP TRIGGER IF EXISTS trg_grant_starter_kit_scenes //

CREATE TRIGGER trg_grant_starter_kit_scenes
AFTER INSERT ON auth.account
FOR EACH ROW
BEGIN
    INSERT IGNORE INTO auth.battlenet_account_warband_scenes 
    (battlenetAccountId, warbandSceneId, isFavorite, hasFanfare)
    VALUES 
        (NEW.id, 1, 0, 0), (NEW.id, 4, 0, 0), (NEW.id, 5, 0, 0),
        (NEW.id, 7, 0, 0), (NEW.id, 25, 0, 0), (NEW.id, 29, 0, 0),
        (NEW.id, 119, 0, 0), (NEW.id, 145, 0, 0), (NEW.id, 146, 0, 0);
END;
//
DELIMITER ;