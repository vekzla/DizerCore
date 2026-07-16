-- populate existing accounts with new scense
INSERT IGNORE INTO auth.battlenet_account_warband_scenes 
(battlenetAccountId, warbandSceneId, isFavorite, hasFanfare)
SELECT a.id, s.sceneId, 0, 0
FROM auth.account a
CROSS JOIN (
    SELECT 1 AS sceneId UNION SELECT 4 UNION SELECT 5 UNION 
    SELECT 7 UNION SELECT 25 UNION SELECT 29 UNION 
    SELECT 119 UNION SELECT 145 UNION SELECT 146
) AS s;