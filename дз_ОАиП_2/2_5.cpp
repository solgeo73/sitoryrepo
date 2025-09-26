#include <iostream>
using namespace std;

int main() {
    int c;
    cin >> c;
    if (c % 15 == 0) {
        cout << "Делится на 3 и 5";
    }
    else if (c % 3 == 0) {
        cout << "Делится на 3";
    }
    else if (c % 5 == 0) {
        cout << "Делится на 5";
    }
    else {
        cout << "Не делится на 3 или 5";
    }
    return 0;
}
