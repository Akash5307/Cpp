// vector-test.cpp by Bill Weinman [bw.org]
// version of 2022-10-26
#include<bits/stdc++.h>
using namespace std;

void disp_v(vector<string>& v, const string& label = "") {
    if (!label.empty()) cout<< label;
    if (v.empty()) cout<<"[empty]";
    else for (auto& s : v) cout<< s;
    cout<<"\n";
}

template <typename T>
void swap(T & a, T & b) {
    cout<<"::swap\n";
    T _tmp(std::move(a));
    a = std::move(b);
    b = std::move(_tmp);
}

int main() {
    vector<string> v1 = { "one", "two", "three", "four", "five" };
    vector<string> v2 = { "six", "seven", "eight", "nine", "ten" };

    disp_v(v1, "v1");
    disp_v(v2, "v2");
}
