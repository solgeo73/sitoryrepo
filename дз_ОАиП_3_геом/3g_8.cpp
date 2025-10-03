#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double a[2][2];
    for (int k=0; k < 2; k++) {
        cin >> a[k][0] >> a[k][1];
    }
    cout << sqrt(pow(a[1][0]-a[0][0], 2) + pow(a[1][1]-a[0][1], 2));
    return 0;
}
