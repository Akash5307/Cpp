// rational2.cpp by Bill Weinman [bw.org]
// updated 2022-10-24
#include<bits/stdc++.h>
using namespace std;

const std::string nanstr {"[NAN]"};

class Rational {
    int n {0};
    int d {1};
public:
    Rational(int numerator = 0, int denominator = 1) : n(numerator), d(denominator) {}
    Rational(const Rational& rhs) : n(rhs.n), d(rhs.d) {}    // copy constructor
    ~Rational();
    int numerator() const { return n; };
    int denominator() const { return d; };
    Rational reduce() const;        // reduce fraction
    std::string str() const;        // return a formatted STL string
    std::string raw_str() const;    // return a non-reduced STL string
    Rational& operator = (const Rational&);  // assignment
};

Rational Rational::reduce() const {
    if(n == 0 || d <= 3) return *this;
    for(auto div = d - 1; div; --div) {
        if(n % div == 0 && d % div == 0) {
            return Rational(n / div, d / div );
        }
    }
    return *this;
}

std::string Rational::str() const {
    if(d == 0) return nanstr;
    if(d == 1 || n == 0) return std::to_string(n);

    auto abs_n = abs(n);     // absolute value
    if(abs_n > d) {
        auto whole = n / d;
        auto remainder = abs_n % d;
        if(remainder) return std::to_string(whole) + " " + Rational(remainder, d).str();
        else return std::to_string(whole);
    } else {
        return reduce().raw_str();
    }
}

std::string Rational::raw_str() const {
    return std::to_string(n) + "/" + std::to_string(d);
}

Rational& Rational::operator = (const Rational& rhs) {
    if (this != &rhs) {
        n = rhs.numerator();
        d = rhs.denominator();
    }
    return *this;
}

Rational operator + (const Rational& lhs, const Rational& rhs) {
    return Rational((lhs.numerator() * rhs.denominator()) + (lhs.denominator() * rhs.numerator()),
                    lhs.denominator() * rhs.denominator());
}

Rational operator - (const Rational& lhs, const Rational& rhs) {
    return Rational((lhs.numerator() * rhs.denominator()) - (lhs.denominator() * rhs.numerator()),
                    lhs.denominator() * rhs.denominator());
}

Rational operator * (const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
}

Rational operator / (const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.numerator() * rhs.denominator(), lhs.denominator() * rhs.numerator());
}

Rational::~Rational() {
    n = 0; d = 1;
}


int main() {
    Rational a {4, 3};  // 1 1/3

    cout<<"a + 20 = "<< (a + 20).raw_str()<<"\n";
    cout<<"a - 20 = "<< (a - 20).raw_str()<<"\n";
    cout<<"a * 20 = "<< (a * 20).raw_str()<<"\n";
    cout<<"a / 20 = "<< (a / 20).raw_str()<<"\n";

    cout<<"\n";

    cout<<"20 + a = "<<(20 + a).raw_str()<<"\n";
    cout<<"20 - a = "<<(20 - a).raw_str()<<"\n";
    cout<<"20 * a = "<< (20 * a).raw_str()<<"\n";
    cout<<"20 / a = "<< (20 / a).raw_str()<<"\n";
}
