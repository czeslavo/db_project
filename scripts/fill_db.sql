SET SCHEMA 'flat_mate';

INSERT INTO chore_frequency VALUES('DAILY', 1, 0, 0);
INSERT INTO chore_frequency VALUES('WEEKLY', 0, 1, 0);
INSERT INTO chore_frequency VALUES('MONTHLY', 0, 0, 1);

INSERT INTO system_user VALUES('czeslavo@gmail.com', 'czeslavo', 'Grzegorz', 'Burzynski', crypt('pass', gen_salt('bf', 8)));
INSERT INTO system_user VALUES('piotr@gmail.com', 'waclaw', 'Piotr', 'Hanusiak', crypt('pass', gen_salt('bf', 8)));
INSERT INTO system_user VALUES('ania@gmail.com', 'ania', 'Ania', 'Bogusz', crypt('pass', gen_salt('bf', 8)));
INSERT INTO system_user VALUES('kasia@gmail.com', 'kasia', 'Kasia', 'Nalepka', crypt('pass', gen_salt('bf', 8)));
INSERT INTO system_user VALUES('andrzej@gmail.com', 'Andrew', 'Andrzej', 'Andrzejowski', crypt('pass', gen_salt('bf', 8)));

INSERT INTO flat (name, flat_admin_mail) VALUES('Symfoniczna 1/13', 'czeslavo@gmail.com');

INSERT INTO flat_user VALUES('czeslavo@gmail.com', 1);
INSERT INTO flat_user VALUES('piotr@gmail.com', 1);
INSERT INTO flat_user VALUES('ania@gmail.com', 1);
INSERT INTO flat_user VALUES('kasia@gmail.com', 1);

INSERT INTO note (date, content, active, author_mail, flat_id)
	VALUES(1463313600, 'To bardzo ważna notatka na lodówce', TRUE, 'czeslavo@gmail.com', 1);
INSERT INTO note (date, content, active, author_mail, flat_id)
	VALUES(1463317600, 'To bardzo ważna notatka na lodówce nr 2', TRUE, 'piotr@gmail.com', 1);
INSERT INTO note (date, content, active, author_mail, flat_id)
	VALUES(1463323600, 'Kiedy impreza?', FALSE, 'kasia@gmail.com', 1);

INSERT INTO equipment (name, owner_mail, flat_id, value) VALUES('Mikrofalowka', 'czeslavo@gmail.com', 1, 50);
INSERT INTO equipment (name, owner_mail, flat_id, value) VALUES('Mikser', 'ania@gmail.com', 1, 25);
INSERT INTO equipment (name, owner_mail, flat_id, value) VALUES('Lodowka', 'kasia@gmail.com', 1, 2500);
INSERT INTO equipment (name, owner_mail, flat_id, value) VALUES('Pralka', 'piotr@gmail.com', 1, 1250);

INSERT INTO chore (name, frequency_id, flat_id) VALUES('Lazienka', 'WEEKLY', 1);
INSERT INTO chore (name, frequency_id, flat_id) VALUES('Kuchnia', 'WEEKLY', 1);
INSERT INTO chore (name, frequency_id, flat_id) VALUES('Przedpokoj', 'WEEKLY', 1);

INSERT INTO recipe (name, description, author_mail) VALUES('kurczak z sosem', 'ugotuj kurczaka i go polej sosem', 'czeslavo@gmail.com');
INSERT INTO recipe (name, description, author_mail) VALUES('kurczak w ciescie', 'ugotuj kurczaka i go otocz ciastem', 'kasia@gmail.com');
INSERT INTO recipe (name, description, author_mail) VALUES('kurczak smazony z sosem', 'usmaz kurczaka i go polej sosem', 'piotr@gmail.com');
INSERT INTO recipe (name, description, author_mail) VALUES('makaron z sosem z kurczaka', 'ugotuj makaron z kurczakiem i go polej sosem', 'czeslavo@gmail.com');
INSERT INTO recipe (name, description, author_mail) VALUES('gulasz', 'ugotuj gulasz', 'ania@gmail.com');

INSERT INTO recipe_ingredient (name, recipe_id) VALUES('kurczak 500g', 1);
INSERT INTO recipe_ingredient (name, recipe_id) VALUES('kurczak 500g', 2);
INSERT INTO recipe_ingredient (name, recipe_id) VALUES('kurczak 500g', 3);
INSERT INTO recipe_ingredient (name, recipe_id) VALUES('cebula', 4);
INSERT INTO recipe_ingredient (name, recipe_id) VALUES('cebula', 2);
INSERT INTO recipe_ingredient (name, recipe_id) VALUES('marchewka czerwona', 2);
INSERT INTO recipe_ingredient (name, recipe_id) VALUES('marchewka pomarańczowa', 3);

INSERT INTO other_expense (user_mail, name, flat_id, date) VALUES('czeslavo@gmail.com', 'kino', 1, 1463317600);
INSERT INTO other_expense (user_mail, name, flat_id, date) VALUES('piotr@gmail.com', 'pizza', 1, 1463323600);
INSERT INTO other_expense (user_mail, name, flat_id, date) VALUES('ania@gmail.com', 'papier toaletowy', 1, 1463318600);






