/*
Write C++ Program to 
Multiply Two Matrices (mxn * nxo = mxo)
*/
#include<iostream>
#include<cmath>
using namespace std;

#define ra 5
#define ca 3
#define rb 3
#define cb 4

void print_matrix(int array[ra][cb]) {
    for (int i=0; i < ra; i++) {
        for (int j=0; j < cb; j++) {
            cout << "\t" <<array[i][j];
            if (j == cb - 1) {
                cout << "\n\n";
            }
        }
    }
}

int mul_matrix(int m1[ra][ca], int m2[rb][cb], int mul[ra][cb]) {
    for (int i=0; i < ra; i++) {
        for (int j=0; j < cb; j++) {
            int x = 0;
            for (int k=0; k < ca; k++) {
                x += m1[i][k] * m2[k][j];
            }
            mul[i][j] = x;
        }
    }
    return 0;
}

int main() {

    int a[ra][ca] = {{0, 1, 2}, {1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    int b[rb][cb] = {{1, 2, 3, 4}, {2, 3, 4, 5}, {3, 4, 5, 6}};
    int mul[ra][cb];

    cout << "Matrix A: \n";
    for (int i=0; i < ra; i++) {
        for (int j=0; j < ca; j++) {
            cout << "\t" << a[i][j];
            if (j == ca - 1) {
                cout << "\n\n";
            }
        }
    }

    cout << "Matrix B: \n";
    for (int i=0; i < rb; i++) {
        for (int j=0; j < cb; j++) {
            cout << "\t" << b[i][j];
            if (j == cb - 1) {
                cout << "\n\n";
            }
        }
    }

    mul_matrix(a, b, mul);
    cout <<  "A * B: \n";
    print_matrix(mul);
}