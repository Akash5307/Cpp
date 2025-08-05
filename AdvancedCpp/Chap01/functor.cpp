// functor.cpp by Bill Weinman [bw.org]
// updated 2022-10-21
#include<bits/stdc++.h>
using namespace std;
class MultBy {
    int mult {};
public:
    MultBy (int n = 1) : mult(n) {}
    int operator () (int n) const { return mult * n; }
};

int main() {
    const MultBy times4(4);
    const MultBy times10(10);
    const MultBy times15(15);

    cout<<"times4(5) is "<< times4(5)<<"\n";
    cout<<"times4(15) is "<<times4(15)<<"\n";
    cout<<"times10(5) is "<<times10(5)<<"\n";
    cout<<"times10(15) is "<<times10(15)<<"\n";
    cout<<"times15(5) is "<<times15(5)<<"\n";
    cout<<"times15(15) is "<<times15(15)<<"\n";
}
