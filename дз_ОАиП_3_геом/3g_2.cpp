#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double a[4][2];
    for (int k=0; k < 4; k++) {
        cin >> a[k][0] >> a[k][1];
    }
    double summ = 0;
    for (int k=0; k < 3; k++) {
        summ += sqrt(pow(a[k+1][0]-a[k][0], 2) + pow(a[k+1][1]-a[k][1], 2));
    }
    cout << summ;
    return 0;
}
