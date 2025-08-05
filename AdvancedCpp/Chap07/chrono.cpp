#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <cmath>

using std::chrono::duration;

using seconds = duration<double>;
using milliseconds = duration<double, std::milli>;
using microseconds = duration<double, std::micro>;
using fps24 = duration<unsigned long, std::ratio<1, 24>>;

constexpr uint64_t MAX_PRIME{ 0x1FFFF };

std::string make_commas(const uint64_t& num) {
    auto s = std::to_string(num);
    for (auto l = static_cast<int>(s.length()) - 3; l > 0; l -= 3) {
        s.insert(l, ",");
    }
    return s;
}

uint64_t count_primes() {
    auto isprime = [](const uint64_t n) {
        for (uint64_t i{2}; i <= n / 2; ++i) {
            if (n % i == 0) return false;
        }
        return true;
    };

    uint64_t count{0};
    for (uint64_t i = 2; i <= MAX_PRIME; ++i) {
        if (isprime(i)) ++count;
    }
    return count;
}

template<typename Func>
seconds timer(const Func& f) {
    using timer_clock = std::chrono::steady_clock;
    auto t1 = timer_clock::now();
    auto count = f();
    auto t2 = timer_clock::now();
    seconds secs{t2 - t1};
    std::cout << "found " << make_commas(count) << " primes in range\n";
    return secs;
}

int main() {
    auto t = std::chrono::system_clock::now();
    std::time_t t_time = std::chrono::system_clock::to_time_t(t);
    std::cout << "system_clock::now is " << std::put_time(std::localtime(&t_time), "%F %T") << "\n\n";

    std::cout << "counting primes up to " << make_commas(MAX_PRIME) << "\n";
    auto secs = timer(count_primes);
    std::cout << '\n';

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "time elapsed: " << secs.count() << " sec\n";
    std::cout << "time elapsed: " << milliseconds(secs).count() << " ms\n";
    std::cout << "time elapsed: " << microseconds(secs).count() << " μs\n";

    auto frame_count = static_cast<unsigned long>(secs.count() * 24);
    std::cout << "time elapsed: " << frame_count << " frames at 24 fps\n\n";

    // Shortened generic formatting
    std::cout << "time elapsed: " << secs.count() << " s\n";
    std::cout << "time elapsed: " << milliseconds(secs).count() << " ms\n";
    std::cout << "time elapsed: " << microseconds(secs).count() << " μs\n";
}
