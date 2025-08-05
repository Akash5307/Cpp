#include <bits/stdc++.h>
using namespace std;

template<typename T>
requires std::is_arithmetic_v<T>
T arg42(const T& arg) {
    return arg + 42;
}

int main() {
    auto n = 7.9;
    cout << "The answer is " << arg42(n);
}

//g++ -std=c++20 Chap04/constraints.cpp
