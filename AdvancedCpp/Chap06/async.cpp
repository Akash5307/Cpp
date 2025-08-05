#include <bits/stdc++.h>
#include <chrono>
#include <future>
#include <iomanip>  // For std::setprecision, std::setw, etc.

using namespace std;
using std::chrono::steady_clock;
using secs = std::chrono::duration<double>;

struct prime_time {
    secs dur{};
    uint64_t count{};
};

prime_time count_primes(const uint64_t& max) {
    prime_time ret{};
    constexpr auto isprime = [](uint64_t n) {
        for(uint64_t i {2}; i < n / 2; ++i) {
            if(n % i == 0) return false;
        }
        return true;
    };
    uint64_t start {2};
    uint64_t end {max};
    auto time_thread_start = steady_clock::now();
    for(auto i = start; i <= end ; ++i) {
        if(isprime(i)) ++ret.count;
    }
    ret.dur = steady_clock::now() - time_thread_start;
    return ret;
}

int main() {
    constexpr uint64_t max_prime {0x1FFFF};  // 131071
    constexpr size_t num_threads {15};
    std::list<std::future<prime_time>> swarm;

    cout << "start parallel primes\n";
    auto time_start = steady_clock::now();

    for(size_t i = 0; i < num_threads; ++i) {
        swarm.emplace_back(std::async(count_primes, max_prime));
    }

    int i = 0;
    for(auto& f : swarm) {
        auto [dur, count] = f.get();  // structured binding
        cout << "thread "
             << setw(2) << setfill('0') << ++i
             << ": found " << count
             << " primes in "
             << fixed << setprecision(5) << dur.count()
             << "s\n";
    }

    secs dur_total {steady_clock::now() - time_start};
    cout << "total duration: "
         << fixed << setprecision(5) << dur_total.count()
         << "s\n";

    return 0;
}
