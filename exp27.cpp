/*
Delete one any element in a array
*/
#include<iostream>
#include<cmath>
using namespace std;

int delete_element(int array[], int len, int delete_value) {
    int i;
    cout << "delete: " << delete_value << "\n";

    for (i=0; i < len; i++) {
        if (array[i] == delete_value) {
            break;
        }
    }

    if (i < len) {
        for (int j=i; j < len; j++) {
            array[j] = array[j+1];
        }
        len = len - 1;
    }
    return len;
}

int main() {
    int array[] = {1, 22, 3, 5, 67, 34, 66, 44};
    int delete_values[] = {3, 7, 66};
    int len = sizeof(array) / sizeof(int);

    cout << "Array: ";
    for (int i=0; i < sizeof(array)/sizeof(int); i++) {
        cout << array[i] << " ";
    }
    cout << "\n";
    // 
    for (int i=0; i < (sizeof(delete_values) / sizeof(int)); i++) {
        len = delete_element(array, len, delete_values[i]);
    }
    // cout << "len: " << len << "\n";

    cout << "Array after delete some element: ";
    for (int i=0; i < len; i++) {
        cout << array[i] << " ";
    }
    cout << "\n";

}