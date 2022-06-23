/*
Write C++ program to 
- count total number of negative elements in array
- sum of all negative elements
by normal function and recursion function
*/
#include<iostream>
#include<cmath>
using namespace std;

#define MAX_SIZE 100

// Normal function 
int normal_count_negative(int array[], int len) {
    int count = 0;
    
    for (int i=0; i < len; i++) {
        if (array[i] < 0) {
            count++; 
        }
    }
    return count;
}

int normal_sum(int array[], int len) {
    int sum = 0;

    for (int i=0; i < len; i++) {
        if (array[i] < 0) {
            sum += array[i];
        }
    }
    return sum;
}

// Recursion function 
int recursion_count_negative(int array[], int index, int len) {
    if (index >= len) {
        return 0;
    }
    else {
        if (array[index] < 0) {
            return 1 + recursion_count_negative(array, index + 1, len);
        }
        else {
            return 0 + recursion_count_negative(array, index + 1, len);
        }
    }
}

int recursion_sum(int array[], int index, int len) {
    if (index >= len) {
        return 0;
    }
    else {
        if (array[index] < 0) {
            return array[index] + recursion_sum(array, index + 1, len);
        }
        else {
            return 0 + recursion_sum(array, index + 1, len);
        }
    }
}


// __main__
int main() {
    // int array[MAX_SIZE];
    int array[] = {-1, 5, 16, -22, 37, -56, 45, 48, 37, -58};

    int len = sizeof(array) / sizeof(int);

    cout << "Array: ";
    for (int i=0; i < len; i++) {
        cout << array[i] << " ";
    }
    cout << "\n";

    cout << "[Normal] Total number of negative elements in array: " << normal_count_negative(array, len) << "\n";
    cout << "[Recursion] Total number of negative elements in array: " << recursion_count_negative(array, 0, len) << "\n";

    cout << "[Normal] sum of negative element: " << normal_sum(array, len) << "\n";
    cout << "[Recursion] sum of negative element: " << recursion_sum(array, 0, len) << "\n";
}