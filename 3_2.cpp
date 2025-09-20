#include <iostream>
#include <climits>
using namespace std;

int main() {
    int n;
    cin >> n;
    int a[n];
    int c = 0;
    int m = INT_MIN;
    for (int k=0; k < n; k++) {
        cin >> a[k];
        if (a[k] % 2 == 0) {
            c++;
        }
        else if (a[k] > m) {
            m = a[k];
        }
    }
    cout << m << endl << c << endl;
    return 0;
}
