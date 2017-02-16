
-- Dodawanie obowiązku
INSERT INTO flat_mate.chore (name, frequency_id, flat_id)
	VALUES('nazwa obowiazku', 'WEEKLY', 1);

-- Usuwanie obowiązku
DELETE FROM flat_mate.chore WHERE id = 1;

-- Dodawanie do planu obowiązków
INSERT INTO flat_mate.chores_plan (date, chore_id, assigned_mail, done)
	VALUES(215125, 2, 'piotr@gmail.com', FALSE);

-- Usuwanie z planu obowiązków
DELETE FROM flat_mate.chores_plan WHERE
	date = 21541 AND chore_id = 1;

-- Listowanie planu obowiązków dla mieszkania
SELECT c.name, cp.date, cp.assigned_mail, cp.done
    FROM flat_mate.chores_plan cp
    JOIN flat_mate.chore c ON c.id = cp.chore_id
    WHERE c.flat_id = 1;

-- Listowanie obowiązków dla mieszkania
SELECT id, name, frequency_id, flat_id
    FROM flat_mate.chore
    WHERE flat_id = 1;
