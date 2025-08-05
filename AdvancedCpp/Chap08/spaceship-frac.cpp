#include <iostream>
#include <iomanip>

class frac {
    long n;
    long d;
public:
    frac() = delete;
    constexpr frac(int a, int b) : n{a}, d{b} {}

    constexpr double dbl() const {
        return static_cast<double>(n) / static_cast<double>(d);
    }

    // Manual comparison operators
    constexpr bool operator==(const frac& rhs) const {
        return dbl() == rhs.dbl();
    }

    constexpr bool operator!=(const frac& rhs) const {
        return !(*this == rhs);
    }

    constexpr bool operator<(const frac& rhs) const {
        return dbl() < rhs.dbl();
    }

    constexpr bool operator<=(const frac& rhs) const {
        return !(*this > rhs);
    }

    constexpr bool operator>(const frac& rhs) const {
        return rhs < *this;
    }

    constexpr bool operator>=(const frac& rhs) const {
        return !(*this < rhs);
    }
};

int main() {
    constexpr frac a(10, 15);
    constexpr frac b(2, 3);
    constexpr frac c(5, 3);

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "The frac a is " << a.dbl() << "\n";
    std::cout << "The frac b is " << b.dbl() << "\n";
    std::cout << "The frac c is " << c.dbl() << "\n";

    static_assert(a < c, "a < c failed");
    static_assert(c > a, "c > a failed");
    static_assert(a == b, "a == b failed");
    static_assert(a <= b, "a <= b failed");
    static_assert(a <= c, "a <= c failed");
    static_assert(c >= a, "c >= a failed");
    static_assert(a != c, "a != c failed");

    std::cout << "done.\n";
}
