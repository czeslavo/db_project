DROP SCHEMA IF EXISTS flat_mate CASCADE;

CREATE SCHEMA flat_mate;

CREATE TABLE flat_mate.chore_frequency (
                id VARCHAR(15) NOT NULL,
                days INTEGER DEFAULT 1 NOT NULL,
                weeks VARCHAR DEFAULT 0 NOT NULL,
                months VARCHAR DEFAULT 0 NOT NULL,
                CONSTRAINT chore_frequency_pk PRIMARY KEY (id)
);


CREATE TABLE flat_mate.system_user (
                mail VARCHAR(50) NOT NULL,
                nickname VARCHAR NOT NULL,
                name VARCHAR(50),
                surname VARCHAR(50),
                password TEXT NULL,
                CONSTRAINT system_user_pk PRIMARY KEY (mail)
);


CREATE UNIQUE INDEX user_nickaname_idx
 ON flat_mate.system_user
 ( nickname );

CREATE SEQUENCE flat_mate.recipe_id_seq;

CREATE TABLE flat_mate.recipe (
                id INTEGER NOT NULL DEFAULT nextval('flat_mate.recipe_id_seq'),
                name VARCHAR(50) NOT NULL,
                description TEXT,
                author_mail VARCHAR(50),
                CONSTRAINT recipe_pk PRIMARY KEY (id)
);


ALTER SEQUENCE flat_mate.recipe_id_seq OWNED BY flat_mate.recipe.id;

CREATE TABLE flat_mate.dinner_plan (
                date INTEGER NOT NULL,
                recipe_id INTEGER,
                flat_id INTEGER NOT NULL,
                assigned_mail VARCHAR(50),
                final_price NUMERIC(16, 2),
                done BOOLEAN DEFAULT FALSE NOT NULL,
                CONSTRAINT dinner_plan_pk PRIMARY KEY (date, flat_id)
);


CREATE INDEX dinner_plan_date_k
 ON flat_mate.dinner_plan
 ( date DESC );

CREATE SEQUENCE flat_mate.recipe_ingredient_id_seq;

CREATE TABLE flat_mate.recipe_ingredient (
                id INTEGER NOT NULL DEFAULT nextval('flat_mate.recipe_ingredient_id_seq'),
                name VARCHAR(50) NOT NULL,
                recipe_id INTEGER NOT NULL,
                CONSTRAINT recipe_ingredient_pk PRIMARY KEY (id)
);


ALTER SEQUENCE flat_mate.recipe_ingredient_id_seq OWNED BY flat_mate.recipe_ingredient.id;

CREATE SEQUENCE flat_mate.flat_id_seq;

CREATE TABLE flat_mate.flat (
                id INTEGER NOT NULL DEFAULT nextval('flat_mate.flat_id_seq'),
                name VARCHAR(50) NOT NULL,
                flat_admin_mail VARCHAR(50),
                CONSTRAINT flat_pk PRIMARY KEY (id)
);


ALTER SEQUENCE flat_mate.flat_id_seq OWNED BY flat_mate.flat.id;

CREATE SEQUENCE flat_mate.note_id_seq;

CREATE TABLE flat_mate.note (
                id INTEGER NOT NULL DEFAULT nextval('flat_mate.note_id_seq'),
                date INTEGER NOT NULL,
                content TEXT NOT NULL,
                active BOOLEAN DEFAULT TRUE NOT NULL,
                author_mail VARCHAR(50),
                flat_id INTEGER NOT NULL,
                CONSTRAINT note_pk PRIMARY KEY (id)
);


ALTER SEQUENCE flat_mate.note_id_seq OWNED BY flat_mate.note.id;

CREATE SEQUENCE flat_mate.other_expense_id_seq;

CREATE TABLE flat_mate.other_expense (
                id INTEGER NOT NULL DEFAULT nextval('flat_mate.other_expense_id_seq'),
                user_mail VARCHAR(50) NOT NULL,
                name VARCHAR(50) NOT NULL,
                flat_id INTEGER NOT NULL,
                date INTEGER NOT NULL,
                CONSTRAINT other_expense_pk PRIMARY KEY (id)
);


ALTER SEQUENCE flat_mate.other_expense_id_seq OWNED BY flat_mate.other_expense.id;

CREATE SEQUENCE flat_mate.chore_id_seq;

