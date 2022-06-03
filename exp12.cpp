/*
Write C++ program to find maximum and minimum elements in array using recursion
*/

#include<iostream>
#include<cmath>
using namespace std;

#define MAX_SIZE 10

int find_max(int array[], int index, int len) {
    int max;
    if (index >= len - 2) {
        if (array[index] > array[index + 1]) {
            return array[index];
        }
        else {
            return array[index + 1];
        }
    }
    cout << max << "\n";
    cout << index << "\n";
    

    max = find_max(array, index + 1, len);
    
    if (array[index] > max) {
        return array[index];
    }
    else {
        return max;
    }
    // cout << max << "\n";
    // cout << index << "\n";
    

} 

int main() {
    int array[] = {10, 20 , 40, 55, 27, 77, 12, 35, 46, 89 };
    int len;

    len = sizeof(array) / sizeof(int);
    cout << "Array = [ ";
    for (int i = 0; i < len; i++) {
        cout << array[i] << ", ";
    }
    cout << "]" << "\n";

    int max;
    max = find_max(array, 0, len);
    cout << "MAX = " << max << "\n";
}
