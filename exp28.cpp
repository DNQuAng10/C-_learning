/*
Write C++ program to 
count number of each element in an array
*/
#include<iostream>
#include<cmath>
using namespace std;

int main() {
    int array[] = {1, 2, 3, 4, 2, 55, 21, 34, 2, 4, 21};
    int len = sizeof(array) / sizeof(int);
    int loop_array[len] = {};

    
    int c1 = 0;
    int l = 0;
    for (int i=0; i < len; i++) {
        for (int z=0; z < (sizeof(loop_array) / sizeof(int)); z++) {
            if (array[i] == loop_array[z]) {
                l += 1;
            }
        }
        if (l == 0) {
            int c = 0;
            for (int j=i + 1; j < len; j++) {
                if (array[j] == array[i]) {
                    c += 1;
                }
            }
            if (c > 0) {
                cout << array[i] << " occurs: " << c + 1 << "\n";
                
            }
            else {
                cout << array[i] << " only occur 1." << "\n";
            }
        }
        else {
            l = 0;
        }
        loop_array[c1] = array[i];
        c1 += 1;
    }
}
