#include <iostream>
using namespace std;

int main() {
    double a[3][2];
    for (int k=0; k < 3; k++) {
        cin >> a[k][0] >> a[k][1];
    }
    cout << (a[0][0]+a[1][0]+a[2][0])/3 << " " << (a[0][1]+a[1][1]+a[2][1])/3;
    return 0;
}
