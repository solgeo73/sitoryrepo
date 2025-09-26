#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    if (n > 0) {
        cout << "Положительное";
    }
    else if (n == 0) {
        cout << "Равно 0";
    }
    else {
        cout << "Отрицательное";
    }
    return 0;
}
