#include <iostream>
#include <climits>
using namespace std;

int main() {
    int a[15];
    int mn = INT_MAX;
    int mx = INT_MIN;
    int mn_i;
    int mx_i;
    for (int k=0; k < 15; k++) {
        cin >> a[k];
        if (a[k] < mn) {
            mn = a[k];
            mn_i = k;
        }
        else if (a[k] > mx) {
            mx = a[k];
            mx_i = k;
        }
    }
    if (mn == 0 || mx == 0) {
        if (mx == 0) {
            mn_i = mx_i;
        }
        for (int k=0; k < 15; k++) {
            if (k <= mn_i) {
                cout << "0 ";
            }
            else {
                cout << a[k]<< " ";
            }
        }
    }
    return 0;
}
