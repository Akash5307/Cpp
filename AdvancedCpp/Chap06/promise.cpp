#include <iostream>
#include <list>
#include <chrono>
#include <future>
#include <iomanip>

using std::chrono::steady_clock;
using secs = std::chrono::duration<double>;

struct prime_time {
    secs dur{};
    uint64_t count{};
};

void count_primes(const uint64_t& max, std::promise<prime_time> pval) {
    prime_time ret{};
    constexpr auto isprime = [](uint64_t n) {
        for(uint64_t i {2}; i < n / 2; ++i) {
            if(n % i == 0) return false;
        }
        return true;
    };
    uint64_t start {2};
    uint64_t end {max};
    auto t1 = steady_clock::now();
    for(auto i = start; i <= end ; ++i) {
        if(isprime(i)) ++ret.count;
    }
    ret.dur = steady_clock::now() - t1;
    pval.set_value(ret);
}

int main() {
    constexpr uint64_t max_prime {0x1FFFF};
    constexpr size_t num_threads {15};
    std::list<std::future<prime_time>> swarm;

    std::cout << "start parallel primes\n";
    auto t1 = steady_clock::now();
    for(auto i = num_threads; i; --i) {
        std::promise<prime_time> promise_o{};
        auto future_o = promise_o.get_future();
        swarm.emplace_back(std::move(future_o));
        std::thread t(count_primes, max_prime, std::move(promise_o));
        t.detach();
    }

    int i = 0;
    for(auto& f : swarm) {
        auto [dur, count] = f.get();  // structured binding
        std::cout << "thread "
                  << std::setfill('0') << std::setw(2) << ++i
                  << ": found " << count << " primes in "
                  << std::fixed << std::setprecision(5)
                  << dur.count() << "s\n";
    }

    secs dur_total{ steady_clock::now() - t1 };
    std::cout << "total duration: "
              << std::fixed << std::setprecision(5)
              << dur_total.count() << "s\n";
}

//g++ -std=c++17 -pthread -o promise_cpp_style promise.cpp
