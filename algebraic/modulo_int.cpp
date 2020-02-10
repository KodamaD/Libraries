
#include <iostream>

template <int MODULUS = 1000000007>
class modulo_int {
  static constexpr int mod = MODULUS;
  static_assert(mod > 0, "mod must be positive");
private:
  long long value;
  constexpr void normalize() {
    value %= mod;
    if (value < 0) value += mod;
  }
public:
  constexpr modulo_int(long long value_ = 0): value(value_) { normalize(); }
  constexpr modulo_int operator - () const { return modulo_int(mod - value); }
  constexpr modulo_int operator ~ () const { return power(mod - 2); }
  constexpr long long operator () () const { return value; }
  constexpr modulo_int operator + (const modulo_int& rhs) const { return modulo_int(*this) += rhs; }
  constexpr modulo_int& operator += (const modulo_int& rhs) {
    if ((value += rhs.value) >= mod) value -= mod;
    return (*this);
  }
  constexpr modulo_int operator - (const modulo_int& rhs) const { return modulo_int(*this) -= rhs; }
  constexpr modulo_int& operator -= (const modulo_int& rhs) {
    if ((value += mod - rhs.value) >= mod) value -= mod;
    return (*this);
  }
  constexpr modulo_int operator * (const modulo_int& rhs) const { return modulo_int(*this) *= rhs; }
  constexpr modulo_int& operator *= (const modulo_int& rhs) {
    (value *= rhs.value) %= mod;
    return (*this);
  }
  constexpr modulo_int operator / (const modulo_int& rhs) const { return modulo_int(*this) /= rhs; }
  constexpr modulo_int& operator /= (const modulo_int& rhs) {
    return (*this) *= ~rhs;
  }
  constexpr modulo_int power (unsigned long long pow) const {
    modulo_int result(1), mult(*this);
    while (pow > 0) {
      if (pow & 1) result *= mult;
      mult *= mult;
      pow >>= 1;
    }
    return result;
  }
  friend std::istream& operator >> (std::istream& stream, modulo_int& lhs) {
    stream >> lhs.value;
    lhs.normalize();
    return stream;
  }
  friend std::ostream& operator << (std::ostream& stream, const modulo_int& rhs) {
    return stream << rhs.value;
  }
};

int main() {
  return 0;
}
