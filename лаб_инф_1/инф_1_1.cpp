//вариант 4
#include <iostream>
using namespace std;

int main() {
    double speed;
    cin >> speed;
    if (speed < 60) {
        cout << "Скорость в пределах нормы\n";
    }
    else if (60 <= speed && speed <= 80) {
        cout << "Вы приближаетесь к превышению скорости\n";
    }
    else {
        cout << "Превышение скорости!\n";
    }
    return 0;
}