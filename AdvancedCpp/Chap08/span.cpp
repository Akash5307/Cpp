#include <iostream>

template<typename T>
void pspan(const T* arr, std::size_t size) {
    std::cout << "number of elements: " << size << '\n';
    std::cout << "size of span: " << size * sizeof(T) << '\n';
    for (std::size_t i = 0; i < size; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}

int main() {
    int ca1[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    pspan(ca1, sizeof(ca1) / sizeof(int));
}
//g++ -std=c++17 span.cpp -o span
