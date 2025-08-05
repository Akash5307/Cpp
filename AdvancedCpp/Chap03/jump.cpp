//  jump.cpp by Bill Weinman [bw.org]
//  as of 2022-08-29
#include<bits/stdc++.h>
using namespace std;

const char prompt(const char * p) {
    auto char_upper = [](char c) ->char {
        if(c >= 'a' && c <= 'z') return c - ('a' - 'A');
        else return c;
    };

    std::string r {};
    cout<<p<<" > ";
    getline(std::cin, r, '\n');

    if (r.size() < 1) return '\0';
    else if (r.size() > 1) {
        cout<<"Response too long\n";
        return '\0';
    }
    else return char_upper(r.at(0));
}

bool jump(const char select) {
    // alternately, this works too --
    // using jumpfunc = std::function<void()>;
    // std::function requires the <functional> header
    using jumpfunc = void(*)();

    const std::map<char, jumpfunc> jumpmap {
        { 'A', []{ cout<<"func A\n"; } },
        { 'B', []{ cout<<"func B\n"; } },
        { 'C', []{ cout<<"func C\n"; } },
        { 'D', []{ cout<<"func D\n"; } },
    };

    const auto it = jumpmap.find(select);
    if (it != jumpmap.end()) it->second();
    else {
        cout<<"Invalid response\n";
        return false;
    }
    return true;
}

int main() {
    const char* pstr {"What to do? (A/B/C/D/X)"};
    for (auto key = prompt(pstr); key != 'X'; key = prompt(pstr)) {
        if (key) jump(key);
    }
    cout<<"Bye!\n";
}
