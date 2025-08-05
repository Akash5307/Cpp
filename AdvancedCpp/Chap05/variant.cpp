// variant.cpp by Bill Weinman [bw.org]
// updated 2022-10-28
#include<bits/stdc++.h>
using namespace std;

constexpr auto newline = []{ cout<<"\n"; };

class Animal {
    string_view _name {};
    string_view _sound {};
public:
    Animal() = delete;
    Animal(string_view n, string_view s) : _name{ n }, _sound{ s } {}

    void speak() const {
        cout<<_name<<" says "<<_sound<<"\n";
    }

    void sound(string_view s) {
        _sound = s;
    }
};

class Cat : public Animal {
public:
    Cat(string_view n) : Animal(n, "meow") {}
};

class Dog : public Animal {
public:
    Dog(string_view n) : Animal(n, "arf!") {}
};

class Wookie : public Animal {
public:
    Wookie(string_view n) : Animal(n, "grrraarrgghh!") {}
};

struct animal_speaks {
    void operator()(const Dog& d) const { d.speak(); }
    void operator()(const Cat& c) const { c.speak(); }
    void operator()(const Wookie& w) const { w.speak(); }
};

int main() {
    using v_animal = std::variant<Cat, Dog, Wookie>;
    std::vector<v_animal> pets { Cat{"Hobbes"}, Dog{"Fido"}, Cat{"Bill"}, Wookie{"Chewie"} };

    cout<<"-- get method\n";
    for (const v_animal& a : pets) {
        auto idx = a.index();
        if(idx == 0) get<Cat>(a).speak();
        if(idx == 1) get<Dog>(a).speak();
        if(idx == 2) get<Wookie>(a).speak();
    }

    newline();
    cout<<"-- get_if method\n";
    for (const v_animal& a : pets) {
        if (const auto& o = get_if<Cat>(&a); o) o->speak();
        else if (const auto& o = get_if<Dog>(&a); o) o->speak();
        else if (const auto& o = get_if<Wookie>(&a); o) o->speak();
    }

    newline();
    cout<<"-- visit method\n";
    for (const v_animal& a : pets) {
        std::visit(animal_speaks{}, a);
    }
}
