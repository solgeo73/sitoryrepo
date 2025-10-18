#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char str[100];
    char a[20];
    cin.getline(str, 100);
    char *p1 = str;
    short cb, ln, mx, pr, d;
    cb = ln = mx = pr = d = 0;
    bool f = false;
    const char *w = " ";
    strncat(str, w, 1);
    while (*p1 != '\0') {
        if (pr == 9) { if (*p1 == 'd') { d++; } }
        if (*p1 != ' ') { ln++; }
        else {if (ln > mx) { mx = ln; } ln = 0; pr++; }
        if (*p1 == ' ' && f) { cb++; }
        if (*p1 == 'b') { f = true; }
        else { f = false; }
        p1++;
    }
    cout << "1. Количество слов, оканчивающихся на букву b: " << cb << endl;
    cout << "2. Длина самого длинного слова: " << mx << endl;
    cout << "3. Количество букв d в последнем слове строки: " << d << endl;
    cout << "4. Строка из заглавных букв:\n";
    char *p2 = str;
    while (*p2 != '\0') {
        *p2 = toupper(*p2);
        cout << *p2;
        p2++;
    }
    return 0;
}
