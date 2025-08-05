#include <iostream>
#include "numword.h"

int main() {
    bw::numword nw{};
    uint64_t n{};

    std::cout << "n is " << nw.getnum() << ", " << nw.words() << '\n';

    nw = 3; std::cout << "n is " << nw.getnum() << ", " << nw.words() << '\n';
    nw = 47; std::cout << "n is " << nw.getnum() << ", " << nw.words() << '\n';
    nw = 73; std::cout << "n is " << nw.getnum() << ", " << nw.words() << '\n';
    nw = 1492; std::cout << "n is " << nw.getnum() << ", " << nw.words() << '\n';
    nw = 10012; std::cout << "n is " << nw.getnum() << ", " << nw.words() << '\n';

    n = 100073; std::cout << "n is " << n << ", " << bw::numword{n}.words() << '\n';
    n = 1000000; std::cout << "n is " << n << ", " << bw::numword{n}.words() << '\n';
    n = 1000000001; std::cout << "n is " << n << ", " << bw::numword{n}.words() << '\n';
    n = 123000000000; std::cout << "n is " << n << ", " << bw::numword{n}.words() << '\n';

    n = 474142398123; std::cout << "n is " << n << ", " << bw::numword{n}.words() << '\n';
    n = 1474142398007; std::cout << "n is " << n << ", " << bw::numword{n}.words() << '\n';
    n = 999000000000000; std::cout << "n is " << n << ", " << bw::numword{n}.words() << '\n';
    n = 999999999999999999; std::cout << "n is " << n << ", " << bw::numword{n}.words() << '\n';
    n = 1000000000000000000; std::cout << "n is " << n << ", " << bw::numword{n}.words() << '\n';
}
