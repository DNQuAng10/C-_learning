/*
Write C++ program to 
- check palindrome number using recursion
- with numbers less than number, how many number is palindrome 
*/

/* Check palindrome by find reversed of this number. 
if reversed number equal to this number, 
this number is Palindrome Number;
*/
#include<iostream>
#include<cmath>

using namespace std;

int find_reverse_number(int n) {
    int digit = log10(n);

    if (n == 0) {
        return 0;
    }
    else {
        return n % 10 * pow(10, digit) + find_reverse_number(n/10);
    }
}

int main() {
    int n, reverse_n;

    cout << "n = ";
    cin >> n;

    reverse_n = find_reverse_number(n);
    if (n == reverse_n) {
        cout << n << " is Palindrome Number.\n";
    }
    else {
        cout << "reversed of " << n << " is " << reverse_n << "\n";
        cout << n << " is not Palindrome Number\n";
    }
    // cout << reverse_n << "\n";
}