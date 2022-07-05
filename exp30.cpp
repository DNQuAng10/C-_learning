/*
Write C++ program to 
count total duplicate elements in an array
*/
#include<iostream>
#include<cmath>
using namespace std;

int main() {
    int array[] = {1, 2, 4, 5, 6, 7, 2, 9, 3, 5, 6};
    int len = sizeof(array) / sizeof(int);

    cout << "Array: ";
    for (int i=0; i < len; i++) {
        cout << array[i] << " ";
    }
    cout << "\n";

    int c = 0;
    for (int i=0; i < len; i++) {
        for (int j=(i + 1); j < len; j++) {
            if (array[i] == array[j]) {
                c += 1;
                break;
            }
        }
    }

    cout << "Total number of duplicate elements found in array: " << c << "\n";
}