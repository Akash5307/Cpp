#include <iostream>

class num {
    int a;
public:
    num() = delete;
    constexpr num(const int& n) : a(n) {}
    constexpr int get() const { return a; }

    // Manual comparison operators
    constexpr bool operator == (const num& rhs) const { return a == rhs.a; }
    constexpr bool operator != (const num& rhs) const { return !(a == rhs.a); }
    constexpr bool operator <  (const num& rhs) const { return a < rhs.a; }
    constexpr bool operator >  (const num& rhs) const { return rhs.a < a; }
    constexpr bool operator <= (const num& rhs) const { return !(rhs.a < a); }
    constexpr bool operator >= (const num& rhs) const { return !(a < rhs.a); }
};

int main() {
    num n {42};
    std::cout << "The num is " << n.get() << '\n';

    constexpr num na {7};
    constexpr num nb {7};
    constexpr num nc {42};

    static_assert(na < nc, "na < nc failed");
    static_assert(nc > na, "nc > na failed");
    static_assert(na == nb, "na == nb failed");
    static_assert(na <= nb, "na <= nb failed");
    static_assert(na <= nc, "na <= nc failed");
    static_assert(nc >= na, "nc >= na failed");
    static_assert(na != nc, "na != nc failed");

    std::cout << "done.\n";
}
