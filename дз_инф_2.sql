CREATE TABLE employees(
  e_id INT PRIMARY KEY,
  e_name VARCHAR(20) NOT NULL,
  e_position VARCHAR(15) NOT NULL,
  salary DECIMAL NOT NULL
);

CREATE TABLE projects(
  p_id INT PRIMARY KEY,
  p_name VARCHAR(30) NOT NULL,
  budget DECIMAL NOT NULL
);

CREATE TABLE employee_projects(
  e_id INT UNIQUE,
  FOREIGN KEY (e_id) REFERENCES employees(e_id),
  p_id INT,
  FOREIGN KEY (p_id) REFERENCES projects(p_id),
  role_in_project VARCHAR(15) NOT NULL
);

CREATE TABLE audit_log(
  o_id INT PRIMARY KEY,
  e_id INT,
  FOREIGN KEY (e_id) REFERENCES employees(e_id),
  operation TEXT NOT NULL
);


INSERT INTO employees(e_id, e_name, e_position, salary)
VALUES 
  (1, 'Иван Иванов', 'Разработчик', 100000),
  (2, 'Пётр Петров', 'Администратор', 200000),
  (3, 'Максим Кузнецов', 'Аналитик', 75000),
  (4, 'Марина Орлова', 'Менеджер', 150000),
  (5, 'Анна Кузнецова', 'Разработчик', 100000);

INSERT INTO projects(p_id, p_name, budget)
VALUES 
  (1, 'Проект 1', 500000);

INSERT INTO employee_projects(e_id, p_id, role_in_project)
VALUES 
  (1, 1, 'Разработчик'),
  (2, 1, 'Администратор'),
  (3, 1, 'Аналитик'),
  (4, 1, 'Менеджер');


CREATE ROLE administrator;
GRANT ALL PRIVILEGES ON DATABASE dz2 TO administrator;

CREATE ROLE manager;
GRANT SELECT ON TABLE employees, projects TO manager;
GRANT INSERT ON TABLE employee_projects TO manager;

CREATE ROLE analyst;
GRANT SELECT ON TABLE employee_projects, projects TO analyst;


--Изменение бюджета
BEGIN;

UPDATE projects
SET budget = 450000
WHERE p_name = 'Проект 1';

COMMIT;

--Добавление сотрудника
BEGIN;

INSERT INTO employee_projects(e_id, p_id, role_in_project)
VALUES (5, 1, 'Разработчик');

COMMIT;

--Удаление сотрудника
BEGIN;

DELETE FROM employee_projects 
WHERE e_id = 1 AND p_id = 1;

COMMIT;

--Создание проекта
BEGIN;

INSERT INTO projects(p_id, p_name, budget)
VALUES 
  (2, 'Проект 2', 700000);

INSERT INTO employee_projects(e_id, p_id, role_in_project)
VALUES 
  (1, 2, 'Разработчик'),
  (2, 2, 'Администратор'),
  (3, 2, 'Аналитик'),
  (4, 2, 'Менеджер'),
  (5, 2, 'Разработчик');

COMMIT;

--Удаление проекта
BEGIN;

DELETE FROM employee_projects 
WHERE p_id = 1;

DELETE FROM projects 
WHERE e_id = 1;

COMMIT;
