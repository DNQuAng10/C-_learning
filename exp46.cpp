/*
Write C++ program to 
find maximum 2 number using switch case
*/
#include<iostream>
using namespace std;

int main() {
    int x1;
    int x2;

    cout << "Enter x1: ";
    cin >> x1;
    cout << "Enter x2: ";
    cin >> x2;

    // Cannot use switch with boolean value
    switch (x1 < x2) {
        case 0:
            cout << x1 << " is MAX\n";
            break;
        case 1:
            cout << x2 << " is MAX\n";
            break;
        default: cout << x1 << " and " << x2 << " equal to\n";
    }
    return 0;
}