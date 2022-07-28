/*
Write C++ program to 
check even or odd number using switch case
*/
#include<iostream>
using namespace std;

int main() {
    int x;

    cout << "Enter a number: ";
    cin >> x;

    switch (x % 2) {
        case 0: 
            cout << x << " is even\n";
            break;
        case 1:
            cout << x << " is odd\n";
            break;
        default: cout << "Invalid number.\n";
    }
}