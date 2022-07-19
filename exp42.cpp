/*
Write C++ Program to 
define diagonals of a matrix 
and
interchange diagonals of a matrix
*/
#include<iostream>
using namespace std;

// void interchange_diagonal(int array[]) {

// }


int main() {
    int a[4][4] = {{1, 2, 3 ,4}, {2, 3, 4 , 5}, {3, 4, 5, 6}, {4, 5, 6, 7}};
    int ra = sizeof(a) / sizeof(a[0]);
    int ca = sizeof(a[0]) / sizeof(int);
    int lda[ra];
    int rda[ca];
    int lda_c = 0;
    int rda_c = 0;
    int ida[ra][ca];
   
    cout << "Matrix A: \n";
    for (int i=0; i < ra; i++) {
        for (int j=0; j < ca; j++) {
            if (i == j) {
                lda[lda_c] = a[i][j];
                lda_c += 1;
                ida[i][j] = a[i][ca - i - 1];
                ida[i][ca - i - 1] = a[i][j];
            }
            else if (j == ca - i - 1) {
                rda[rda_c] = a[i][j];
                rda_c += 1;
            }
            else {
                ida[i][j] = a[i][j];
            }
            cout << "\t" << a[i][j];
            if (j == ca - 1) {
                cout << "\n\n";
            }
        }
    }

    cout << "left diagonals: ";
    for (int i=0; i < ra; i++) {
        cout << lda[i] << " ";
    }
    cout << "\n";
    cout << "right diagonals: ";
    for (int i=0; i < ra; i++) {
        cout << rda[i] << " ";
    }
    cout << "\n";

    cout << "interchange diagonals Matrix A: \n";
    for (int i=0; i < ra; i++) {
        for (int j=0; j < ca; j++) {
            cout << "\t" << ida[i][j];
            if (j == ca - 1) {
                cout << "\n\n";
            }
        }
    }


    int b[3][3] = {{1, 2, 3}, {3, 4, 5}, {6, 7, 8}};
    int rb = sizeof(b) / sizeof(b[0]);
    int cb = sizeof(b[0]) / sizeof(int);
    int ldb[rb];
    int rdb[rb];
    int ldb_c = 0;
    int rdb_c = 0;
    int idb[rb][cb];

    cout << "Matrix B: \n";
    for (int i=0; i < rb; i++) {
        for (int j=0; j < cb; j++) {
            if (i == j) {
                ldb[ldb_c] = b[i][j];
                ldb_c += 1;
                idb[i][j] = b[i][cb - i - 1];
                idb[i][cb - i - 1] = b[i][j];
            }
            else if (j == rb - i - 1) {
                rdb[rdb_c] = b[i][j];
                rdb_c += 1;
                // idb[i][j] = b[i][j];
            }
            else if (i == rb / 2) {
                idb[i][j] = b[i][j];
            }
            else {
                idb[i][j] = b[i][j];
            }
            cout << "\t" << b[i][j];
            if (j == cb - 1) {
                cout << "\n\n";
            }
        }
    }
    cout << "left diagonals: ";
    for (int i=0; i < rb; i++) {
        cout << ldb[i] << " ";
    }
    cout << "\n";
    cout << "right diagonals: ";
    for (int i=0; i < rb; i++) {
        cout << rdb[i] << " ";
    }
    cout << "\n";

    cout << "interchange diagonal Matrix B: \n";
    for (int i=0; i < rb; i++) {
        for (int j=0; j < cb; j++) {
            cout << "\t" << idb[i][j];
            if (j == cb - 1) {
                cout << "\n\n";
            }
        }
    }
}