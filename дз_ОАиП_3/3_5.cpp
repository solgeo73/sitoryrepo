#include <iostream>
#include <cfloat>
using namespace std;

int main() {
    double a[10];
    double mn = DBL_MAX;
    double mx = DBL_MIN;
    int mn_i;
    int mx_i;
    for (int k=0; k < 10; k++) {
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
    if (mn_i == 4 && mx_i == 9) {
        cout << (mn + mx) / 2 << endl;
    }
    return 0;
}
