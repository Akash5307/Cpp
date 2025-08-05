//  mutex.cpp modified for C++ style cout
#include <iostream>
#include <string_view>
#include <thread>
#include <future>
#include <mutex>
#include <list>
#include <optional>

std::mutex animal_mutex {};

class Animal {
    using friend_t = std::list<Animal>;
    std::string_view s_name {"unk"};
    friend_t l_friends {};
public:
    Animal() = delete;
    Animal(const std::string_view n) : s_name(n) {}

    bool operator==(const Animal& o) const {
        return s_name == o.s_name;
    }

    bool add_friend(Animal& o) noexcept {
        std::cout << "add_friend " << s_name << " -> " << o.s_name << '\n';
        if (*this == o) return false;

        std::lock_guard<std::mutex> l {animal_mutex};
        if (!is_friend(o)) l_friends.emplace_back(o);
        if (!o.is_friend(*this)) o.l_friends.emplace_back(*this);

        return true;
    }

    bool delete_friend(Animal& o) noexcept {
        std::cout << "delete_friend " << s_name << " <-> " << o.s_name << '\n';
        if (*this == o) return false;

        std::lock_guard<std::mutex> l {animal_mutex};
        if (auto it = find_friend(o); it) l_friends.erase(it.value());
        if (auto it = o.find_friend(*this); it) o.l_friends.erase(it.value());

        return true;
    }

    bool is_friend(const Animal& o) const {
        for (const auto& a : l_friends) {
            if (a == o) return true;
        }
        return false;
    }

    std::optional<friend_t::iterator> find_friend(const Animal& o) noexcept {
        for (auto it = l_friends.begin(); it != l_friends.end(); ++it) {
            if (*it == o) return it;
        }
        return {};
    }

    void pfriends() const noexcept {
        std::lock_guard<std::mutex> l {animal_mutex};
        auto n_animals = l_friends.size();
        std::cout << s_name << " friends: ";
        if (!n_animals) {
            std::cout << "none";
        } else {
            for (const auto& n : l_friends) {
                std::cout << n.s_name;
                if (--n_animals) std::cout << ", ";
            }
        }
        std::cout << '\n';
    }
};

int main() {
    auto cat1 = std::make_unique<Animal>("Felix");
    auto tiger1 = std::make_unique<Animal>("Hobbes");
    auto dog1 = std::make_unique<Animal>("Astro");
    auto rabbit1 = std::make_unique<Animal>("Bugs");

    std::cout << "add friends\n";
    auto a1 = std::async([&]{ cat1->add_friend(*tiger1); });
    auto a2 = std::async([&]{ cat1->add_friend(*rabbit1); });
    auto a3 = std::async([&]{ rabbit1->add_friend(*dog1); });
    auto a4 = std::async([&]{ rabbit1->add_friend(*tiger1); });

    a1.wait();
    a2.wait();
    a3.wait();
    a4.wait();

    std::cout << "\nprint animals\n";
    auto p1 = std::async([&]{ cat1->pfriends(); });
    auto p2 = std::async([&]{ tiger1->pfriends(); });
    auto p3 = std::async([&]{ dog1->pfriends(); });
    auto p4 = std::async([&]{ rabbit1->pfriends(); });

    p1.wait();
    p2.wait();
    p3.wait();
    p4.wait();

    std::cout << "\ndelete Felix/Bugs friendship\n";
    auto a5 = std::async([&]{ cat1->delete_friend(*rabbit1); });
    a5.wait();

    std::cout << "\nprint animals\n";
    p1 = std::async([&]{ cat1->pfriends(); });
    p2 = std::async([&]{ tiger1->pfriends(); });
    p3 = std::async([&]{ dog1->pfriends(); });
    p4 = std::async([&]{ rabbit1->pfriends(); });

    p1.wait();
    p2.wait();
    p3.wait();
    p4.wait();

    std::cout << "\nend of main()\n";
}
//g++ -std=c++17 -pthread mutex.cpp
