/*
Tìm và in các số nguyên tố nhỏ hơn n
Tìm và in ra màn hình tất cả các số nguyên tố không vượt quá số n cho trước nhập từ bàn phím. 
Số nguyên tố là số chỉ có ước số là 1 và chính số đó.
*/

#include<iostream>
#include<cmath>
using namespace std;

int main() {
    int x;
    cout << "x =\t";
    cin >> x;
    // int list[x] = {0};

    int c = 0;
    int count = 0;
    cout << "list_prime_number: [\n";
    for (int i = 2; i < x; i++) {
        // cout << i << "\n";
        for (int j = 2; j < i; j++) {
            // cout << "j: " << j << "\n";
            if (i % j == 0) {
                // cout << i << j << "\n";
                c += 1;
                break;
            }
        }
        // cout << c << "\n";
        if (c == 0) {
            // cout << i << " is prime number\n";
            // list[count] = i;
            // count += 1;
            cout << i << ", ";
        }
        else {
            c = 0;
        }
    }
    // for (int i = 0; i < sizeof(list) / sizeof(int); i++) {
    //     cout << i << ", "; 
    // }
    cout << "]\n";
}