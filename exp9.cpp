/*
Kiểm tra số chính phương
Viết 1 hàm kiểm tra 1 số có là chính phương hay không (số chính phương là số bằng bình phương của một số nguyên nào đó); 
một hàm kiểm tra 1 số có phải là số Pitago hay không (số Pitago là số chính phương và bằng tổng 2 số chính phương khác). 
Trong hàm main nhập số nguyên dương và sử dụng các hàm trên kiểm tra có là số chính phương? số Pitago?
*/

#include<iostream>
#include<cmath>
using namespace std;

int check(int x) {
    int c = 0;
    for (int i = 1; i < x; i++) {
        if (i * i == x) {
            cout << "=>\t" << x << " is perfect square number ( " << i << "^2 + " << i << "^2 = " << x << " )\n";
        }
        if (c == 0) {
            for (int j = 1; j < x; j++) {
                if (i * i + j * j == x) {
                    cout << "=>\t" << x << " is Pitago number ( " << i << "^2 + " << j << "^2 = " << x << " )\n";
                    c += 1;
                }
            }
        }
    }
    cout << "-----\n";
    return 0;
}

int main() {
    int limit;
    
    int i = 0;
    while (i == 0){
        cout << "limit =\t";
        cin >> limit;
        if (limit == 0) {
            cout << "type again, bro... x > 0\n";
        }
        else {
            i += 1;
        }
    }
    
    cout << "\n";
    for (int x = 1; x <= limit; x++) {
        check(x);
    }

    return 0;
}
