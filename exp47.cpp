/*
CLASS in C++
*/
#include <iostream>
using namespace std;

class Name {
    // Access specifier
    public:

    string name_per;
    string age;

    void print_name() {
        cout << "My name is: " << name_per << "\n";
    }

    void print_age();

    void print_edu(string e) {
        edu = e;
        cout << name_per << " learned at " << edu << "\n";
    }

    private:
        string edu;

    protected:
        int paint_size; 
};

// This OUTSIDE CLASS FUNCTION 
void Name::print_age() {
    cout << name_per << " is age: " << age << "\n";
}

class Me : public Name {
    public:
        void set_paint_size(int id) {
            paint_size = id;
        }

        void print_paint_size() {
            cout << "paint_size: " << paint_size << endl;
        }
};

int main() {
    Name n;
    n.name_per = "DNQuAng";
    n.age = "18^^";

    n.print_name();
    n.print_age();
    n.print_edu("UTC");

    Me m;
    m.set_paint_size(100);
    m.print_paint_size();
    return 0;
}