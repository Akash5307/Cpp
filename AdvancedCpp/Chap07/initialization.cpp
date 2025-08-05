#include <iostream>
#include <initializer_list>
#include <vector>
#include <string>

template <typename T>
class thing {
    T v {};
    std::string state {"undef"};
public:
    thing() : v(T{}) {
        std::cout << "default constructor\n";
        state = "zero";
    }

    thing(const T& p) : v(p) {
        std::cout << "copy constructor\n";
        state = "copied value";
    }

    thing(const std::initializer_list<T>& ilist) {
        std::cout << "initializer_list: ";
        for (const auto& e : ilist) std::cout << e << " ";
        std::cout << "\n";
        const auto sz = ilist.size();
        auto pt = ilist.begin();
        if(sz > 1) pt += sz / 2;
        v = *pt;
        state = "list constructed";
    }

    thing(const size_t p1, const T& p2) {
        std::cout << "specific constructor: " << p1 << ", " << p2 << "\n";
        if (p1 < 10) return;
        else v = p2;
        state = "specific value";
    }

    void status() const {
        std::cout << "status: " << state << ", value " << v << "\n";
    }
};

void initialize_this() {
    std::cout << "t1: ";
    thing<int> t1 {};
    t1.status();
    std::cout << '\n';

    std::cout << "t2: ";
    thing<int> t2 {7};
    t2.status();
    std::cout << '\n';

    std::cout << "t3: ";
    thing t3(42);
    t3.status();
    std::cout << '\n';

    std::cout << "t4: ";
    thing<int> t4 {1, 2, 3, 4, 5};
    t4.status();
    std::cout << '\n';

    std::cout << "t5: ";
    thing<int> t5 {1, 2};
    t5.status();
    std::cout << '\n';

    std::cout << "t6: ";
    thing<int> t6(1, 2);
    t6.status();
    std::cout << '\n';
}

int main() {
    int x {};
    std::cout << "x is " << x << "\n";

    initialize_this();
}
