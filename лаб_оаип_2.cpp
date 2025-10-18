#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int main() {
    char str[100];
    vector <char> a;
    cin.getline(str, 100);
    char *p1 = str;
    short cb, ln, mx, pr, d, i, c2;
    cb = ln = mx = pr = d = i = c2 = 0;
    bool f = false;
    const char *w = " ";
    strncat(str, w, 1);
    while (*p1 != '\0') {
        if (pr == 9) { if (*p1 == 'd') { d++; } }
        if (*p1 != ' ') { ln++; }
        else {if (ln > mx) { mx = ln; } ln = 0; pr++; }
        if (ln == 2) { a.insert(a.begin(), *p1); }
        if (*p1 == ' ' && f) { cb++; }
        if (*p1 == 'b') { f = true; }
        else { f = false; }
        p1++;
    }
    ln = 0;
    while (p1 != &str[0]) {
        if (*p1 != ' ') { ln++; }
        else { ln = 0; }
        if (ln == 2) { if (*p1 == a[i]) { c2++; } i++; }
        p1--;
    }
    cout << "1. Количество слов, оканчивающихся на букву b: " << cb << endl;
    cout << "2. Длина самого длинного слова: " << mx << endl;
    cout << "3. Количество букв d в последнем слове строки: " << d << endl;
    cout << "4. Строка из заглавных букв:\n";
    p1 = &str[0];
    while (*p1 != '\0') {
        *p1 = toupper(*p1);
        cout << *p1;
        p1++;
    }
    cout << "\n5. Количество слов, у которых совпадает второй и предпоследний символ: " << c2; 
    return 0;
}
