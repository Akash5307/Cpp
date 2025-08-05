#include <iostream>
#include <string>
#include <list>
#include <thread>
#include <atomic>
#include <iomanip>

std::atomic_bool ready{};
std::atomic_uint64_t g_count{};
std::atomic_flag winner = ATOMIC_FLAG_INIT;

constexpr uint64_t max_count{1'000'000};
constexpr int max_threads{100};

std::string make_commas(const uint64_t& num) {
    auto s = std::to_string(num);
    for (auto l = static_cast<int>(s.length()) - 3; l > 0; l -= 3) {
        s.insert(l, ",");
    }
    return s;
}

void sleep_ms(unsigned ms) {
    using std::this_thread::sleep_for;
    using std::chrono::milliseconds;
    sleep_for(milliseconds(ms));
}

void countem(int id) {
    while (!ready) std::this_thread::yield();
    for (auto i = 0; i < max_count; ++i) {
        if (winner.test_and_set(std::memory_order_relaxed)) return;
        ++g_count;
    }
    if (!winner.test_and_set(std::memory_order_relaxed)) {
        std::cout << "thread " << std::setw(2) << std::setfill('0') << id << " won!" << '\n';
    }
};

int main() {
    std::list<std::thread> swarm{};
    std::cout << "spawn " << max_threads << " threads\n";
    for (int i = 0; i < max_threads; ++i) {
        swarm.emplace_back(countem, i);
    }

    sleep_ms(25); // give the threads a beat to spawn
    std::cout << "Go!\n";
    ready = true;

    for (auto& t : swarm) t.join();
    std::cout << "global count: " << make_commas(g_count) << '\n';
}
