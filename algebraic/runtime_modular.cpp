#pragma once

#include <cstdint>
#include <iostream>

template <class Modulus>
class modular {
public:
  using value_type = uint32_t;
  using max_type = uint64_t;
  
  static value_type mod() { return Modulus::value; } 
  static value_type get_mod() { return Modulus::value;; }

  template <class T>
  static value_type normalize(T value_) {
    if (value_ < 0) {
      value_ = -value_;
      value_ %= mod();
      if (value_ == 0) return 0;
      return mod() - value_;
    }
    return value_ % mod();
  }

private:
  value_type value;

public:
  modular(): value(0) { }
  template <class T>
  explicit modular(T value_): value(normalize(value_)) { }
  template <class T>
  explicit operator T() { return static_cast<T>(value); }

  value_type get() const { return value; }
  modular operator - () const { return modular(mod() - value); }
  modular operator ~ () const { return inverse(); }

  value_type &extract() { return value; }
  modular inverse() const { return power(mod() - 2); }
  modular power(max_type exp) const {
    modular res(1), mult(*this);
    while (exp > 0) {
      if (exp & 1) res *= mult;
      mult *= mult;
      exp >>= 1;
    }
    return res;
  }

  modular operator + (const modular &rhs) const { return modular(*this) += rhs; }
  modular& operator += (const modular &rhs) { 
    if ((value += rhs.value) >= mod()) value -= mod(); 
    return *this; 
  }

  modular operator - (const modular &rhs) const { return modular(*this) -= rhs; }
  modular& operator -= (const modular &rhs) { 
    if ((value += mod() - rhs.value) >= mod()) value -= mod(); 
    return *this; 
  }

  modular operator * (const modular &rhs) const { return modular(*this) *= rhs; }
  modular& operator *= (const modular &rhs) { 
    value = (max_type) value * rhs.value % mod();
    return *this;
  }

  modular operator / (const modular &rhs) const { return modular(*this) /= rhs; }
  modular& operator /= (const modular &rhs) { return (*this) *= rhs.inverse(); }

  bool zero() const { return value == 0; }
  bool operator == (const modular &rhs) const { return value == rhs.value; }
  bool operator != (const modular &rhs) const { return value != rhs.value; }
  friend std::ostream& operator << (std::ostream &stream, const modular &rhs) {
    return stream << rhs.value;
  }

};

struct modulus_type { static inline uint32_t value; };
using m32 = modular<modulus_type>;
