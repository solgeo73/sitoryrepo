#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int A[2], o;
    cin >> A[0] >> A[1] >> o;
    o *= M_PI / 180.0;
    int a[2][2];
    a[0][0] = cos(o); a[0][1] = sin(o);
    a[1][0] = -sin(o); a[1][1] = cos(o);
    cout << A[0]*a[0][0] + A[1]*a[0][1] << " " << A[0]*a[1][0] + A[1]*a[1][1];
    return 0;
}
