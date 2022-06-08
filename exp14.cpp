/*
Write C++ program to find reverse of a number using recursion
*/

#include<iostream>
#include<cmath>
#include<math.h>
using namespace std;

/*
123 --> 
log10(123) = 2
(123/10^0)%10 * 10^2 = 300
(123/10^1)%10 * 10^1 = 20
(123/10^2)%10 * 10^0 = 1
                     = 321
*/
int normal(int x, int e) {
    int j;
    int y;
    int z;
    cout << "use normal function: ";
    for (int i=0; i <= e; i++) {
        j = (x / pow(10, i));
        // cout << "j: " << j << "\n";
        // z = (pow(10, e - i));
        // cout << "z: " << z << "\n";
        y = j % 10;
        cout << y; 
        // break;
    }
    cout << "\n";
    return 0;
}

int recursion(int num) {
    int digit = (int) log10(num);
 
    // Base condition
    if(num == 0)
        return 0;
    cout << (num%10 * pow(10, digit)) << "\n";
    return ((num%10 * pow(10, digit)) + recursion(num/10));
}

int main() {
    int x;
    cout << "x =\t";
    cin >> x;
    int e = log10(x);
    // cout << e << pow(10, 0);
    // cout << 1 % 10;
    normal(x, e);
    x = recursion(x);
    cout << "use recursion: " << x << "\n";
}
