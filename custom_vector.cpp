#include<iostream>
#include<algorithm>// for std::swap
#include<stdexcept>

template<typename T>
class myvector{
    public:
        myvector(){
            arr=nullptr;
            capacity=0,index=0;
        }
        ~myvector(){
            delete[] arr;
        }
        myvector(const myvector& other){
            capacity=other.capacity,index=other.index;
            arr=new T[capacity];
            for(size_t i=0;i<capacity;i++){
                arr[i]=other.arr[i];
            }
        }
        // Copy assignment operator
        myvector& operator=(const myvector& other){
            if (this != &other) { // Self-assignment check
                myvector temp(other); // Create a temporary copy
                swap(temp); // Swap with the temporary copy
            }
            return *this;
        }
        //Move constructor
        myvector(myvector&& other)noexcept{
            arr=other.arr;
            capacity=other.capacity;
            index=other.index;
            other.arr=nullptr;
            other.capacity=0;
            other.index=0;
        }
        // Move assignment operator
        myvector& operator=(myvector&& other) noexcept {
            if (this != &other) { // Self-assignment check
                delete[] arr; // Free existing memory
                arr = other.arr;
                capacity = other.capacity;
                index = other.index;
                other.arr = nullptr;
                other.capacity = 0;
                other.index = 0;
            }
            return *this;
        }

        void swap(myvector& other)noexcept{
            std::swap(arr,other.arr);
            std::swap(capacity,other.capacity);
            std::swap(index,other.index);
        }

        //Add element to end of the vector
        void push_back(const T& value){
            if(index>=capacity){
                if(capacity==0)resize(1);
                else resize(capacity*2);
            }
            arr[index]=value;
            index++;
        }
        // Add an element to the end of the vector (move version)
        void push_back(T&& value) {
            if (index >= capacity) {
                resize(capacity == 0 ? 1 : capacity * 2); // Double the capacity
            }
            arr[index] = std::move(value);
            index++;
        }

        void pop_back(){
            if(index>0){
                index--;
            }else{
                throw std::out_of_range("Vector is empty");
            }
        }
        T& operator[](size_t i){
            if(i>=index){
                throw std::out_of_range("Index out of range");
            }
            return arr[i];
        }
        // Const version of element access
        const T& operator[](size_t i) const {
            if (i >= index) {
                throw std::out_of_range("Index out of range");
            }
            return arr[i];
        }
        // Get the current number of elements in the vector
        size_t get_size() const {
            return index;
        }
        // Get the current capacity of the vector
        size_t get_capacity() const {
            return capacity;
        }

        // Check if the vector is empty
        bool empty() const {
            return index == 0;
        }

        // Clear the vector
        void clear() {
            index = 0;
        }
        // Iterator support (basic implementation)
        class Iterator {
        private:
            T* ptr;
        public:
            Iterator(T* p){
                ptr=p;
            }
            T& operator*() { return *ptr; }
            Iterator& operator++() { ++ptr; return *this; }
            bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
        };

        Iterator begin() { return Iterator(arr); }
        Iterator end() { return Iterator(arr + index); }

    private:
        T* arr;//pointer to dynamically allocated array
        size_t capacity;//total capacity
        size_t index;//currently filled

        void resize(size_t new_capacity) {
            T* new_arr = new T[new_capacity];
            if (arr) {
                for (size_t i = 0; i < index; ++i) {
                    new_arr[i] = std::move(arr[i]);
                }
                delete[] arr;
            }
            arr = new_arr;
            capacity = new_capacity;
        }
};

int main() {
    myvector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);
    vec.push_back(50);

    std::cout << "Vector size: " << vec.get_size() << "\n";
    std::cout << "Vector capacity: " << vec.get_capacity() << "\n";

    std::cout << "Elements: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    vec.pop_back();
    std::cout << "After pop_back, size: " << vec.get_size() << "\n";

    std::cout << "Element at index 1: " << vec[1] << "\n";

    // Test move semantics
    myvector<int> vec2 = std::move(vec);
    std::cout << "After move, vec2 size: " << vec2.get_size() << "\n";
    std::cout << "After move, vec size: " << vec.get_size() << "\n";

    return 0;
}