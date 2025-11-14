CREATE DATABASE restaurant_menu;
CREATE TABLE categories (
 c_id INT PRIMARY KEY,
 category_name VARCHAR NOT NULL
);
CREATE TABLE dishes (
 d_id INT PRIMARY KEY,
 d_name VARCHAR NOT NULL,
 category_id INT,
 FOREIGN KEY (category_id) REFERENCES categories(c_id),
 price INT NOT NULL
);
CREATE TABLE orders (
 order_id INT PRIMARY KEY,
 dish_id INT,
 FOREIGN KEY (dish_id) REFERENCES dishes(d_id),
 order_date DATE NOT NULL,
 quantity INT,
 total_price INT NOT NULL
);
INSERT INTO categories(c_id, category_name)
VALUES ((1, 'Супы'),
(2, 'Основные блюда'),
(3, 'Закуски'),
(4, 'Десерты'));
INSERT INTO dishes(d_id, d_name, category_id, price)
VALUES ((1, 'Борщ', 1, 500),
(2, 'Солянка', 1, 450),
(3, 'Гуляш', 2, 550),
(4, 'Торт', 4, 350));
INSERT INTO orders(order_id, dish_id, order_date, quantity, total_price)
VALUES ((1, 1, 2025-11-16, 2, price * quantity),
(2, 3, 2025-11-16, 1, price * quantity),
(3, 1, 2025-11-19, 1, price * quantity));
SELECT * FROM dishes WHERE category_id = 1;
SELECT * FROM orders WHERE order_date < 2025-11-20 and order_date > 2025-11-15;
SELECT sum(total_price) FROM orders WHERE order_date = 2025-11-16;
SELECT * FROM orders WHERE max(quantity);
