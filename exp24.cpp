/*
Write C++ program to insert an element in array
*/
#include<iostream>
#include<cmath>
using namespace std;
#define MAX_SIZE 100

int main() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int idx;
    int x = 10;

    int len = sizeof(array) / sizeof(int);
    
    cout << "Insert number to index: ";
    cin >> idx;

    
    cout << "Array: ";
    for (int i=0; i < len; i++) {
        cout << array[i] << " ";
    }

    if (idx > len || idx <= 0) {
        cout << "Invalid option! position between 1 to " << len << "\n";
    }
    else {
        for (int i=len; i >= idx; i--) {
            array[i] = array[i - 1];
        }
        array[idx - 1] = x;
        len++;
    
        cout << "New array: ";
        for (int i=0; i < len; i++) {
            cout << array[i] << " ";
        }
    }



}