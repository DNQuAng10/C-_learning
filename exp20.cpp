/*
Write C++ program to 
- swap two numbers using pointers
*/
#include<iostream>
using namespace std;

void swap(int *num1, int *num2) {
    int temp;
    temp = *num1;

    *num1 = *num2;

    *num2 = temp;
}

int main() {
    int num1, num2;
    cout << "num1: ";
    cin >> num1;
    cout << "num2: ";
    cin >> num2;

    swap(&num1, &num2);
    cout << "new first num1: " << num1 << "\n";
    cout << "new second num2: " << num2 << "\n";
}
