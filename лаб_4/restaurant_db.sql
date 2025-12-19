CREATE TABLE categories (
 c_id INT PRIMARY KEY,
 category_name VARCHAR(15) UNIQUE
);

CREATE TABLE dishes (
 d_id INT PRIMARY KEY,
 d_name VARCHAR(15) UNIQUE,
 category_id INT,
 FOREIGN KEY (category_id) REFERENCES categories(c_id),
 price DECIMAL(10, 2) NOT NULL
);

CREATE TABLE orders (
 order_id INT PRIMARY KEY,
 dish_id INT,
 FOREIGN KEY (dish_id) REFERENCES dishes(d_id),
 order_date DATE NOT NULL,
 quantity INT,
 total_price DECIMAL(10, 2) NOT NULL
);


INSERT INTO categories(c_id, category_name)
VALUES (1, 'Супы'),
(2, 'Основные блюда'),
(3, 'Закуски'),
(4, 'Десерты');

INSERT INTO dishes(d_id, d_name, category_id, price)
VALUES (1, 'Борщ', 1, 500),
(2, 'Солянка', 1, 450),
(3, 'Гуляш', 2, 550),
(4, 'Торт', 4, 350);

INSERT INTO orders(order_id, dish_id, order_date, quantity, total_price)
VALUES (1, 1, '2025-11-16', 2, 1000),
(2, 3, '2025-11-16', 1, 550),
(3, 1, '2025-11-19', 1, 500);


CREATE INDEX category_index ON categories(category_name);
CREATE INDEX order_index ON orders(order_date);
