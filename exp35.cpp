/*
Write C++ Program to Add Two Matrices
*/
#include<iostream>
#include<cmath>
using namespace std;

void print_matrix(int array[100][100], int r, int c) {
    for (int r1=0; r1 < r; r1++) {
        for (int c1=0; c1 < c; c1++) {
            cout << "\t" << array[r1][c1];
            if (c1 == c - 1) {
                cout << "\n\n";
            }
        }
    }
}

int main() {
    int r, c, a[100][100], b[100][100], sum[100][100], i, j;

    cout << "Number of row: ";
    cin >> r;
    cout << "Number of cols: ";
    cin >> c;

    cout << "Matrix a: ";
    for (i=0; i < r; i++) {
        for (j=0; j < c; j++) {
            cout << "Enter element a[" << i << "]" << "[" << j << "] :";
            cin >> a[i][j];
        }
    }

    cout << "Matrix b: ";
    for (i=0; i < r; i++) {
        for (j=0; j < c; j++) {
            cout << "Enter element a[" << i << "]" << "[" << j << "] :";
            cin >> b[i][j];
        }
    }

    cout << "Show Matrix A: \n";
    print_matrix(a, r, c);
    cout << "Show Matrix B: \n";
    print_matrix(b, r, c);

    for (i=0; i < r; i++) {
        for (j=0; j < c; j++) {
            sum[i][j] = a[i][j] + b[i][j];
        }
    }
    cout << "A + B: \n";
    print_matrix(sum, r, c);
    return 0;
}
