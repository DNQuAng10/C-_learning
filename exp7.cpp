/*
Tìm và in số hoàn hảo
Tìm và in ra màn hình tất cả các số hoàn hảo không vượt quá số n cho trước nhập từ bàn phím. 
Số hoàn hảo là số bằng tổng các ước số của nó không kể ước số là chính số đó. 
Ví dụ số 6 là số hoàn hảo vì 6=1+2+3.
*/

#include<iostream>
#include<cmath>
using namespace std;

int check_perfect_number(int x) {
    int a = 0;
    int c = 0;
    for (int i = 1; i < x; i++) {
        if (x % i == 0) {
            a += i;
            //cout << a;
        }
    }
    //cout << a;
    if (x == a) {
        cout << x << " is perfect number\n";
        c += 1;
    }
    // else {
    //     cout << "Nope, normal ^^\n";
    //     c = 0;
    // }
    return c;
}

int check_input() {
    int x;
    int i = 0;
    while (i == 0) {
        cout << "x =\t";
        cin >> x;
        
        if (x == 0) {
            cout << "Hey, x > 0, again.\n";
        }
        else {
            i += 1;
        }
    }

    int c;
    check_perfect_number(x);
    return 0;
}

int perfect_number_list() {
    int x = 1000;
    int c;
    int count = 0;
    int list[x] = { 0 };
    cout << "-------------------------------\n";
    cout << "perfect number in range less than 10000 \n";

    cout << "list_perfect_number: [\n";
    for (int i = 1; i <= x; i++) {
        c = check_perfect_number(i);
        // if (c == 1) {
        //     // list[count] = i;
        //     // count += 1;
        //     cout << i << ", ";
        // }        
    }
    // cout << "array size: \t" << sizeof(list) / sizeof(int);
    // cout << "list_perfect_number: [\n";
    // for (int i = 0; i < sizeof(list) / sizeof(int); i++) {
    //     cout << i << ", ";
    // }
    cout << "]\n";
    return 0;
}

int main() {
    check_input();
    perfect_number_list();
    return 0;
}