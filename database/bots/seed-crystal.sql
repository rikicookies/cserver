
-- Run only after schema-crystal.sql and after the candidate has compiled.
-- A reserved non-login account and its first test population. No existing rows are overwritten.
START TRANSACTION;
INSERT INTO accounts (id, name, password, email, type, creation)
VALUES (65000, 'crystal_local_bots', SHA1(RANDOM_BYTES(32)), 'crystal-bots@example.invalid', 1, UNIX_TIMESTAMP());

INSERT INTO players (name, group_id, account_id, level, vocation, health, healthmax, experience,
                     mana, manamax, town_id, posx, posy, posz, cap, sex, looktype, conditions, comment, world_id)
SELECT b.name, 1, 65000, 8, b.vocation, 185, 185, 4200, 90, 90,
       t.id, t.posx, t.posy, t.posz, 470, 1, b.looktype, '', '', 1
FROM towns t
CROSS JOIN (
   SELECT 'Catrin Vale' AS name, 1 AS vocation, 130 AS looktype
   UNION ALL SELECT 'Elvin Marsh', 2, 130
   UNION ALL SELECT 'Rhea Flint', 3, 129
   UNION ALL SELECT 'Tomas Alder', 4, 131
   UNION ALL SELECT 'Maris Oaken', 9, 131
) b
WHERE t.name = 'Thais';
COMMIT;

