/*
Write C++ program to find reverse of an array
*/
#include<iostream>
#include<cmath>
using namespace std;

int main() {
    int array[] = {1, 27, 35, 16, 55, 14, 22};
    int len = sizeof(array) / sizeof(int);
    int re_array[len] = {};

    cout << "Array: "; 
    for (int i=0; i < len; i++) {
        cout << array[i] << " ";
    }
    cout << "\n";

    int c = 0;
    for (int i=len - 1; i >= 0; i--) {
        re_array[c] = array[i];
        c += 1;
    } 

    cout << "Reversed Array: ";
    for (int i=0; i < len; i++) {
        cout << re_array[i] << " ";
    }
    cout << "\n";


}