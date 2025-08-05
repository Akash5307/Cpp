#include <iostream>
#include <deque>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <iomanip>  // Optional, for formatting numbers if needed

using namespace std::chrono_literals;

constexpr size_t num_items {10};
constexpr auto delay_time {250ms};

std::mutex p_mtx {};  // producer mutex
std::mutex c_mtx {};  // consumer mutex
std::deque<size_t> q {};
std::atomic_flag finished = ATOMIC_FLAG_INIT;

void sleep_ms(const std::chrono::milliseconds& delay) {
    std::this_thread::sleep_for(delay);
}

void producer() {
    for (size_t i = 0; i < num_items; ++i) {
        sleep_ms(delay_time);
        std::cout << "push " << i << " on the queue\n";
        std::lock_guard<std::mutex> lck{p_mtx};
        q.push_back(i);
    }

    std::lock_guard<std::mutex> lck{p_mtx};
    finished.test_and_set();  // Signal that producer is done
}

void consumer() {
    while (!finished.test()) {
        std::lock_guard<std::mutex> lck{c_mtx};
        while (!q.empty()) {
            std::cout << "pop " << q.front() << " from the queue\n";
            q.pop_front();
        }
        // Optional small sleep to avoid tight busy-waiting
        std::this_thread::sleep_for(10ms);
    }

    // Drain any remaining items after producer signals finished
    std::lock_guard<std::mutex> lck{c_mtx};
    while (!q.empty()) {
        std::cout << "pop " << q.front() << " from the queue\n";
        q.pop_front();
    }
}

int main() {
    std::thread t1 {producer};
    std::thread t2 {consumer};
    t1.join();
    t2.join();
    std::cout << "finished!\n";
}

// g++ -std=c++20 -pthread ./Chap06/producer-consumer.cpp
