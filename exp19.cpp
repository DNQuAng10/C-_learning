/*
Write C++ program to 
find maximum and minimum elements in array using recursion
*/

#include<iostream>
#include<cmath>

using namespace std;
#define MAX_SIZE 10

int find_max(int array[], int index, int len) {
    static int max = 0;
    if (index >= len) {
        return max;
    }
    else {
        if (array[index] > max) {
            max = array[index];
            return find_max(array, index + 1, len);
        }
        else {
            return find_max(array, index + 1, len);
        }
    }
}

int find_min(int array[], int index, int len) {
    static int min = array[0];
    if (index >= len) {
        return min;
    }
    else {
        if (array[index] < min) {
            min = array[index];
            return find_min(array, index + 1, len);
        }
        else {
            return find_min(array, index + 1, len);
        }
    }
}

int main() {
    int array[MAX_SIZE];
    int n;

    cout << "Size of n: ";
    cin >> n;

    cout << "Array: ";
    for (int i=0; i < n; i++) {
        cin >> array[i];
    }

    int max = find_max(array, 0, n);
    cout << "MAX value: " << max << "\n";

    int min = find_min(array, 0, n);
    cout << "MIN value: " << min << "\n";

}