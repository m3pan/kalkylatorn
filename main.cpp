#include <iostream>
using namespace std;

struct Base {
    ~Base() { cout << "Base" << endl; }
};
struct Derived : public Base
{
    ~Derived() { cout << "Derived" << endl; }
};

int main()
{
    Base* bp{new Derived()};
    delete bp;
}
