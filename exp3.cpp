#include <iostream>
using namespace std;

int main() {
    int x, y, z;
    int a, b, c; // y = a*100 + b*10 + c
    int ax, bx, cx; 
    int i = 0;
    while (i == 0) {
        cout << "x: ";
        cin >> x;
        cout << "y: ";
        cin >> y;
        if (x >= 100 && x <= 1000 && y >= 100 && y <= 1000) {
            i += 1;
        } 
        else {
            cout << "[NOTE] Type 100 <= x, y <= 1000 \n";
        }
        if (i > 0) {
            break;
        }
    } 
    
    //z = x * y;
    // 100 < x, y < 1000;
    a = y / 100;
    b = (y % 100) / 10;
    c = (y % 100) % 10;
    //cout << a << b << c;
    ax = a * x;
    bx = b * x;
    cx = c * x;
    z = a * x * 100 + b * x * 10 + c * x;
    cout << "   " << x << "\n";
    cout << "x\n";
    cout << "   " << y << "\n";
    cout << "--------\n";
    if (cx <= 1000) {
        cout << "   " << cx << "\n";
    }
    else {
        cout << "  " << cx << "\n";
    }
    if (bx <= 1000) {
        cout << "  " << bx << "\n";
    }
    else {
        cout << " " << bx << "\n";
    }
    if (ax <= 1000) {
        cout << " " << ax << "\n";
    }
    else {
        cout << "" << ax << "\n";
    }
    cout << "--------\n";
    cout << z << "\n";
    //cout << "z: " << z;
    return 0 ;
}