CREATE TABLE flat_mate.chore (
                id INTEGER NOT NULL DEFAULT nextval('flat_mate.chore_id_seq'),
                name VARCHAR(50) NOT NULL,
                frequency_id VARCHAR(15) NOT NULL,
                flat_id INTEGER NOT NULL,
                CONSTRAINT chore_pk PRIMARY KEY (id)
);


ALTER SEQUENCE flat_mate.chore_id_seq OWNED BY flat_mate.chore.id;

CREATE TABLE flat_mate.chores_plan (
                date INTEGER NOT NULL,
                chore_id INTEGER NOT NULL,
                assigned_mail VARCHAR(50) NOT NULL,
                done BOOLEAN DEFAULT FALSE NOT NULL,
                CONSTRAINT chores_plan_pk PRIMARY KEY (date, chore_id)
);


CREATE INDEX chores_plan_date_k
 ON flat_mate.chores_plan
 ( date DESC );

CREATE SEQUENCE flat_mate.equipment_id_seq;

CREATE TABLE flat_mate.equipment (
                id INTEGER NOT NULL DEFAULT nextval('flat_mate.equipment_id_seq'),
                name VARCHAR NOT NULL,
                owner_mail VARCHAR(50) NOT NULL,
                flat_id INTEGER,
                value NUMERIC(16, 2) NOT NULL,
                CONSTRAINT equipment_pk PRIMARY KEY (id)
);


ALTER SEQUENCE flat_mate.equipment_id_seq OWNED BY flat_mate.equipment.id;

CREATE TABLE flat_mate.flat_user (
                user_mail VARCHAR(50) NOT NULL,
                flat_id INTEGER NOT NULL,
                CONSTRAINT flat_user_pk PRIMARY KEY (user_mail, flat_id)
);


ALTER TABLE flat_mate.chore ADD CONSTRAINT chore_frequency_chore_fk
FOREIGN KEY (frequency_id)
REFERENCES flat_mate.chore_frequency (id)
ON DELETE SET DEFAULT
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE flat_mate.flat_user ADD CONSTRAINT user_flat_user_fk
FOREIGN KEY (user_mail)
REFERENCES flat_mate.system_user (mail)
ON DELETE CASCADE
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE flat_mate.equipment ADD CONSTRAINT user_equipment_fk
FOREIGN KEY (owner_mail)
REFERENCES flat_mate.system_user (mail)
ON DELETE CASCADE
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE flat_mate.flat ADD CONSTRAINT user_flat_fk
FOREIGN KEY (flat_admin_mail)
REFERENCES flat_mate.system_user (mail)
ON DELETE SET NULL
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE flat_mate.recipe ADD CONSTRAINT user_recipe_fk
FOREIGN KEY (author_mail)
REFERENCES flat_mate.system_user (mail)
ON DELETE SET NULL
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE flat_mate.dinner_plan ADD CONSTRAINT user_dinner_plan_fk
FOREIGN KEY (assigned_mail)
REFERENCES flat_mate.system_user (mail)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE flat_mate.chores_plan ADD CONSTRAINT user_chores_plan_fk
FOREIGN KEY (assigned_mail)
REFERENCES flat_mate.system_user (mail)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE flat_mate.other_expense ADD CONSTRAINT user_other_expense_fk
FOREIGN KEY (user_mail)
REFERENCES flat_mate.system_user (mail)
ON DELETE CASCADE
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE flat_mate.note ADD CONSTRAINT user_note_fk
FOREIGN KEY (author_mail)
REFERENCES flat_mate.system_user (mail)
ON DELETE SET NULL
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE flat_mate.recipe_ingredient ADD CONSTRAINT recipe_recipe_ingredient_fk
FOREIGN KEY (recipe_id)
REFERENCES flat_mate.recipe (id)
ON DELETE CASCADE
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE flat_mate.dinner_plan ADD CONSTRAINT recipe_dinner_plan_fk
FOREIGN KEY (recipe_id)
REFERENCES flat_mate.recipe (id)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE flat_mate.flat_user ADD CONSTRAINT flat_flat_user_fk
FOREIGN KEY (flat_id)
REFERENCES flat_mate.flat (id)
ON DELETE CASCADE
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE flat_mate.equipment ADD CONSTRAINT flat_equipment_fk
FOREIGN KEY (flat_id)
REFERENCES flat_mate.flat (id)
ON DELETE CASCADE
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE flat_mate.chore ADD CONSTRAINT flat_chore_fk
FOREIGN KEY (flat_id)
REFERENCES flat_mate.flat (id)
ON DELETE CASCADE
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE flat_mate.other_expense ADD CONSTRAINT flat_other_expense_fk
FOREIGN KEY (flat_id)
REFERENCES flat_mate.flat (id)
ON DELETE CASCADE
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE flat_mate.note ADD CONSTRAINT flat_note_fk
FOREIGN KEY (flat_id)
REFERENCES flat_mate.flat (id)
ON DELETE CASCADE
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE flat_mate.chores_plan ADD CONSTRAINT chore_chores_plan_fk
FOREIGN KEY (chore_id)
REFERENCES flat_mate.chore (id)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE flat_mate.dinner_plan ADD CONSTRAINT flat_dinner_plan_fk
FOREIGN KEY (flat_id)
REFERENCES flat_mate.flat (id)
ON DELETE CASCADE
NOT DEFERRABLE;

