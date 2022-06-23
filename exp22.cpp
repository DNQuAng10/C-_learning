/*
Write C++ program to Sum of Array Elements using Pointers
*/

#include<iostream>
#include<cmath>
using namespace std;

int main() {
    int array[5], i, sum = 0;
    int *ptr;

    cout << "Enter any 5 number: ";
    for (int i=0; i < 5; i++) {
        cin >> array[i];
    }

    ptr = array;
    for (i=0; i < 5; i++) {
        sum = sum + *(ptr + i);
    }
    cout << "sum of array elements: " << sum << "\n";
}