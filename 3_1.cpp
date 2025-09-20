#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n;
    cin >> n;
    int a[n];
    int c = 0;
    for (int k=0; k < n; k++) {
        cin >> a[k];
        if (a[k] > pow(2, k)) {
            c++;
        }
    }
    cout << c << endl;
    return 0;
}
