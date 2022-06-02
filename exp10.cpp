/*
Viết hàm đệ quy tìm ước chung lớn nhất và bội số chung nhỏ nhất
Viết hàm đệ quy tìm ước số chung lớn nhất của 2 số tự nhiên; 
một hàm tìm bội số chung nhỏ nhất của 2 số tự nhiên. 
Hàm main sử dụng các hàm đã viết và có thể chạy nhiều lần 
để tìm ước số chung lớn nhất và bội số chung nhỏ nhất của các cặp số nguyên dương khác nhau. 
Yêu cầu kiểm tra dữ liệu nhập vào phải là các số nguyên dương.
*/

#include<iostream>
#include<cmath>
#include<tuple>
using namespace std;

void set_input(int &x, int &y) {
    //int arr[2];
    //int x, y;
    int i = 0;
    while (i == 0) {
        cout << "x = \t";
        cin >> x;
        cout << "y = \t";
        cin >> y;
        
        if (x > 0 && y > 0) {
            i += 1;
        }
        else {
            cout << "x > 0 and y > 0. Again\n";
        }
    }
    // arr[0] = x;
    // arr[1] = y;
    // return arr[2];
}

// int find_max_divisor(int z) {
//     int max = 0;
//     int list_divisor[z];
//     for (int i = 2; i <= z; i++) {
//         if (z % i == 0) {
//             max = i;
//         }
//     }
//     cout << max << "\n";
//     return max;
// }

void find_max_divisor_common(int x, int y) {
    int max = 0;

    if (x < y) {
        for (int i = 2; i <= x; i++) {
            if (x % i == 0 && y % i == 0) {
                max = i;
            }
        }
    }
    else if (y > x) {
        for (int i = 2; i <= y; i++) {
            if (x % i == 0 && y % i == 0) {
                max = i;
            }
        }
    }
    else {
        max = y;
    }

    if (max != 0) {
        cout << "MAX divisor common of " << x << " and " << y << " = " << max << "\n";
    }
    else {
        cout << "Don't have max divisor common\n";
    }
}

void find_min_multiple_common(int x, int y) {
    int min;
    if (x < y) {
        if (y % x == 0) {
            cout << "MIN multiple of " << x << " and " << y << " = " << y << "\n";
        }
        else {
            int c = 0;
            for (int i = 1; i <= y; i++) {
                if (c == 0) {
                    for (int j = 1; j <= x; j++) {
                        //cout << "x*i = " << x * i << " y*j = " << y * j << "\n";
                        if (x * i == y * j) {
                            cout << "MIN multiple of " << x << " and " << y << " = " << x * i << " at " << i << " at " << j << "\n";
                            c += 1;
                            break;
                        }
                    }
                }
                else {
                    break;
                }
            }
        }
    }
    else if (y < x) {
        if (x % y == 0) {
            cout << "MIN multiple of " << x << " and " << y << " = " << y << "\n";
        }
        else {
            int c = 0;
            for (int i = 1; i <= x; i++) {
                if (c == 0) {
                    for (int j = 1; j <= y; j++) {
                        if (y * i == x * j) {
                            cout << "MIN multiple of " << x << " and " << y << " = " << y * i << " at " << j << " at " << i << "\n";
                            c += 1;
                            break;
                        }
                    }
                }
                else {
                    break;
                }
            }
        }
    }
    else {
        cout << "MIN multiple of " << x << " and " << y << " = " << y << "\n";
    }
}

void find_max_divisor_and_min_multiple(int x, int y) {
    find_max_divisor_common(x, y);
    find_min_multiple_common(x, y);
}

int main() {
    cout << __cplusplus << "\n";
    //int arr[2];
    int x, y;
    set_input(x, y);
    // x = arr[0];
    // y = arr[1];

    //cout << "what" << x << y;
    find_max_divisor_and_min_multiple(x, y);
}