#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n;
    int s = 0;
    cin >> n;
    for (int i = 1; i < n; i++) {
        if (i % 2 == 0 || i % 5 == 0) {
            s += i;
        }
    }
    cout << s;
    return 0;
}
