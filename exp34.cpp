/*
Write C++ program to 
- left rotate an array
- right rotate an array
*/
#include<iostream>
#include<cmath>
using namespace std;

int left_rotate(int array[], int len) {
    int start = array[0];
    for (int i=0; i < len; i++) {
        if (i == len - 1) {
            array[i] = start;
        }
        else {
            array[i] = array[i + 1];
        }
    }
    return len;
}

int right_rotate(int array[], int len) {
    int final = array[len - 1];
    // array[0] = final;
    
    for (int i=len - 1; i >= 0; i--) {
        if (i == 0) {
            array[i] = final;
        }
        else {
            array[i] = array[i - 1];
        }
    }
    return len;
}

// int* left_rotate_1(int array[], int len) {
//     int left_array[len];
//     int start = array[0];
//     for (int i=0; i < len; i++) {
//         if (i == len - 1) {
//             left_array[i] = start;
//         }
//         else {
//             left_array[i] = array[i + 1];
//         }
//     }
//     return left_array;
// }

// void print_array(int array[], int len) {
//     for (int i=0; i < len; i++) {
//         cout << array[i] << " ";
//     }
//     cout << "\n";
// }


void do_left_rotate(int iter) {
    int array[] = {1, 2, 3, 4, 5};
    int len = sizeof(array) / sizeof(int);
    int left_array[len] = {};
    
    cout << "Array: ";
    for (int i=0; i < len; i++) {
        cout << array[i] << " ";
    }
    cout << "\n";

    for (int l=0; l < iter; l++) {
        // cout << l + 1 << " left rotate: ";
        len = left_rotate(array, len);
        // print_array(left_array, len);
        cout << l + 1 << " left rotate: ";
        for (int i=0; i < len; i++) {
            cout << array[i] << " ";
        }
        cout << "\n";
    }
}

void do_right_rotate(int iter) {
    int array_1[] = {1, 2, 3, 4, 5};
    int len = sizeof(array_1) / sizeof(int);
    // int iter;
    // cout << "iter: ";
    // cin >> iter;
    
    cout << "Array_1: ";
    for (int i=0; i < len; i++) {
        cout << array_1[i] << " ";
    }
    cout << "\n";

    for (int l=0; l < iter; l++) {
        // cout << l + 1 << " left rotate: ";
        len = right_rotate(array_1, len);
        // print_array(left_array, len);
        cout << l + 1 << " right rotate: ";
        for (int i=0; i < len; i++) {
            cout << array_1[i] << " ";
        }
        cout << "\n";
    }
}

int main() {
    int iter;
    cout << "iter: ";
    cin >> iter;
    
    do_left_rotate(iter);
    do_right_rotate(iter);
    return 0;
}