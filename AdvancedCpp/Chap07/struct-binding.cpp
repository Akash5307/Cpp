#include <iostream>
#include <tuple>
#include <vector>
#include <utility>
#include <iomanip>

struct thing {
    int alpha {};
    double bravo {};
    const char* charlie {};
};

auto newline = []{ std::cout << '\n'; };

int main() {
    thing x1 {42, 73.2, "hello, earthlings!"};
    std::tuple<int, double, const char*> x2 {42, 73.2, "hello, earthlings!"};
    std::pair<int, double> x3 {47, 112.5};

    std::cout << "struct:\n";
    const auto [a1, b1, c1] = x1;
    std::cout << "a1 " << a1 << ", b1 " << b1 << ", c1 " << c1 << '\n';
    newline();

    std::cout << "tuple:\n";
    const auto [a2, b2, c2] = x2;
    std::cout << "a2 " << a2 << ", b2 " << b2 << ", c2 " << c2 << '\n';
    newline();

    std::cout << "pair:\n";
    auto& [a3, b3] = x3;
    std::cout << "a3 " << a3 << ", b3 " << b3 << '\n';
    newline();

    std::cout << "modified pair:\n";
    a3 = 212;
    b3 = 500.9;
    auto& [a4, b4] = x3;
    std::cout << "a4 " << a4 << ", b4 " << b4 << '\n';
    newline();

    std::cout << "C-array:\n";
    const int x5[] {1, 2, 3, 4, 5};
    auto [a5, b5, c5, d5, e5] = x5;
    std::cout << "a5 " << a5 << ", b5 " << b5 << ", c5 " << c5
              << ", d5 " << d5 << ", e5 " << e5 << '\n';
    newline();

    std::cout << "C-string:\n";
    const char x6[] {"four"};
    auto [a6, b6, c6, d6, e6] = x6;
    std::cout << std::hex << std::setfill('0');
    std::cout << "a6 x" << std::setw(2) << static_cast<int>(a6)
              << ", b6 x" << std::setw(2) << static_cast<int>(b6)
              << ", c6 x" << std::setw(2) << static_cast<int>(c6)
              << ", d6 x" << std::setw(2) << static_cast<int>(d6)
              << ", e6 x" << std::setw(2) << static_cast<int>(e6) << '\n';
    newline();
}
