/*
Write C++ Program to 
Find the Transpose of a given Matrix
*/
#include<iostream>
#include<cmath>
using namespace std;

#define rows 3
#define cols 3

void print_matrix(int array[rows][cols]) {
    cout << "wor";
    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {
            cout << "\t" << array[i][j];
            if (j == cols - 1) {
                cout << "\n\n";
            }
        }
    }
}


int main() {
    int a[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int b[2][4] = {{1, 2, 3, 4}, {6, 7, 8, 9}};
    int c[4][3] = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};

    int ra = sizeof(a) / sizeof(a[0]);
    int ca = sizeof(a[0]) / sizeof(int);
    int ta[ca][ra];
    cout << ra << " " << ca << "\n";

    int rb = sizeof(b) / sizeof(b[0]);
    int cb = sizeof(b[0]) / sizeof(int);
    int tb[cb][rb];

    int rc = sizeof(c) / sizeof(c[0]);
    int cc = sizeof(c[0]) / sizeof(int);
    int tc[cc][rc];

    cout << "Matrix A:\n";
    for (int i=0; i < ra; i++) {
        for (int j=0; j < ca; j++) {
            cout << "\t" << a[i][j];
            if (j == ca - 1) {
                cout << "\n\n";
            }
        }
    }

    cout << "Transpose Matrix A:\n";
    for (int i=0; i < ca; i++) {
        for (int j=0; j < ra; j++) {
            ta[i][j] = a[j][i];
            cout << "\t" << ta[i][j];
            if (j == ra - 1) {
                cout << "\n\n";
            }
        }
    }

    cout << "Matrix B:\n";
    for (int i=0; i < rb; i++) {
        for (int j=0; j < cb; j++) {
            cout << "\t" << b[i][j];
            if (j == cb - 1) {
                cout << "\n\n";
            }
        }
    }

    cout << "Transpose Matrix B:\n";
    for (int i=0; i < cb; i++) {
        for (int j=0; j < rb; j++) {
            tb[i][j] = b[j][i];
            cout << "\t" << tb[i][j];
            if (j == rb - 1) {
                cout << "\n\n";
            }
        }
    }

    cout << "Matrix C:\n";
    for (int i=0; i < rc; i++) {
        for (int j=0; j < cc; j++) {
            cout << "\t" << c[i][j];
            if (j == cc - 1) {
                cout << "\n\n";
            }
        }
    }

    cout << "Transpose Matrix C:\n";
    for (int i=0; i < cc; i++) {
        for (int j=0; j < rc; j++) {
            tc[i][j] = c[j][i];
            cout << "\t" << tc[i][j];
            if (j == rc - 1) {
                cout << "\n\n";
            }
        }
    }
    
}