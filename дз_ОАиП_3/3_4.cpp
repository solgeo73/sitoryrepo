#include <iostream>
#include <cfloat>
using namespace std;

int main() {
    double a[15];
    double mn = DBL_MAX;
    double mx = DBL_MIN;
    int mn_i;
    int mx_i;
    for (int k=0; k < 15; k++) {
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
    if (mn_i - mx_i == 1) {
        cout << mn * mx << endl;
    }
    return 0;
}
