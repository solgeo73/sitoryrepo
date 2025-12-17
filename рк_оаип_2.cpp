#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>

using namespace std;

class Building {
protected:
    string name;
    int floors;
    double area;
    vector<string> owners;

public:
    Building(const string& n, int f, double a) : name(n), floors(f), area(a) {}
    virtual ~Building() {}

    virtual void display() const {
        cout << "Название: " << name << endl;
        cout << "  Этажи: " << floors << endl;
        cout << "  Площадь: " << area << " м^2" << endl;
        cout << "  Собственники: ";
        for (size_t i = 0; i < owners.size(); ++i) {
            if (i > 0) cout << ", ";
            cout << owners[i];
        }
        cout << endl;
    }

    virtual void saveToFile(ofstream& file) const {
        file << getType() << ";" << name << ";" << floors << ";" << area << ";";
        for (size_t i = 0; i < owners.size(); ++i) {
            file << owners[i];
            if (i < owners.size() - 1) file << "|";
        }
    }

    void addOwner(const string& owner) {
        owners.push_back(owner);
    }

    string getName() const { return name; }
    int getFloors() const { return floors; }
    double getArea() const { return area; }
    const vector<string>& getOwners() const { return owners; }

    void setFloors(int f) { floors = f; }
    void setArea(double a) { area = a; }

    virtual string getType() const = 0;
    virtual int getCount() const = 0;
    virtual double getAvgArea() const = 0;
};

class ResidentialBuilding : public Building {
private:
    int apartmentsCount;

public:
    ResidentialBuilding(const string& n, int f, double a, int apt)
        : Building(n, f, a), apartmentsCount(apt) {
    }

    void display() const override {
        cout << "=== ЖИЛОЕ ЗДАНИЕ ===" << endl;
        Building::display();
        cout << "  Квартир: " << apartmentsCount << endl;
        cout << "  Средняя площадь квартиры: " << getAvgArea() << " м^2" << endl;
        cout << "=====================" << endl;
    }

    void saveToFile(ofstream& file) const override {
        Building::saveToFile(file);
        file << ";" << apartmentsCount;
    }

    string getType() const override { return "Residential"; }
    int getCount() const override { return apartmentsCount; }
    double getAvgArea() const override {
        return apartmentsCount > 0 ? area / apartmentsCount : 0;
    }
};

class OfficeBuilding : public Building {
private:
    int officesCount;

public:
    OfficeBuilding(const string& n, int f, double a, int off)
        : Building(n, f, a), officesCount(off) {
    }

    void display() const override {
        cout << "=== ОФИСНОЕ ЗДАНИЕ ===" << endl;
        Building::display();
        cout << "  Офисов: " << officesCount << endl;
        cout << "  Средняя площадь офиса: " << getAvgArea() << " м^2" << endl;
        cout << "======================" << endl;
    }

    void saveToFile(ofstream& file) const override {
        Building::saveToFile(file);
        file << ";" << officesCount;
    }

    string getType() const override { return "Office"; }
    int getCount() const override { return officesCount; }
    double getAvgArea() const override {
        return officesCount > 0 ? area / officesCount : 0;
    }
};

const int MAX_BUILDINGS = 100;
vector<unique_ptr<Building>> buildings;

void loadFromFile(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return;
    }

    buildings.clear();

    string line;
    while (getline(file, line) && buildings.size() < MAX_BUILDINGS) {
        if (line.empty()) continue;

        istringstream iss(line);
        string type, name, floorsStr, areaStr, countStr;

        getline(iss, type, ';');
        getline(iss, name, ';');
        getline(iss, floorsStr, ';');
        getline(iss, areaStr, ';');
        getline(iss, countStr, ';');

        int floors = stoi(floorsStr);
        double area = stod(areaStr);
        int count = stoi(countStr);

        unique_ptr<Building> building;
        if (type == "Residential") {
            building = make_unique<ResidentialBuilding>(name, floors, area, count);
        }
        else if (type == "Office") {
            building = make_unique<OfficeBuilding>(name, floors, area, count);
        }
        else {
            continue;
        }

        string owner;
        while (getline(iss, owner, ';')) {
            if (!owner.empty()) {
                building->addOwner(owner);
            }
        }

        buildings.push_back(move(building));
    }

    file.close();
    cout << "Загружено " << buildings.size() << " зданий из файла." << endl;
}

