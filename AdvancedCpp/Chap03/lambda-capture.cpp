// lambda-capture.cpp by Bill Weinman [bw.org]
// updated 2022-09-09
#include<bits/stdc++.h>
using namespace std;

int main() {
    const char* greeting {"Hello, earthlings"};
    auto x = [greeting]{ return greeting; };
    cout<<x();
}
