// container-02.cpp by Bill Weinman [bw.org]
// updated 2022-10-26
#include<bits/stdc++.h>
using namespace std;


template<typename T>
class container {
    std::vector<T> things {};
public:
    container() { cout<<"default ctor\n"; }    // default ctor
    container(std::initializer_list<T> il);     // il ctor
    container(const container& rhs);            // copy ctor
    container(container&& rhs) noexcept;        // move ctor
    ~container();
    container<T>& operator = (const container& rhs);
    void reset();
    string str() const;
};

// initializer-list ctor
template<typename T>
container<T>::container(std::initializer_list<T> il) : things {il.begin(), il.end()} {
    cout<<"initializer-list ctor\n";
}

// copy ctor
template<typename T>
container<T>::container(const container& rhs) : things {rhs.things} {
    cout<<"copy ctor\n";
}

// move ctor
template<typename T>
container<T>::container(container&& rhs) noexcept
: things {std::move(rhs.things)} {
    cout<<"move ctor\n";
}

// copy assignment operator
template<typename T>
container<T>& container<T>::operator = (const container& rhs) {
    cout<<"copy assignment operator\n";
    if(this != &rhs) things = rhs.things;
    return *this;
}

// dtor
template<typename T>
container<T>::~container() {
    cout<<"dtor\n";
}

template<typename T>
void container<T>::reset() {
    things.clear();
}

template<typename T>
string container<T>::str() const {
    string out {};
    if(things.empty()) return "[empty]";
    for(auto i : things) {
        if(out.size()) out += ':';
        out += i;
    }
    return out;
}

template <typename T>
container<T> f(container<T> o) {
    return o;
}

int main() {
    container<string> a {"one", "two", "three", "four", "five"};
    container<string> b {"five", "six", "seven"};

    cout<<"a: "<<a.str()<<"\n";
    cout<<"b: "<<b.str()<<"\n";

    container c {std::move(a)};
    cout<<"a: "<< a.str()<<"\n";
    cout<<"c: "<< c.str()<<"\n";
}
