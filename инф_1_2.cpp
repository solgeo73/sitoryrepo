//вариант 4
#include <iostream>
using namespace std;

int main() {
    int cars;
    cin >> cars;
    int fact = 1;
    int c = 1;
    while (c <  cars + 1) {
        fact *= c;
        cout << fact << endl;
        c++;
    }
    return 0;
}
