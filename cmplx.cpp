#include <iostream>
template <class T>
class cmplx{
  private:
    T a;
    T b;
  public:
    cmplx() {
        T dont_care1=0; 
        T dont_care2=0;
        a = dont_care1;
        b = dont_care2;
    }
    cmplx(T x, T y){
      a=x,b=y;
    }
    cmplx (const cmplx<T>& other){
      if(this!=&other){
        *this=other;
      }
    }
    cmplx<T>& operator=(const cmplx<T>& other){
      a=other.a;
      b=other.b;
      return *this;
    }
    template<class U>
    cmplx<T>& operator=(const cmplx<U>& other){
      a=T(other.x);
      b=T(other.y);
      return *this;
    }
    cmplx<T>operator -(){
      return cmplx<T>(-a,-b);
    }
    template<class U>
    cmplx<T>operator +=(const cmplx<U>& other){
      a+=other.a;
      b+=other.b;
      return *this;
    }
    template<class U>
    cmplx<T>operator -=(const cmplx<U>& other){
      a-=other.a;
      b-=other.b;
      return *this;
    }
    template<class U>
    cmplx<T>operator *=(const cmplx<U>& other){
      a=a*other.re()-b*other.im();;
      b=a*other.im()+b*other.re();
      return *this;
    }
    cmplx<T> exchg() const { return cmplx<T>(b, a); }
    cmplx<T> conj() const { return cmplx<T>(a, -b); }
    T re() const { return  a; }
    T im() const { return b; }
    std::ostream& dump(std::ostream& os) const {
        os << a << " " << b;
        return os;
    }
};
template<class T>
std::ostream& operator<<(std::ostream& os, const cmplx<T> val) {
    return val.dump(os);
}
int main() { 
  cmplx<int> c1(3, 4);  // 3 + 4i
  cmplx<int> c2(1, -2); // 1 - 2i
  cmplx<double> c3(2.5, 3.7); // 2.5 + 3.7i

  // Test the constructors and assignment operators
  cmplx<int> c4 = c1;  // Copy constructor
  cmplx<int> c5;
  c5 = c2;  // Assignment operator

  // Test the unary negation operator
  cmplx<int> c6 = -c1;  // -3 - 4i

  // Test the +=, -=, and *= operators
  c1 += c2;  // c1 = (3 + 1) + (4 - 2)i => 4 + 2i
  c2 -= c1;  // c2 = (1 - 4) + (-2 - 2)i => -3 - 4i
  c3 *= c1;  // c3 = (2.5 * 4 - 3.7 * 2) + (2.5 * 2 + 3.7 * 4)i => 5.6 + 19.8i
  // Test the exchg() function
  cmplx<int> c7 = c1.exchg();  // Swap real and imaginary parts: 2 + 4i

  // Test the conj() function
  cmplx<int> c8 = c1.conj();  // Conjugate: 4 - 2i

  // Test the stream insertion operator
  std::cout << "c1: " << c1 << std::endl;  // 4 2
  std::cout << "c2: " << c2 << std::endl;  // -3 -4
  std::cout << "c3: " << c3 << std::endl;  // 5.6 19.8
  std::cout << "c4: " << c4 << std::endl;  // 3 4
  std::cout << "c5: " << c5 << std::endl;  // 1 -2
  std::cout << "c6: " << c6 << std::endl;  // -3 -4
  std::cout << "c7: " << c7 << std::endl;  // 2 4
  std::cout << "c8: " << c8 << std::endl;  // 4 -2

  return 0;
}