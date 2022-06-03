/*
Tính giai thừa cách của số nguyên dương n
Viết hàm đệ quy tính giai thừa cách của số nguyên dương n. 
Hàm main sử dụng hàm này và có thể chạy nhiều lần để tính cho nhiều số n khác nhau nhập từ bàn phím. 
Yêu cầu kiểm tra dữ liệu nhập vào phải là số nguyên dương. 
Công thức tính giai thừa cách của n: n!=1.3...n nếu n lẻ và n!=2.4...n nếu n chẵn.
*/

#include<iostream>
#include<cmath>
using namespace std;

int cal_factorial(int n) {
    if (n % 2 == 1 && n > 1) {
        return n * cal_factorial(n - 2);
    }
    else if (n % 2 == 0 && n > 1) {
        if (n == 2) {
            return 2;
        }
        else {
            return n * cal_factorial(n - 2);
        }
    }
    else {
        return 1;
    }
}

int main() {
    int x, f;
    cout << "x =\t";
    cin >> x;

    f = cal_factorial(x);
    cout << x << "! = " << f << "\n";
    return 0;
}