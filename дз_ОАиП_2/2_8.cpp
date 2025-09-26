#include <iostream>
#include <cmath>
using namespace std;

int main() {
    char arr[6] {'a', 'e', 'i', 'o', 'u', 'y'};
    char s;
    int c = 0;
    do {
        cin >> s;
        if (find(arr, arr + 6, s) != -1) {
            c++;
        }
    } while (s != '\n');
    cout << c;
    return 0;
}
