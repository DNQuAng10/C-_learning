/*
Write C++ program to print all unique element in an array
*/
#include<iostream>
using namespace std;

int main() {
    int array[] = {1, 3, 5, 2, 1, 2, 6, 7, 9, 1, 3};
    int c = 0;
    int c1 = 0;
    int looped = 0;

    int len = sizeof(array) / sizeof(int);
    int loop_array[len] = {};
    

    cout << "List of unique element in array: ";
    for (int i=0; i < len; i++) {
        int len_loop = sizeof(loop_array) / sizeof(int);
        for (int l=0; l < len_loop; l++) {
            if (array[i] == loop_array[l]) {
                looped += 1;
            }
        }
        if (looped == 0) {
            for (int j=(i + 1); j < len; j++) {
                if (array[j] == array[i]) {
                    c += 1;
                    loop_array[c1] = array[i];
                    c1 += 1;
                    
                }
            }
            if (c == 0) {
                cout << array[i] << " "; 
            }
            else {
                c = 0;
            }
        }
        else {
            looped = 0;
        }
    }

}