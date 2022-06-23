/*
Write C++ program to 
- print elements of array using recursion
- find sum of array elements using recursion
*/

#include<iostream>
#include<cmath>
using namespace std;

#define MAX_SIZE 100

void print_array(int arr[], int start, int len) {
    if (start >= len) {
        return;
    }
    else {
        cout << arr[start] << "\t";
        print_array(arr, start + 1, len);
    }
}

int sum_array(int arr[], int start, int len) {
    if (start >= len) {
        return 0;
    }
    else {
        return arr[start] + sum_array(arr, start + 1, len);
    }
}

int main() {
    int arr[MAX_SIZE];
    int num;
    int x;

    cout << "size of array: ";
    cin >> num;

    cout << "Array: ";
    for (int i=0; i < num; i++) {
        cin >> arr[i];
    }

    cout << "Print array element: ";
    print_array(arr, 0, num);
    cout << "\n";

    x = sum_array(arr, 0, num);
    cout << "Sum of array: " << x << "\n";

}