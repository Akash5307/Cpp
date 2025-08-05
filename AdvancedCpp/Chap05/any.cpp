// any.cpp by Bill Weinman [bw.org]
// updated 2022-10-28
#include<bits/stdc++.h>
using namespace std;

void print_any(const std::any& o) {
    if (!o.has_value()) cout<<"None\n";
    else if (o.type() == typeid(int)) {
        auto x = std::any_cast<int>(o);
        cout<<"int "<< x<<"\n";
    }
    else if (o.type() == typeid(std::string)) {
        auto x = std::any_cast<const std::string&>(o);
        cout<<"string "<< x<<"\n";
    }
    else if (o.type() == typeid(std::vector<int>)) {
        auto v = std::any_cast<const std::vector<int>&>(o);
        cout<<"vector of int, "<<v.size()<<"elements: ";
        for (const auto& e : v)cout<<e<<" ";
        cout<<"\n";
    }
    else cout<<"I don't handle this type (compiler type string: "<< o.type().name()<<")\n";
}

int main() {
    print_any(47);
    print_any(std::string{"47"});
    print_any(std::vector{1, 2, 3, 4, 5});
    print_any(std::vector{1.0, 2.0, 3.0, 4.0, 5.0});
}
