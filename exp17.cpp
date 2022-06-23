/*
Write C++ program to
- generate nth fibonacci term using recursion
- find factorial of a number using recursion
*/

#include<iostream>
#include<cmath>

using namespace std;

int cal_fibonacci(int n) {
    if (n == 1 || n == 0) {
        return n;
    }
    else {
        return cal_fibonacci(n - 1) + cal_fibonacci(n - 2);
    }

}

int cal_factorial(int n) {
    if (n < 1) {
        return 1;
    }
    else {
        return n * cal_factorial(n - 1);
    }
}

int main() {
    int n, fib;
    int i = 0;

    cout << "Find fibonacci of n: ";
    cin >> n;

    cout << "Fibonacci of " << n << ": "; 
    while (i <= n) {
        fib = cal_fibonacci(i);
        cout << fib << " --> \t";
        i += 1;
    }
    cout << "\n";

    cout << "Factorial of " << n << " : " << cal_factorial(n) << "\n";
    return 0;
    
}