/*
Write C++ Program to 
check whether two matrices are equal or not
*/
#include<iostream>
using namespace std;

void check_equal(int m1[3][3], int m2[3][3]) {
    int m3[3][3];
    int c = 0;
    for (int i=0; i < 3; i++) {
        for (int j=0; j < 3; j++) {
            m3[i][j] = m1[i][j] - m2[i][j];
            if (m3[i][j] != 0) {
                c += 1;
            }  
        }
    }
    if (c == 0) {
        cout << "2 matrix equal to\n";
    }
    else {
        cout << "2 matrix not equal to\n";
    }
}

int main() {
    int a[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int b[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int c[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 10}};

    cout << "Matrix A vs B\n";
    check_equal(a, b);
    cout << "Matrix A vs C\n";
    check_equal(a, c);
    cout << "Matrix B vs C\n";
    check_equal(b, c);
    return 0;
}