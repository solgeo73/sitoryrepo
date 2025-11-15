#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Dish {
    string name, type;
    int price;
};

vector<string> types = { "Закуски", "Основные блюда", "Десерты", "Напитки", "Для детей" };

void saveToOutput(const string& msg) {
    ofstream f("output.txt", ios::app);
    f << msg << endl;
    cout << msg << endl;
}

vector<Dish> readDishes() {
    vector<Dish> dishes;
    ifstream f("menu.txt");
    string line;
    while (getline(f, line)) {
        size_t p1 = line.find(';'), p2 = line.find(';', p1 + 1);
        if (p1 != string::npos && p2 != string::npos) {
            dishes.push_back({ line.substr(0, p1),
                            line.substr(p1 + 1, p2 - p1 - 1),
                            stoi(line.substr(p2 + 1)) });
        }
    }
    return dishes;
}

void writeDishes(const vector<Dish>& dishes) {
    ofstream f("menu.txt");
    for (const auto& d : dishes)
        f << d.name << ";" << d.type << ";" << d.price << endl;
}


void addDish() {
    string name;
    cout << "Название блюда: ";
    getline(cin, name);
    if (name.empty()) return;

    cout << "Типы: 1-Закуски 2-Основные 3-Десерты 4-Напитки 5-Для детей\nВыберите: ";
    string c; getline(cin, c);
    if (c < "1" || c > "5") return;

    cout << "Цена: ";
    string p; getline(cin, p);

    ofstream f("menu.txt", ios::app);
    f << name << ";" << types[stoi(c) - 1] << ";" << p << endl;
    saveToOutput("Добавлено: " + name);
}

string poisk(string a) {
    auto dishes = readDishes();
    for (const auto& d : dishes) {
        if (d.name.find(a) != string::npos) {
            return "Найдено: " + d.name + " (" + d.type + ") - " + to_string(d.price);
        }
    }
    return "Не найдено";
}

void searchDish() {
    cout << "Поиск: ";
    string s; getline(cin, s);
    saveToOutput(poisk(s));
}

void sortDishes() {
    cout << "Сортировка (1-по типу, 2-по цене): ";
    string c; getline(cin, c);
    auto dishes = readDishes();

    if (c == "1") sort(dishes.begin(), dishes.end(),
        [](const Dish& a, const Dish& b) { return a.type < b.type; });
    else if (c == "2") sort(dishes.begin(), dishes.end(),
        [](const Dish& a, const Dish& b) { return a.price < b.price; });
    else return;

    writeDishes(dishes);
    saveToOutput("Сортировка завершена");
    for (const auto& d : readDishes()) {
        saveToOutput(d.name + " (" + d.type + ") - " + to_string(d.price));
    }
}

void filterByPrice() {
    cout << "Макс. цена: ";
    string p; getline(cin, p);
    double maxPrice = stod(p);
    for (const auto& d : readDishes()) {
        if (d.price <= maxPrice) {
            saveToOutput(d.name + " (" + d.type + ") - " + to_string(d.price));
        }
    }
}

int main() {
    ofstream clear("output.txt");
    setlocale(LC_ALL, "Russian");

    ofstream f("menu.txt");
    while (true) {
        string name;
        cout << "Название блюда (пустая строка для выхода): ";
        getline(cin, name);
        if (name.empty()) break;

        cout << "Типы: 1-Закуски 2-Основные 3-Десерты 4-Напитки 5-Для детей\nВыберите: ";
        string c; getline(cin, c);
        if (c < "1" || c > "5") continue;

        cout << "Цена: ";
        string p; getline(cin, p);

        f << name << ";" << types[stoi(c) - 1] << ";" << p << endl;
        saveToOutput("Добавлено: " + name);
    }

    while (true) {
        cout << "\n1-Поиск 2-Сортировка 3-Добавить 4-Блюда не дороже N руб. 0-Выход\nВыбор: ";
        string choice; getline(cin, choice);
        if (choice == "1") searchDish();
        else if (choice == "2") sortDishes();
        else if (choice == "3") addDish();
        else if (choice == "4") filterByPrice();
        else if (choice == "0") break;
    }
    return 0;
}
