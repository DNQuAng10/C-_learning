/*Kiểm tra 3 số có phải cạnh tam giác không, nếu có là loại tam giác nào, tính chu vi, diện tích
Nhập 3 số thực a, b, c và kiểm tra 3 số đó có phải là 3 cạnh của 1 tam giác không? 
Nếu là 3 cạnh tam giác thì cho biết là tam giác nào trong các loại tam giác sau: đều, vuông cân, vuông, cân, thường và 
tính chu vi, diện tích của tam giác đó. In kết quả ra màn hình.
*/

#include<iostream>
#include<cmath>
using namespace std;

int main() {
    int a, b, c;
    for (int i = 0; i < 3; i++) {
        cout << "Set triangle edge " << i + 1 << ":\t";
        if (i == 0) {
            cin >> a; 
        }
        else if (i == 1) {
            cin >> b;
        }
        else {
            cin >> c;
        }

    }
    if (a < 0 || b < 0 || c < 0) {
        cout << "Not triangel => at leaste have a edge < 0\n";
    }
    else {
        if (a == 0 || b == 0 || c == 0) {
            cout << "Not triangle => at least have a edge == 0\n";
        }
        else {
            if (a == b == c) {
                cout << "=> equilateral triangle\n";
            }
            else if (a == b || c == b || a == c) {
                if (a * a + b * b - c * c == 0 || a * a + c * c - b * b == 0 || b * b + c * c - a * a == 0) {
                    cout << "=> square icosceles triangle\n";
                }
                else {
                    cout << "=> icosceles triangle\n";
                }
            }
            else if (a * a + b * b - c * c == 0 || a * a + c * c - b * b == 0 || b * b + c * c - a * a == 0) {
                cout << "=> square triangle\n";
            }
            else {
                cout << "=> this is triangle\n";
            }
        }
    }
}