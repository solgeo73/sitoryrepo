#include <iostream>
#include <pqxx/pqxx>
#include "classes.h"
#include <iomanip>
#include <limits>
#include <fstream>

using namespace std;
using namespace pqxx;

void logOperation(const string& operation) {
    ofstream logFile("log.txt", ios::app);
    if (logFile.is_open()) {
        char buffer[80];
        logFile << "[" << buffer << "] " << operation << endl;
        logFile.close();
    }
}

void addCategory() {
    string name;
    cout << "Название категории: ";
    getline(cin, name);

    if (!name.empty()) {
        Category category(name);
        if (category.save(conn)) {
            cout << "Категория добавлена." << endl;
            logOperation("Категория добавлена");
        }
    }
    else {
        cout << "Название не может быть пустым." << endl;
        logOperation("Ошибка при создании категории");
    }
}

void addDish() {
    string name;
    int categoryId;
    double price;
    int type;

    cout << "\nДоступные категории:" << endl;
    try {
        work txn(*conn);
        result res = txn.exec("SELECT * FROM categories ORDER BY id");

        cout << "ID  Название" << endl;

        for (const auto& row : res) {
            cout << setw(3) << row["id"].as<int>() << "  "
                << row["category_name"].c_str() << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    cout << "\nДобавление блюда" << endl;
    cout << "Название блюда: ";
    getline(cin, name);

    cout << "ID категории: ";
    cin >> categoryId;

    try {
        work check_txn(*conn);
        auto check = check_txn.exec("SELECT id FROM categories WHERE id = " +
            check_txn.quote(categoryId));

        if (check.empty()) {
            cerr << "Ошибка: Категория с ID " << categoryId << " не существует." << endl;
            logOperation("Ошибка при создании блюда");
            return;
        }
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        logOperation("Ошибка при создании блюда");
        return;
    }

    cout << "Цена: ";
    cin >> price;

    cout << "Тип (1 - Основное, 2 - Десерт): ";
    cin >> type;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (type == 1) {
        MainCourse dish(name, categoryId, price);
        if (dish.save(conn)) {
            cout << "Основное блюдо добавлено." << endl;
            logOperation("Основное блюдо добавлено");
        }
    }
    else if (type == 2) {
        Dessert dish(name, categoryId, price);
        if (dish.save(conn)) {
            cout << "Десерт добавлен." << endl;
            logOperation("Десерт добавлен");
        }
    }
    else {
        Dish dish(name, categoryId, price);
        if (dish.save(conn)) {
            cout << "Блюдо добавлено." << endl;
            logOperation("Блюдо добавлено");
        }
    }
}

void addOrder() {
    int dishId, quantity;

    cout << "\nДобавление заказа" << endl;
    cout << "ID блюда: ";
    cin >> dishId;

    cout << "Количество: ";
    cin >> quantity;
    cin.ignore();

    if (dishId > 0 && quantity > 0) {
        Order order(dishId, quantity);
        if (order.save(conn)) {
            cout << "Заказ добавлен." << endl;
            logOperation("Заказ добавлен");
        }
    }
    else {
        cout << "Неверные данные." << endl;
        logOperation("Ошибка при создании заказа");
    }
}

void viewAllDishes() {
    Dish::display(conn);
    logOperation("Показ всех блюд");
}

void viewAllOrders() {
    Order::display(conn);
    logOperation("Показ всех заказов");
}

void earningsByCategory() {
    try {
        work txn(*conn);
        string query = R"(
            SELECT c.category_name, SUM(o.total_price) as earnings
            FROM categories c
            JOIN dishes d ON c.id = d.categoryId
            JOIN orders o ON d.id = o.dishId
            GROUP BY c.category_name
            ORDER BY earnings DESC
        )";

        result res = txn.exec(query);

        cout << "\nВыручка по категориям:" << endl;
        for (const auto& row : res) {
            cout << "Категория: " << row["category_name"].c_str()
                << ", Выручка: " << row["earnings"].as<double>()
                << " руб." << endl;
        }
        logOperation("Показ выручки по категориям");
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        logOperation("Ошибка при показе выручки по категориям");
    }
}

void topSellingDishes() {
    try {
        work txn(*conn);
        string query = R"(
            SELECT d.name, SUM(o.quantity) as total_quantity
            FROM dishes d
            JOIN orders o ON d.id = o.dishId
            GROUP BY d.name
            ORDER BY total_quantity DESC
            LIMIT 3
        )";

        result res = txn.exec(query);

        cout << "\nТоп-3 самых продаваемых блюд:" << endl;
        int rank = 1;
        for (const auto& row : res) {
            cout << rank++ << ". " << row["name"].c_str()
                << " - продано: " << row["total_quantity"].as<int>()
                << " порций" << endl;
        }
        logOperation("Показ топ-3 блюд");
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        logOperation("Ошибка при показе топ-3 блюд");
    }
}

void averageOrderValue() {
    try {
        work txn(*conn);
        string query = "SELECT AVG(total_price) as avg_price FROM orders";

        result res = txn.exec(query);

        cout << "\nСредняя стоимость заказа:" << endl;
        if (!res.empty()) {
            cout << "Средняя стоимость: "
                << res[0]["avg_price"].as<double>()
                << " руб." << endl;
        }
        logOperation("Показ средней стоимости");
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        logOperation("Ошибка при показе средней стоимости");
    }
}

void orderCountPerDish() {
    try {
        work txn(*conn);
        string query = R"(
            SELECT d.name, COUNT(o.order_id) as order_count
            FROM dishes d
            LEFT JOIN orders o ON d.id = o.dishId
            GROUP BY d.name
            ORDER BY order_count DESC
        )";

        result res = txn.exec(query);

        cout << "\nКоличество заказов по блюдам:" << endl;
        for (const auto& row : res) {
            cout << "Блюдо: " << row["name"].c_str()
                << ", Заказов: " << row["order_count"].as<int>() << endl;
        }
        logOperation("Показ общего кол-ва заказов по блюду");
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        logOperation("Ошибка при показе общего кол-ва заказов по блюду");
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    try {
        string conninfo = "host=localhost port=5432 dbname=restaurant_db user=postgres";

        connection conn(conninfo);

        if (conn.is_open()) {
            cout << "Connected to database: " << conn.dbname() << endl;
        }
        else {
            cerr << "Failed to connect to the database." << endl;
            return 1;
        }

        conn.close();
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    while (true) {
        cout << "\n=== МЕНЮ ===" << endl;
        cout << "1. Добавить категорию" << endl;
        cout << "2. Добавить блюдо" << endl;
        cout << "3. Добавить заказ" << endl;
        cout << "4. Просмотр всех блюд" << endl;
        cout << "5. Просмотр всех заказов" << endl;
        cout << "6. Общая выручка по каждой категории" << endl;
        cout << "7. Топ-3 самых продаваемых блюда" << endl;
        cout << "8. Средняя стоимость заказа" << endl;
        cout << "9. Общее количество заказов по каждому блюду" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            addCategory();
            break;
        case 2:
            addDish();
            break;
        case 3:
            addOrder();
            break;
        case 4:
            viewAllDishes();
            break;
        case 5:
            viewAllOrders();
            break;
        case 6:
            earningsByCategory();
            break;
        case 7:
            topSellingDishes();
            break;
        case 8:
            averageOrderValue();
            break;
        case 9:
            orderCountPerDish();
            break;
        case 0:
            cout << "Завершение работы." << endl;
            break;
        default:
            cout << "Неверный выбор." << endl;
        }
    }
    return 0;
}
