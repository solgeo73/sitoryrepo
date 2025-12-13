CREATE TABLE students (
  student_id INT PRIMARY KEY,
  full_name VARCHAR(30) NOT NULL,
  group_number VARCHAR(10) NOT NULL
);

CREATE TABLE subjects(
  subject_id INT PRIMARY KEY,
  subject_name VARCHAR(30) UNIQUE
);

CREATE TABLE grades(
  grade_id INT PRIMARY KEY,
  student_id INT,
  FOREIGN KEY (student_id) REFERENCES students(student_id),
  subject_id INT,
  FOREIGN KEY (subject_id) REFERENCES subjects(subject_id),
  grade INT
);

CREATE TABLE attendance(
  attendance_id INT PRIMARY KEY,
  student_id INT,
  FOREIGN KEY (student_id) REFERENCES students(student_id),
  date_attended DATE,
  status BOOL
);

CREATE TABLE notes(
  note_id INT PRIMARY KEY,
  student_id INT,
  FOREIGN KEY (student_id) REFERENCES students(student_id),
  note_text TEXT
);


INSERT INTO students(student_id, full_name, group_number)
VALUES (1, 'Иван Иванов', 'ИУ1-12Б'),
(2, 'Пётр Петров', 'ИУ1-12Б'),
(3, 'Максим Кузнецов', 'ИУ1-12Б'),
(4, 'Анна Кузнецова', 'ИУ1-12Б'),
(5, 'Марина Орлова', 'ИУ1-12Б'),
(6, 'Олег Синицин', 'ИУ1-12Б');

INSERT INTO subjects(subject_id, subject_name)
VALUES (1, 'Математический анализ'),
(2, 'Аналитическая геометрия'),
(3, 'Информатика');

INSERT INTO grades(grade_id, student_id, subject_id, grade)
VALUES (1, 1, 1, 5),
(2, 1, 2, 4),
(3, 1, 3, 5),
(4, 2, 1, 3),
(5, 2, 2, 3),
(6, 2, 3, 3),
(7, 3, 1, 5),
(8, 3, 2, 5),
(9, 3, 3, 5),
(10, 4, 1, 4),
(11, 4, 2, 3),
(12, 4, 3, 5),
(13, 5, 1, 3),
(14, 5, 2, 3),
(15, 5, 3, 5),
(16, 6, 1, 5),
(17, 6, 2, 5),
(18, 6, 3, 2);

INSERT INTO attendance(attendance_id, student_id, date_attended, status)
VALUES (1, 1, '2025-12-11', TRUE),
(2, 2, '2025-12-11', FALSE),
(3, 3, '2025-12-11', TRUE),
(4, 4, '2025-12-11', TRUE),
(5, 5, '2025-12-11', TRUE),
(6, 6, '2025-12-11', FALSE),
(7, 1, '2025-12-12', TRUE),
(8, 2, '2025-12-12', TRUE),
(9, 3, '2025-12-12', FALSE),
(10, 4, '2025-12-12', FALSE),
(11, 5, '2025-12-12', TRUE),
(12, 6, '2025-12-12', FALSE);

INSERT INTO notes(note_id, student_id, note_text)
VALUES (1, 1, 'Замечаний нет.'),
(2, 2, 'Часто опаздывает.'),
(3, 3, 'Замечаний нет.'),
(4, 4, 'Замечаний нет.'),
(5, 5, 'Замечаний нет.'),
(6, 6, 'Давно не было.');


CREATE INDEX group_index ON students (group_number);
CREATE INDEX student_index ON grades (student_id);
CREATE INDEX note_index ON notes USING GIN(to_tsvector('russian', note_text));


CREATE VIEW student_avg_grades AS
SELECT student_id, AVG(grade) AS average_grade
FROM grades
GROUP BY student_id;


BEGIN;

INSERT INTO students(student_id, full_name, group_number)
VALUES (7, 'Андрей Соколов', 'ИУ1-12Б');

INSERT INTO grades(grade_id, student_id, subject_id, grade)
VALUES (19, 7, 1, 3),
(20, 7, 2, 3),
(21, 7, 3, 5);

COMMIT;


--Поиск одногруппников
SELECT student_id, full_name
FROM students
WHERE 1 < student_id AND student_id != 4 AND student_id < 8;

--Средний балл студента
SELECT * FROM student_avg_grades WHERE student_id = 4;

--Средний балл по информатике
SELECT * FROM (SELECT subject_id, AVG(grade) AS average_grade
FROM grades
GROUP BY subject_id)
WHERE subject_id = 3;

--Поиск по заметкам
SELECT student_id, note_text
FROM notes 
WHERE note_text LIKE '%опаздывает%'

--Обновление посещаемости
BEGIN;

UPDATE attendance 
SET status = TRUE 
WHERE student_id = 4 AND date_attended = '2025-12-12';

COMMIT;
