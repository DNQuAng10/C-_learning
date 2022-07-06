/*
Write C++ Program to Multiply Two Matrices (nxn * nxn)
*/
#include<iostream>
#include<cmath>
using namespace std;

void print_matrix(int array[3][3]) {
    for (int i=0; i < 3; i++) {
        for (int j=0; j < 3; j++) {
            cout << "\t" << array[i][j];
            if (j == 2) {
                cout << "\n\n";
            }
        }
    }
}

int* sum_matrix(int m1[3][3], int m2[3][3], int sum[3][3]) {
    for (int i=0; i < 3; i++) {
        for (int j=0; j < 3; j++) {
            sum[i][j] = m1[i][j] + m2[i][j];
        }
    }
    return 0; 
}

int mul_matrix(int m1[3][3], int m2[3][3], int mul[3][3]) {
    for (int i=0; i < 3; i++) {
        for (int j=0; j < 3; j++) {
            int x = 0;
            for (int k=0; k < 3; k++) {
                x += m1[i][k] * m2[k][j];
            }
            mul[i][j] = x;
        }
    }
    return 0;
}

int main() {
    int a[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int b[3][3] = {{0, 1, 2}, {2, 1, 2}, {3, 4, 7}};
    int sum[3][3], mul[3][3];

    cout << "Matrix A: \n";
    print_matrix(a);
    
    cout << "Matrix B: \n";
    print_matrix(b);

    sum_matrix(a, b, sum);
    cout << "A + B: \n";
    print_matrix(sum);

    mul_matrix(a, b, mul);
    cout << "A * B: \n";
    print_matrix(mul);
}