void displayAll() {
    if (buildings.empty()) {
        cout << "Нет зданий для отображения." << endl;
        return;
    }

    cout << "\n=== ВСЕ ЗДАНИЯ ===" << endl;
    for (size_t i = 0; i < buildings.size(); i++) {
        cout << "\nЗдание #" << i + 1 << ":" << endl;
        buildings[i]->display();
    }
}

void sortByAreaAndFloors() {
    for (size_t i = 0; i < buildings.size() - 1; i++) {
        for (size_t j = 0; j < buildings.size() - i - 1; j++) {
            bool needSwap = false;

            if (buildings[j]->getArea() < buildings[j + 1]->getArea()) {
                needSwap = true;
            }
            else if (buildings[j]->getArea() == buildings[j + 1]->getArea() &&
                buildings[j]->getFloors() < buildings[j + 1]->getFloors()) {
                needSwap = true;
            }

            if (needSwap) {
                swap(buildings[j], buildings[j + 1]);
            }
        }
    }
    cout << "Здания отсортированы по площади и этажности." << endl;
}

void searchByFloors() {
    if (buildings.empty()) {
        cout << "Нет зданий для поиска." << endl;
        return;
    }

    cout << "Введите минимальную этажность: ";
    int minFloors;
    cin >> minFloors;

    cout << "\n=== ЗДАНИЯ С ЭТАЖНОСТЬЮ >= " << minFloors << " ===" << endl;
    bool found = false;

    for (size_t i = 0; i < buildings.size(); i++) {
        if (buildings[i]->getFloors() >= minFloors) {
            cout << "\nЗдание #" << i + 1 << ":" << endl;
            buildings[i]->display();
            found = true;
        }
    }

    if (!found) {
        cout << "Здания не найдены." << endl;
    }
}

void searchByOwner() {
    if (buildings.empty()) {
        cout << "Нет зданий для поиска." << endl;
        return;
    }

    cout << "Введите имя собственника: ";
    string owner;
    cin.ignore();
    getline(cin, owner);

    cout << "\n=== ЗДАНИЯ, ПРИНАДЛЕЖАЩИЕ '" << owner << "' ===" << endl;
    bool found = false;

    for (size_t i = 0; i < buildings.size(); i++) {
        const vector<string>& owners = buildings[i]->getOwners();
        for (const string& o : owners) {
            if (o == owner) {
                cout << "\nЗдание #" << i + 1 << ":" << endl;
                buildings[i]->display();
                found = true;
                break;
            }
        }
    }

    if (!found) {
        cout << "Здания не найдены." << endl;
    }
}

void addNewBuilding() {
    if (buildings.size() >= MAX_BUILDINGS) {
        cout << "Достигнут максимальный лимит зданий (" << MAX_BUILDINGS << ")." << endl;
        return;
    }

    cout << "=== ДОБАВЛЕНИЕ НОВОГО ЗДАНИЯ ===" << endl;

    string name;
    int floors, count;
    double area;

    cout << "Выберите тип (1 - Жилое, 2 - Офисное): ";
    int typeChoice;
    cin >> typeChoice;
    cin.ignore();

    cout << "Введите название: ";
    getline(cin, name);

    cout << "Введите этажность: ";
    cin >> floors;

    cout << "Введите общую площадь (м^2): ";
    cin >> area;

    cout << (typeChoice == 1 ? "Введите количество квартир: " : "Введите количество офисов: ");
    cin >> count;

    unique_ptr<Building> newBuilding;
    if (typeChoice == 1) {
        newBuilding = make_unique<ResidentialBuilding>(name, floors, area, count);
    }
    else {
        newBuilding = make_unique<OfficeBuilding>(name, floors, area, count);
    }

    cout << "Введите имена собственников через запятую: ";
    string ownersInput;
    getline(cin, ownersInput);

    istringstream oss(ownersInput);
    string owner;
    while (getline(oss, owner, ',')) {
        owner.erase(0, owner.find_first_not_of(" "));
        owner.erase(owner.find_last_not_of(" ") + 1);
        if (!owner.empty()) {
            newBuilding->addOwner(owner);
        }
    }
    

    buildings.push_back(move(newBuilding));
    cout << "Здание успешно добавлено!" << endl;
}

