/*
Write C++ program to sort an array in ascending order
*/
#include<iostream>
#include<cmath>
using namespace std;

int recursive_find_min(int array[], int index, int len) {
    static int min = array[(len - 1)];
    if (index >= len) {
        return min;
    }
    else {
        if (array[index] < min) {
            min = array[index];
            return recursive_find_min(array, index + 1, len);
        }
        else {
            return recursive_find_min(array, index + 1, len);
        }
    }
} 

// int main() {
//     int array[7] = {12, 31, 22, 3, 45, 16, 17};
//     int len = sizeof(array) / sizeof(int);
//     int array_1[7] = {};
//     int sorted_array[] = {};
    
//     for (int i=0; i < len; i++) {
//         array_1[i] = array[i];
//     }   

//     cout << "Array: " ;
//     for (int i=0; i < len; i++) {
//         cout << array_1[i] << " ";
//     }
//     cout << "\n";

//     // int min = find_min(array, 0, len);

//     int c = 0;
//     for (int i=0; i < len; i++) {
//         cout << "Array_1: " ;
//         for (int z=0; z < (sizeof(array_1) / sizeof(int)); z++) {
//             cout << array_1[z] << " ";
//         }
//         cout << "\n";
//         int min = find_min(array_1, 0, (sizeof(array_1) / sizeof(int)));
//         cout << "min: " <<  min << "\n";
//         sorted_array[c] = min;
//         c += 1;
//         int c1 = 0;
//         int array_1[len - 1] = {};
//         for (int j=0; j < len; j++) {
//             // cout << "len: " << j << "\n";
//             if (array[j] != min) {
//                 // cout << "!= min: " << array[j] << "\n";
//                 array_1[c1] = array[j];
//                 // cout << "array_1: " << array_1[c1] << "\n";               
//                 c1 += 1; 
//             }
//         }
//     }

//     cout << "Sort array: ";
//     for (int i=0; i < (sizeof(sorted_array) / sizeof(int)); i++) {
//         cout << sorted_array[i] << " ";
//     }
//     cout << "\n";
// }

int normal_find_min(int array[], int len) {
    int min = array[len - 1];
    for (int i=0; i < len; i++) {
        if (array[i] < min) {
            min = array[i];
        }
    }
    return min;
}

int delete_element(int array[], int n, int min) {
    int i;
    for (i=0; i < n; i++) {
        if (array[i] == min) {
            break;
        }
    }

    if (i < n) {
        for (int j=i; j < n; j++) {
            array[j] = array[j + 1];
        }
    }
    return n;
    
}


int main() {
    int array[7] = {12, 31, 22, 3, 45, 16, 17};
    int len = sizeof(array) / sizeof(int);
    int array_1[7] = {};
    int sorted_array[] = {};
    
    cout << "Array:\t";
    for (int z=0; z < (sizeof(array) / sizeof(int)); z++) {
        cout << array[z] << " ";
    }
    cout << "\n";

    cout << "NEW Ascending order Array:\n";
    for (int i=0; i < len; i++) {
        // cout << "NEW Array: ";
        // for (int z=0; z < (sizeof(array) / sizeof(int)); z++) {
        //     cout << array[z] << " ";
        // }
        // cout << "\n";
        // int min = find_min(array, 0, sizeof(array)/sizeof(int));
        int min = normal_find_min(array, sizeof(array)/sizeof(int));
        len = delete_element(array, len, min);
        cout << min << " ";
    }
    cout << "\n";
}