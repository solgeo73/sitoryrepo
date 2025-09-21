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
        else if (a[k] > mx) {
            mx = a[k];
            mx_i = k;
        }
    }
    swap(a[0], a[mn_i]);
    swap(a[14], a[mx_i]);
    for (int k=0; k < 15; k++) {
        cout << a[k] << " ";
    }
    return 0;
}
