#include <iostream>
#include <cmath>
using namespace std;

int main() {
    float a, b, c;
    float x, x1, x2;
    // a*x^2 + b*x + c = 0
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;
    cout << "c: ";
    cin >> c;
    if (a == 0) {
        if (b == 0) {
            cout << "x = infinite\n";
        }
        else {
            if (c == 0) {
                cout << "x = 0\n";
            }
            else {
                x = -c / b;
                cout << "x = " << x << "\n";
            }
        }
    }
    else {
        if (b == 0) {
            if (c == 0) {
                cout << "x = 0\n";
            }
            else {
                if (-c / a > 0) {
                    cout << "x = +/-" << sqrt(-c / a) << "\n";
                }
                else {
                    cout << "x = empty\n";
                }
            }
        }
        else {
            if (c == 0) {
                cout << "x = 0 and x = " << -b / a << "\n";
            }
            else {
                if (b * b - 4 * a * c > 0) {
                    x1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
                    x2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
                    cout << "x = " << x1 << " and x = " << x2 << "\n";
                }
                else {    
                    cout << "x = empty\n";
                }
            }
        }
    }
}