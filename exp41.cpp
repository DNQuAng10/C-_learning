/*
Write C++ Program to 
Find the Frequency of Odd & Even Numbers in the given Matrix
if a number occured, frequence will not increase
*/
#include<iostream>
#include<cmath>
using namespace std;

int count_odd_even(int a[3][4], int ra, int ca, int loop_array[]) {
    int odd_array[ra*ca];
    int even_array[ra*ca];

    // cout << "Loop array: ";
    // for (int i=0; i < ra*ca; i++) {
    //     cout << loop_array[i] << " ";
    // }
    // cout << "\n";

    cout << "Array: ";
    int odd = 0;
    int even = 0;
    int c = 0;
    int ck_l = 0;
    for (int i=0; i < ra; i++) {
        for (int j=0; j < ca; j++) {
            for (int ck=0; ck < ra * ca; ck ++) {
                if (a[i][j] == loop_array[ck]) {
                    if (a[i][j] != 0) {
                        ck_l += 1;
                    }
                }
            }
            // cout << "a0: " << a[i][j] << " ck_l: " << ck_l << "\n"; 
            if (ck_l == 0) {
                if (a[i][j] % 2 == 0) {
                    // cout << " a2: " << a[i][j];
                    even_array[even] = a[i][j];
                    even += 1;
                }
                else if (a[i][j] % 2 == 1) {
                    // cout << " a1: " << a[i][j];
                    odd_array[odd] = a[i][j];
                    odd += 1;
                }
            }
            else {
                ck_l = 0;
            }
            loop_array[c] = a[i][j];
            c += 1;
            // print array 
            cout << "\t" << a[i][j];
            if (j == ca - 1) {
                cout << "\n\n";
            }
        }
    }
    
    cout << "Number of odd elements in matrix: " << odd << " - { ";
    for (int i=0; i < odd; i++) {
        cout << odd_array[i] << ", ";
    }
    cout << " }\n";
    cout << "Number of even elements in matrix: " << even << " - { ";
    for (int i=0; i < even; i++) {
        cout << even_array[i] << ", ";
    }
    cout << " }\n";
    cout << "=========================\n";
    // for (int i=0; i < ra*ca; i++) {
    //     cout << loop_array[i] << " ";
    // }
    // cout << "\n";
    return 0;
}

int main() {
    int a1[3][4] = {{0, 2, 7, 8}, {1, 2, 4, 6}, {3, 9, 12, 15}};
    int b[3][4] = {{1, 2, 5, 6}, {1, 2, 5, 5}, {2, 5, 7, 8}};
    int ra = sizeof(a1) / sizeof(a1[0]);
    int ca = sizeof(a1[0]) / sizeof(int);

    int loop_array[ra*ca];
    count_odd_even(a1, ra, ca, loop_array);   
    int loop_array_1[ra*ca];
    count_odd_even(b, ra, ca, loop_array_1);
    return 0;

}