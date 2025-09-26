//вариант 4
#include <iostream>
using namespace std;

int main() {
    int age;
    cin >> age;
    if (age < 18) {
        cout << "Меньше 18\n";
    }
    else if (18 <= age && age < 60) {
        cout << "От 18 до 60\n";
    }
    else {
        cout << "Больше 60\n";
    }
    return 0;
}
