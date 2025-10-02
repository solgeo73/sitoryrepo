#include <iostream>
#include <climits>
using namespace std;

int main() {
    int a[10];
    int mn = INT_MAX;
    int mx = INT_MIN;
    int mn_i;
    int mx_i;
    for (int k=0; k < 10; k++) {
        cin >> a[k];
        if (a[k] < mn) {
            mn = a[k];
            mn_i = k;
        }
        if (a[k] > mx) {
            mx = a[k];
            mx_i = k;
        }
    }
    if (mn_i == 4 && mx_i == 1) {
        cout << a[0] << " " << a[1] << " " << a[2] << " " << a[3] << " " << a[4] << " ";
        for (int k=5; k < 10; k++) {
            cout << mx << " ";
        }
    }
    return 0;
}
