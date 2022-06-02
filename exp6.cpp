/*
Tính số năm cần gửi tiết kiệm
Một người cần có một số tiền T, 
tích lũy bằng cách gửi tiết kiệm số tiền ban đầu là S 
với lãi suất có kỳ hạn theo năm là P% 
theo phương thức lũy tiến (lãi của mỗi năm được cộng vào với tiền gốc). 
Hãy nhập vào các số thực T, S, P và xác định số năm cần gửi tiết kiệm.
*/

#include<iostream>
#include<cmath>
using namespace std;

int log_a_to_base_b(int a, int b) {
    return log2(a) / log2(b);
}


int main() {
    int T, S, P;
    float x, n;
    cout << "source money: \t";
    cin >> S;
    cout << "target money: \t";
    cin >> T;
    cout << "interest rate: \t";
    cin >> P;

    if (S < 0 || T < 0 || P < 0) {
        cout << "You suck, get out\n";
    }
    else {
        if (S == 0 || T == 0 || P == 0) {
            if (S == 0) {
                cout << "wait 1 thousand year, stupid bro!!!\n";
            }
            else if (P == 0) {
                cout << "give me your money, bro ^3^\n";
            }
            else {
                cout << "Go to other bank^0^\n";
            }
        } 
        else {
            if (T / S <= 1) {
                cout << "You have all the world\n";
            }
            else {
                //cout << T / S;
                cout << log10(T / S) << "\n";
                cout << log10(12) << "\n";
                cout << "After " << log_a_to_base_b(T / S, P + 1) << " year you have target money that you want, hihi^^\n";
            }
        }
    }
}