void editBuilding() {
    if (buildings.empty()) {
        cout << "Нет зданий для редактирования." << endl;
        return;
    }

    displayAll();
    cout << "\nВведите номер здания для редактирования (1-" << buildings.size() << "): ";
    size_t index;
    cin >> index;
    index--;

    if (index >= buildings.size()) {
        cout << "Неверный номер здания." << endl;
        return;
    }

    Building* building = buildings[index].get();

    cout << "\n=== РЕДАКТИРОВАНИЕ ЗДАНИЯ ===" << endl;
    building->display();

    cout << "\nЧто вы хотите изменить?" << endl;
    cout << "1. Этажность" << endl;
    cout << "2. Площадь" << endl;
    cout << "3. Добавить собственника" << endl;
    cout << "0. Отмена" << endl;
    cout << "Выбор: ";

    int choice;
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1: {
        cout << "Введите новую этажность: ";
        int newFloors;
        cin >> newFloors;
        building->setFloors(newFloors);
        break;
    }
    case 2: {
        cout << "Введите новую площадь: ";
        double newArea;
        cin >> newArea;
        building->setArea(newArea);
        break;
    }
    case 3: {
        cout << "Введите имя нового собственника: ";
        string newOwner;
        getline(cin, newOwner);
        building->addOwner(newOwner);
        break;
    }
    case 0:
        cout << "Редактирование отменено." << endl;
        return;
    default:
        cout << "Неверный выбор." << endl;
        return;
    }

    cout << "Изменения сохранены!" << endl;
}

void deleteBuilding() {
    if (buildings.empty()) {
        cout << "Нет зданий для удаления." << endl;
        return;
    }

    displayAll();
    cout << "\nВведите номер здания для удаления (1-" << buildings.size() << "): ";
    size_t index;
    cin >> index;
    index--;

    if (index >= buildings.size()) {
        cout << "Неверный номер здания." << endl;
        return;
    }

    buildings.erase(buildings.begin() + index);
    cout << "Здание удалено!" << endl;
}

void saveToFile(const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Ошибка: не удалось создать файл " << filename << endl;
        return;
    }

    for (const auto& building : buildings) {
        building->saveToFile(file);
        file << endl;
    }

    file.close();
    cout << "Данные сохранены в файл " << filename << " (" << buildings.size() << " зданий)" << endl;
}


void showMenu() {
    cout << "\n=== СИСТЕМА УПРАВЛЕНИЯ ЗДАНИЯМИ ===" << endl;
    cout << "1. Загрузить данные из файла" << endl;
    cout << "2. Показать все здания" << endl;
    cout << "3. Поиск по этажности" << endl;
    cout << "4. Поиск по собственникам" << endl;
    cout << "5. Сортировать по площади и этажности" << endl;
    cout << "6. Добавить новое здание" << endl;
    cout << "7. Редактировать здание" << endl;
    cout << "8. Удалить здание" << endl;
    cout << "9. Сохранить в файл" << endl;
    cout << "0. Выход" << endl;
    cout << "Выбор: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            loadFromFile("city.txt");
            break;
        case 2:
            displayAll();
            break;
        case 3:
            searchByFloors();
            break;
        case 4:
            searchByOwner();
            break;
        case 5:
            sortByAreaAndFloors();
            break;
        case 6:
            addNewBuilding();
            break;
        case 7:
            editBuilding();
            break;
        case 8:
            deleteBuilding();
            break;
        case 9:
            saveToFile("city.txt");
            break;
        case 0:
            cout << "Выход из программы..." << endl;
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    } while (choice != 0);

    return 0;
}
