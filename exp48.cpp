/*
Inheritance Class
*/
#include<iostream>
using namespace std;

/* When a base class is privately inherited by the derived class 
- public member of the base class becomes the private members of the derived class and therefore,
- the public members of the base class can only be accessed by the member functions of the derived class.
They are inaccessible to the objects of the derived class.
On the other hand, when the base class is publicly inherited by the derived class
- public members of the base class also become the public members of the derived class.
- The public members of the base class are accessible by the objects of the derived class
as well as by the members functions of the derived class. 
*/
class Person {
    int id;
    char name[100];

    public:
        void set_p() {
            cout << "ID: ";
            cin >> id;
            cout << "Name: ";
            cin.get(name, 100);
        }

        void display_p() {
            cout << endl << id << "\t" << name;
        }
};

class Student: private Person {
    char course[50];
    int fee;

    public:
        void set_s() {
            set_p();
            cout << "Enter the course name: ";
            fflush(stdin);
            cin.getline(course, 50);
            cout << "Enter the Course Fee: ";
            cin >> fee;
        }

        void display_s() {
            display_p();
            cout << "\t" << course << "\t" << fee << "\n";
        }
};

int main0() {
    cout << "================> Test private inheritance 1\n"; 
    Student s;
    s.set_s();
    s.display_s();
    cout << "\n";
    return 0;
}


class Person1 {
    int id;
    char name[100];

    public:
        void set_p();
        void display_p();
};
void Person1 :: set_p() {
    cout << "ID: ";
    cin >> id;
    cout << "Name: ";
    cin.get(name, 100);
}

void Person1 :: display_p() {
    cout << endl << id << "\t" << name;
}

class Student1: private Person1 {
    char course[50];
    int fee;

    public:
        void set_s();
        void display_s();
};

void Student1 :: set_s() {
    set_p();
    cout << "Enter the course name: ";
    fflush(stdin);
    cin.getline(course, 50);
    cout << "Enter the Course Fee: ";
    cin >> fee;
}

void Student1 :: display_s() {
    display_p();
    cout << "\t" << course << "\t" << fee << "\n";
}

int main1() {
    cout << "================> Test private inheritance 2\n"; 
    Student s;
    s.set_s();
    s.display_s();
    cout << "\n";
    return 0;
}

int main() {
    main0();
    main1();
}