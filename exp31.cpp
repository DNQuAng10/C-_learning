/*
Write C++ program to 
merge two sorted array
*/
#include<iostream>
#include<cmath>
using namespace std;

int find_min(int array[], int len) {
    int min = array[0];
    int min_index = 0;

    for (int i=0; i < len; i++) {
        if (array[i] < min) {
            min = array[i];
        }
    }
    return min;
}

int delete_element(int array[], int len, int index) {
    for (int i=index; index < len; i++){
        array[i] = array[i + 1];
    }
    len = len - 1;
    return len;
}

int delete_element_1(int array[], int len, int value) {
    int i = 0;
    for (i; i < len; i++) {
        if (array[i] == value) {
            break;
        }
    }

    for (int j=i; j < len; j++) {
        array[j] = array[j + 1];
    }
    // len = len - 1;
    return len;
}

int main() {
    int array_0[] = {1, 3, 8, 9, 12};
    int array_1[] = {2, 5, 18, 4, 7, 21};

    int len_0 = sizeof(array_0) / sizeof(int);
    int len_1 = sizeof(array_1) / sizeof(int);
    int len = len_0 + len_1;

    int array[len] = {};

    for (int i=0; i < (len); i++) {
        if (i < len_0) {
            array[i] = array_0[i];
        }
        else {
            array[i] = array_1[i % len_1];
        }
    }

    cout << "Merged Array: ";
    for (int i=0; i < (len); i++) {
        cout << array[i] << " ";
    }
    cout << "\n";

    cout << "Sorted Array: ";
    for (int i=0; i < (len); i++) {
        int min = find_min(array, len);
        len = delete_element_1(array, len, min);
        cout << min << " ";
    }
    cout << "\n";

}