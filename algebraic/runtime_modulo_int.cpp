
#include <iostream>

template <class T>
class runtime_modulo_int {
public:
  static int mod() {
    return T::value;
  }
private:
  long long value;
  void normalize() {
    value %= mod();
    if (value < 0) value += mod();
  }
public:
  runtime_modulo_int(long long value_ = 0): value(value_) { normalize(); }
  runtime_modulo_int operator - () const { return runtime_modulo_int(mod() - value); }
  runtime_modulo_int operator ~ () const { return power(mod() - 2); }
  long long operator () () const { return value; }
  runtime_modulo_int operator + (const runtime_modulo_int& rhs) const { return runtime_modulo_int(*this) += rhs; }
  runtime_modulo_int& operator += (const runtime_modulo_int& rhs) {
    if ((value += rhs.value) >= mod()) value -= mod();
    return (*this);
  }
  runtime_modulo_int operator - (const runtime_modulo_int& rhs) const { return runtime_modulo_int(*this) -= rhs; }
  runtime_modulo_int& operator -= (const runtime_modulo_int& rhs) {
    if ((value += mod() - rhs.value) >= mod()) value -= mod();
    return (*this);
  }
  runtime_modulo_int operator * (const runtime_modulo_int& rhs) const { return runtime_modulo_int(*this) *= rhs; }
  runtime_modulo_int& operator *= (const runtime_modulo_int& rhs) {
    (value *= rhs.value) %= mod();
    return (*this);
  }
  runtime_modulo_int operator / (const runtime_modulo_int& rhs) const { return runtime_modulo_int(*this) /= rhs; }
  runtime_modulo_int& operator /= (const runtime_modulo_int& rhs) {
    return (*this) *= ~rhs;
  }
  runtime_modulo_int power (unsigned long long pow) const {
    runtime_modulo_int result(1), mult(*this);
    while (pow > 0) {
      if (pow & 1) result *= mult;
      mult *= mult;
      pow >>= 1;
    }
    return result;
  }
  friend std::istream& operator >> (std::istream& stream, runtime_modulo_int& lhs) {
    stream >> lhs.value;
    lhs.normalize();
    return stream;
  }
  friend std::ostream& operator << (std::ostream& stream, const runtime_modulo_int& rhs) {
    return stream << rhs.value;
  }
};

struct runtime_mod { static int value; };
int runtime_mod::value;
int &mod = runtime_mod::value;
using modint = runtime_modulo_int<runtime_mod>;

int main() {
  return 0;
}
