/*
Write C++ program to 
- print number of days in a month using switch case
*/
#include<iostream>
using namespace std;

int main() {
    int m;

    cout << "Enter month (1-12): ";
    cin >> m;

    switch(m) {
        case 1: 
            cout << "31 days\n";
            break;
        case 2: 
            cout << "28 or 29 days\n";
            break;
        case 3: 
            cout << "31 days\n";
            break;
        case 4:
            cout << "30 days\n";
            break;
        case 5:
            cout << "31 days\n";
            break;
        case 6:
            cout << "30 days\n";
            break;
        case 7:
            cout << "31 days\n";
            break;
        case 8:
            cout << "31 days\n";
            break;
        case 9:
            cout << "30 days\n";
            break;
        case 10:
            cout << "31 days\n";
            break;
        case 11:
            cout << "30 days\n";
            break;
        case 12:
            cout << "30 days\n";
            break;
        default: cout << "Invalid month, please enter 1-12, please, dammit...\n";
    }
}
