/*
Write C++ program to 
check vowel or consonant using switch case
*/
#include<iostream>
using namespace std;

int main() {
    char ch;

    cout << "Enter a character: ";
    cin >> ch;

    switch (ch)
    {
    case 'a':
        /* code */
        cout << ch << " is vowel\n"; 
        break;
    case 'i':
        cout << ch << " is vowel\n"; 
        break;
    case 'u':
        cout << ch << " is vowel\n"; 
        break;
    case 'e':
        cout << ch << " is vowel\n"; 
        break;
    case 'o':
        cout << ch << " is vowel\n"; 
        break;
    case 'A':
        /* code */
        cout << ch << " is vowel\n"; 
        break;
    case 'I':
        cout << ch << " is vowel\n"; 
        break;
    case 'U':
        cout << ch << " is vowel\n"; 
        break;
    case 'E':
        cout << ch << " is vowel\n"; 
        break;
    case 'O':
        cout << ch << " is vowel\n"; 
        break; 
    default: cout << ch << " is consonant\n";
        break;
    }
}