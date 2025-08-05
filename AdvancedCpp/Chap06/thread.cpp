#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>

using std::thread;

void sleepms(const unsigned ms) {
    using millis = std::chrono::milliseconds;
    std::this_thread::sleep_for(millis(ms));
}

void thread_func(const int n) {
    std::cout << "This is t" << n << '\n';
    auto slp_dur = 100 * n;

    for (auto i = 0; i < 5; ++i) {
        sleepms(slp_dur);
        std::cout << "t" << n << " (" << slp_dur << "ms): loop " << i + 1 << '\n';
    }
    std::cout << "Finishing t" << n << '\n';
}

int main() {
    thread t1(thread_func, 1);
    thread t2(thread_func, 2);
    t1.detach();
    t2.detach();

    std::cout << "main() sleep 2 sec\n";
    sleepms(2000);   // give the threads time

    std::cout << "end of main()\n";
}
//g++ -std=c++17 -pthread -o thread_cpp_style thread.cpp
