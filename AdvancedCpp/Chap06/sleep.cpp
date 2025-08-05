#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>

using std::chrono::steady_clock;
using std::chrono::duration;
using std::this_thread::sleep_for;
using std::this_thread::sleep_until;

using namespace std::chrono_literals;

int main() {
    std::cout << "let's wait a bit...\n";

    auto t1 = steady_clock::now();
    std::cout << "sleep for 2.5 seconds\n";
    sleep_for(2s + 500ms);

    std::cout << "sleep for 3 seconds\n";
    sleep_until(steady_clock::now() + 3s);

    duration<double> dur1 = steady_clock::now() - t1;
    std::cout << "total duration: "
              << std::fixed << std::setprecision(5)
              << dur1.count() << "s\n";
}
//g++ -std=c++17 -pthread -o sleep_cpp_style sleep.cpp
