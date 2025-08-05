// incr-decr.cpp by Bill Weinman [bw.org]
// as of 2022-10-21
#include<bits/stdc++.h>
using namespace std;

class num {
    int value {};
public:
    num(int x = 0) : value{x} {}
    int getvalue() const { return value; }
    void setvalue(int x) { value = x; }
    operator int () { return value; }
    num& operator++ ();
    num operator++ (int);
    num& operator-- ();
    num operator-- (int);
};


// pre-increment
num& num::operator++ () {
    cout<<"pre-increment: ";
    value += 1;
    return *this;
}

// post-increment
num num::operator++ (int) {
    cout<<"post-increment: ";
    auto temp = *this;
    value += 1;
    return temp;
}

// pre-decrement
num& num::operator-- () {
    cout<<"pre-decrement: ";
    value -= 1;
    return *this;
}

// post-decrement
num num::operator-- (int) {
    cout<<"post-decrement: ";
    auto temp = *this;
    value -= 1;
    return temp;
}

int main() {
    num n(42);
    cout<<"value is: "<< n<<"\n";
    cout<<"value is: "<< (++n)<<"\n";
    cout<<"value is: "<< n<<"\n";

    return 0;
}
