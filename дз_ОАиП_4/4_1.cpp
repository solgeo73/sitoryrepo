#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int a[n][n];
    for (int k=0; k < n; k++) {
        for (int q=0; q < n; q++) {
            cin >> a[k][q];
        }
    }
    for (int k=0; k < n; k++) { //главная диагональ
        for (int q=0; q < n; q++) {
            cout << a[q][k] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    for (int k=0; k < n; k++) { //вертикаль
        for (int q=0; q < n; q++) {
            cout << a[k][n-1-q] << " ";
        }
        cout << endl;
    }
    return 0;
}
