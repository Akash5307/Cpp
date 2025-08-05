// optional.cpp by Bill Weinman [bw.org]
// updated 2022-08-30
#include<bits/stdc++.h>
using namespace std;

struct return_status {
    long value;
    bool have_value;
};

return_status factor(long n) {
    return_status rs {0, false};
    for(long i = 2; i <= n / 2; ++i) {
        if (n % i == 0) {
            rs.value = i;
            rs.have_value = true;
            return rs;
        }
    }
    return rs;
}

int main() {
    long a {42};
    auto x = factor(a);

    if(x.have_value) cout<<"lowest factor of "<<a<<" is "<< x.value<<"\n";
    else cout<<a<<" is prime\n";
}
