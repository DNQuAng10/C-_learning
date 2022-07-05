/*
Write C++ program to 
put even and odd elements of array in two separate array
*/
#include<iostream>
#include<cmath>

using namespace std;

int main() {
    int array[] = {1, 21, 3, 4, 55, 6, 78, 12, 93, 91, 11, 51};
    int len = sizeof(array) / sizeof(int);

    int odd[len] = {};
    int even[len] = {};

    cout << "Array: ";
    for (int i=0; i < len; i++) {
        cout << array[i] << " ";
    }
    cout << "\n";

    int o = 0;
    int e = 0;
    for (int i=0; i < len; i++) {
        if (array[i] % 2 == 0) {
            even[e] = array[i];
            e += 1;
        }
        else if (array[i] % 2 == 1) {
            odd[o] = array[i];
            o += 1;
        }
    }

    cout << "Even: ";
    for (int i=0; i < e; i++) {
        cout << even[i] << " ";
    }
    cout << "\n";

    cout << "Odd: ";
    for (int i=0; i < o; i++) {
        cout << odd[i] << " ";
    }
    cout << "\n";
    return 0;
}