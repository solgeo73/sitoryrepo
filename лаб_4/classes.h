#include <iostream>
#include <string>
#include <memory>
#include <vector>

using namespace std;

template<typename T1, typename T2>
class Pair {
private:
    T1 first;
    T2 second;

public:
    Pair(const T1& f, const T2& s) : first(f), second(s) {}

    T1 getFirst() const { return first; }
    T2 getSecond() const { return second; }

    void setFirst(const T1& f) { first = f; }
    void setSecond(const T2& s) { second = s; }

    void display() const {
        cout << first << " -> " << second << endl;
    }
};

class Category {
private:
    int id;
    string name;

public:
    Category() : id(0), name("") {}
    Category(int id, const string& name)
        : id(id), name(name) {
    }

    int getId() const { return id; }
    string getName() const { return name; }

    void setId(int newId) { id = newId; }
    void setName(const string& newName) { name = newName; }

    void display() const {
        cout << "Category ID: " << id << endl;
        cout << "Name: " << name << endl;
    }
};

class Dish {
protected:
    int id;
    string name;
    double price;
    int categoryId;

public:
    Dish() : id(0), name(""), price(0.0), categoryId(0) {}
    Dish(int id, const string& name, double price, int categoryId)
        : id(id), name(name), price(price), categoryId(categoryId) {
    }

    virtual ~Dish() {}

    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getCategoryId() const { return categoryId; }

    void setId(int newId) { id = newId; }
    void setName(const string& newName) { name = newName; }
    void setPrice(double newPrice) { price = newPrice; }
    void setCategoryId(int newCategoryId) { categoryId = newCategoryId; }

    virtual void display() const {
        cout << "Dish ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Price: " << price << " RUB" << endl;
        cout << "Category ID: " << categoryId << endl;
    }

    virtual string getType() const {
        return "Generic Dish";
    }
};

class MainCourse : public Dish {
public:
    using Dish::Dish;
    string getType() const { return "Основное блюдо"; }
};

class Dessert : public Dish {
public:
    using Dish::Dish;
    string getType() const { return "Десерт"; }
};

class Order {
private:
    int id;
    int dishId;
    int quantity;
    string orderDate;
    double totalPrice;

public:
    Order() : id(0), dishId(0), quantity(0), orderDate(""), totalPrice(0.0) {}
    Order(int id, int dishId, int quantity,
        const string& orderDate, double totalPrice)
        : id(id), dishId(dishId), quantity(quantity),
        orderDate(orderDate), totalPrice(totalPrice) {
    }

    int getId() const { return id; }
    int getDishId() const { return dishId; }
    int getQuantity() const { return quantity; }
    string getOrderDate() const { return orderDate; }
    double getTotalPrice() const { return totalPrice; }

    void setId(int newId) { id = newId; }
    void setDishId(int newDishId) { dishId = newDishId; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }
    void setOrderDate(const string& date) { orderDate = date; }
    void setTotalPrice(double price) { totalPrice = price; }

    void display() const {
        cout << "Order ID: " << id << endl;
        cout << "Dish ID: " << dishId << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Order Date: " << orderDate << endl;
        cout << "Total Price: " << totalPrice << " RUB" << endl;
    }

    void calculateTotalPrice(double dishPrice) {
        totalPrice = dishPrice * quantity;
    }
};
