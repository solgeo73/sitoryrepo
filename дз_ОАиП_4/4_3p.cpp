#include <iostream>
using namespace std;

int main() {
    int a[3][3];
    for (int k=0; k < 3; k++) {
        cin >> a[k][0] >> a[k][1];
        a[k][2] = 1;
    }
    if (a[0][0]*a[1][1]+a[1][0]*a[2][1]+a[2][0]*a[0][1]-a[1][0]*a[0][1]-a[2][0]*a[1][1]-a[0][0]*a[2][1] == 0){
        cout << "Коллинеарны";
    }
    else {
        cout << "Не коллинеарны";
    }
    return 0;
}
