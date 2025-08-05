#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>

constexpr size_t n_samples {1000};
constexpr size_t n_partitions {10};
constexpr size_t n_max {50};

template <typename RNG>
void histogram(const std::string& rng_name) {
    auto p_ratio = static_cast<double>(RNG::max()) / n_partitions;

    RNG rng{};
    std::vector<size_t> v(n_partitions);

    for (size_t i{}; i < n_samples; ++i) {
        ++v[static_cast<size_t>(rng() / p_ratio)];
    }

    auto max_el = std::max_element(v.begin(), v.end());
    auto v_ratio = *max_el / n_max;
    if (v_ratio < 1) v_ratio = 1;

    std::cout << "engine: " << rng_name << '\n';
    for (size_t i{}; i < n_partitions; ++i) {
        std::cout << std::setw(2) << std::setfill('0') << (i + 1) << ":";
        size_t bar_length = v[i] / v_ratio;
        for (size_t j = 0; j < bar_length; ++j) {
            std::cout << '*';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

int main() {
    histogram<std::random_device>("random_device");
    histogram<std::default_random_engine>("default_random_engine");

    // Uncomment these if you want to include more engines
    // histogram<std::minstd_rand0>("minstd_rand0");
    // histogram<std::minstd_rand>("minstd_rand");
    // histogram<std::mt19937>("mt19937");
    // histogram<std::mt19937_64>("mt19937_64");
    // histogram<std::ranlux24_base>("ranlux24_base");
    // histogram<std::ranlux48_base>("ranlux48_base");
    // histogram<std::ranlux24>("ranlux24");
    // histogram<std::ranlux48>("ranlux48");
    // histogram<std::knuth_b>("knuth_b");
}
