/*
Write C++ program to find LCM(Least Common Multiple) 
and HCF(Highest Common Factor) of two numbers 
using recursion
*/

#include<iostream>
#include<cmath>
#include<math.h>
using namespace std;

int find_LCM(int x, int y) {
    static int multiple = 0;
    multiple += x;

    if (multiple % x == 0 && multiple % y == 0) {
        return multiple;
    }
    else {
        return find_LCM(x, y);
    }
}


int find_HCF(int x, int y, int max) {
    static int factor = max;
    factor -= 1;
    if (factor >= 2) {
        if (x % factor == 0 && y % factor == 0) {
            return factor;
        }
        else {
            return find_HCF(x, y, max);
        }
    }
    else {
        return 1;
    }
}

int main() {
    int x, y, max, lcm, hcf;
    cout << "x =\t";
    cin >> x;
    cout << "y =\t";
    cin >> y;

    lcm = find_LCM(x, y);
    cout << "LCM of " << x << " and " << y << " :\t" << lcm << "\n";

    if (x < y) {
        max = y;
    }
    else {
        max = x;
    }
    hcf = find_HCF(x, y, max);
    if (hcf > 1) {
        cout << "HCF of " << x << " and " << y << " :\t" << hcf << "\n";
    }
    else {
        cout << "Don't have HCF";
    }
}