#include <iostream>
using namespace std;

int main() {
    double a[3][2];
    for (int k=0; k < 3; k++) {
        cin >> a[k][0] >> a[k][1];
    }
    if ((a[1][0]-a[0][0])*(a[2][1]-a[0][1]) - (a[1][1]-a[0][1])*(a[2][0]-a[0][0]) == 0) {
        cout << "Точки лежат на одной прямой";
    }
    else {
        cout << "Точки не лежат на одной прямой";
    }
    return 0;
}
