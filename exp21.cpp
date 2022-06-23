/*
learn about pointer
*/
#include<iostream>
#include<string>
using namespace std;

int main() {
    string food = "Pizza";
    string *ptr = &food;

    cout << "food: " << food << "\n";

    cout << "&food: " << &food << "\n";

    cout << "*ptr: " << *ptr << "\n";

    *ptr = "Hamburger";
    cout << "change *ptr: " << *ptr << "\n";
    cout << "new &food: " << &food << "\n";
    cout << "new food: " << food << "\n";
    cout << "*ptr access to memory of food" << "\n";
}