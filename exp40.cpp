/*
Write C++ Program to 
Find sum of each row and columns of a matrix
*/
#include<iostream>
#include<cmath>
using namespace std;

int main() {
    int a[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {2, 14, 2, 3}};
    int ra = sizeof(a) / sizeof(a[0]);
    int ca = sizeof(a[0]) / sizeof(int);

    cout << "Array A: \n";
    for (int i=0; i < ra; i++) {
        for (int j=0; j < ca; j++) {
            cout << "\t" << a[i][j];
            if (j == ca - 1) {
                cout << "\n\n";
            }
        }
    }

    int sum_r = 0;
    for (int i=0; i < ra; i++) {
        for (int j=0; j < ca; j++) {
            sum_r += a[i][j];
        }
        cout << "Sum row " << i << " = " << sum_r << "\n";
        sum_r = 0;
    }

    int sum_c = 0;
    for (int i=0; i < ca; i++) {
        for (int j=0; j < ra; j++) {
            sum_c += a[j][i];
        }
        cout << "Sum col " << i << " = " << sum_c << "\n";
        sum_c = 0;
    }
}