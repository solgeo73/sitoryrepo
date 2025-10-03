#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double a[4][2];
    for (int k=0; k < 4; k++) {
        cin >> a[k][0] >> a[k][1];
    }
    bool f=0;
    for (int k=0; k < 4; k++) {
        for (int q=0; q < 4; q++) {
            if (a[k][0]!=a[q][0] && a[k][1]!=a[q][1]) {
                cout << sqrt(pow(a[q][0]-a[k][0], 2) + pow(a[q][1]-a[k][1], 2));
                f=1;
                break;
            }
        }
        if (f) {
            break;
        }
    }
    return 0;
}
