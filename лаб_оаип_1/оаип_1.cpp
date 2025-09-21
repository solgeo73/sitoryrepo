//вариант 4
#include <iostream>
#include <climits> //для INT_MIN
using namespace std;

void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int max = INT_MIN;
    int sum = 0;
    int num[10];
    for (int i = 0; i < 10; i++) {
        cin >> num[i];
        sum += num[i];
    }
    cout << "Исходный массив: ";
    for (int i = 0; i < 10; i++) {
        cout << num[i] << " ";
        if (num[i] > max) {
            max = num[i];
        }
    }
    cout << "\nСумма элементов: " << sum << "\nМаксимальный элемент: " << max << endl;
    insertionSort(num, 10);
    cout << "Отсортированный массив: ";
    for (int i = 0; i < 10; i++) {
        cout << num[i] << " ";
        if (num[i] > max) {
            max = num[i];
        }
    }
    return 0;

}