CREATE EXTENSION IF NOT EXISTS pgcrypto
    WITH SCHEMA flat_mate;


-- Funkcje

-- Zwraca id mieszkania dla podanego obowiązku
CREATE OR REPLACE FUNCTION get_flat_id_for_chore(chore_id integer)
    RETURNS TABLE (
        id integer
    ) 
AS
$$
BEGIN
    RETURN QUERY (SELECT flat_id FROM chore c WHERE c.id = chore_id);
END;
$$
LANGUAGE 'plpgsql' IMMUTABLE;


-- Zwraca maile użytkowników danego mieszkania
CREATE OR REPLACE FUNCTION get_flat_users(_flat_id integer)
    RETURNS TABLE (
        mail VARCHAR(50)
        ) AS
$$
BEGIN
    RETURN QUERY (SELECT user_mail FROM flat_user fu WHERE fu.flat_id = _flat_id);
END;
$$
LANGUAGE 'plpgsql' IMMUTABLE;


-- Zwraca aktualna date
CREATE OR REPLACE FUNCTION get_current_date()
    RETURNS DOUBLE PRECISION
    AS
$$
BEGIN
    RETURN EXTRACT(EPOCH FROM CURRENT_TIMESTAMP);
END;
$$
LANGUAGE 'plpgsql' IMMUTABLE;


-- Planuje dany obowiązek na daną datę i użytkownika
CREATE OR REPLACE FUNCTION schedule_chore(_chore_id integer, _date integer, _user_mail VARCHAR(50))
RETURNS BOOLEAN
AS
$$
BEGIN
    -- Upewnij się, że planowa data nie jest wcześniejsza niż dzisiejsza
    IF (_date < get_current_date()) THEN
	    RETURN FALSE;
    END IF;
    
    INSERT INTO chores_plan (date, chore_id, assigned_mail, done) 
        VALUES(_date, _chore_id, _user_mail, FALSE);
    
	RETURN TRUE;
END;
$$
LANGUAGE 'plpgsql';


-- Planuje dany obowiązek dla całego mieszkania w zadanym przedziale czasu
CREATE OR REPLACE FUNCTION schedule_chore_from_to(_chore_id integer, _from integer, _to integer)
RETURNS BOOLEAN
AS
$$      
DECLARE 
    users VARCHAR(50)[];
    userr VARCHAR(50);
    _current_date integer = _from;
BEGIN
    -- Upewnij się, że 'od' jest mniejsze niż 'do'
    IF (_from < get_current_date() AND _from > _to) THEN
	    RETURN FALSE;
    END IF;
  
    -- losujemy kolejkę do zadania  
    users := array(SELECT get_flat_users(get_flat_id_for_chore(_chore_id)) 
            ORDER BY RANDOM()
    ); 
    
    FOREACH userr IN ARRAY users LOOP
        RAISE NOTICE 'Calling for user: (%)', userr;

        INSERT INTO chores_plan (date, chore_id, assigned_mail, done) 
            VALUES(_current_date, _chore_id, userr, FALSE);
        
        _current_date := _current_date + 100;

    END LOOP;
      

	RETURN TRUE;
END;
$$
LANGUAGE 'plpgsql';





