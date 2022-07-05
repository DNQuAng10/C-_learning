/*
Write C++ program to 
delete all duplicate elements from an array
*/
#include<iostream>
#include<cmath>
using namespace std;

// ==============================================================
// ------Method-1-------------
int delete_element(int array[], int len, int value) {
    int i;
    for (i=0; i < len; i++) {
        if (array[i] == value) {
            break;
        }
    }
    if (i < len) {
        for (int j=i; j < len; j++) {
            if (array[j] != array[j +1]) {
                array[j] = array[j + 1];
            }
            else {
                array[j] == array[j + 2];
            }
        }
        len = len - 1;
    }
    return len;
}

int delete_element_1(int array[], int len, int index) {
    // if (index < len) {
    for (int j=index; j < len; j++) {
        if (array[j] != array[j + 1]) {
            array[j] = array[j + 1];
        }
        else {
            array[j] = array[j + 2];
        }
    }
    len = len - 1;
    // }
    return len;
}


int main_1() {
    int array[] = {1, 2, 3, 1, 4, 5, 6, 2, 4, 4, 4, 7, 8, 2, 2, 2};
    int len = sizeof(array) / sizeof(int);

    cout << "Array: ";
    for (int i=0; i < len; i++) {
        cout << array[i] << " ";
    }
    cout << "\n";

    for (int i=0; i < len; i++) {
        for (int j=i + 1; j < len; j++) {
            if (array[i] == array[j]) {
                // len = delete_element(array, len, array[j]);
                // cout << "array[j]: " << array[j] << " j: " << j << "\n";
                len = delete_element_1(array, len, j);
            }
        }
    }
    // cout << len << "\n";
    cout << "NEW Array after remove duplicate element: ";
    for (int i=0; i < len; i++) {
        cout << array[i] << " ";
    }
    cout << "\n";
    return 0;
}

// ============================================================
// -------------Method-2-----------------
int main_2() {
    int array[] = {1, 2, 3, 1, 4, 5, 6, 2, 4, 4, 4, 7, 8, 2, 2, 2};
    int len = sizeof(array) / sizeof(int);
    int i, j, k;

    cout << "Array: ";
    for (int i=0; i < len; i++) {
        cout << array[i] << " ";
    }
    cout << "\n";

    for (i=0; i < len; i++) {
        for (j=i+1; j < len; j++) {
            if (array[i] == array[j]) {
                // cout << "j before: " << j << "\n";
                for (k=j; k < len; k++) {
                    array[k] = array[k + 1];
                }
                len--;
                j--;
                // cout << "j after: " << j << "\n";
            }
        }
    }
    

    // cout << len << "\n";
    cout << "NEW Array after remove duplicate element: ";
    for (int z=0; z < len; z++) {
        cout << array[z] << " ";
    }
    cout << "\n";
    return 0;
}

int main() {
    main_1();
    main_2();
}
