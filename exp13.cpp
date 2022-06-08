/*
Write C++ program to find power of a number using recursion
*/

#include<iostream>
#include<cmath>
#include<math.h>
using namespace std;

int power(int x, int i) {
    if (i > 0) {
        return x * power(x, i - 1);
    }
    // if (i < 0) {
    //     return (1 / x) * (1 / power(x, i + 1));
    // }
    else {
        return 1;
    }
}

int main() {
    int x = 2;
    int i = 10;
    double exp;
    cout << "x =\t";
    cin >> x;
    cout << "i =\t";
    cin >> i;

    if (i >= 0) {
        exp = power(x, i);
        cout << x << "^" << i << " = " << exp << "\n";
    }
    else {
        exp = power(x, -i);
        exp = 1 / exp;
        cout << x << "^" << i << " = " << exp << "\n";
    }
}