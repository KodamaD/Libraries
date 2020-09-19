#pragma once

#include "../algebraic/ext_gcd.cpp"

#include <cstdint>
#include <iostream>
#include <cassert>
#include <type_traits>

template <class Modulus>
class modular {
public:
  using value_type = uint32_t;
  using cover_type = uint64_t;
 
  template <class T>
  static constexpr value_type normalize(T value_) noexcept {
    if (value_ < 0) {
      value_ = -value_;
      value_ %= Modulus::mod();
      if (value_ == 0) return 0;
      return Modulus::mod() - value_;
    }
    return value_ % Modulus::mod();
  }

private:
  value_type value;

  template <bool IsPrime, std::enable_if_t<IsPrime>* = nullptr>
  constexpr modular inverse_helper() const noexcept { return power(*this, Modulus::mod() - 2); }
  template <bool IsPrime, std::enable_if_t<!IsPrime>* = nullptr>
  constexpr modular inverse_helper() const noexcept {
    const auto tmp = ext_gcd(value, Modulus::mod());
    assert(tmp.first == 1);
    return modular(tmp.second);
  }

public:
  constexpr modular() noexcept : value(0) { }
  template <class T>
  explicit constexpr modular(T value_) noexcept : value(normalize(value_)) { }
  template <class T>
  explicit constexpr operator T() const noexcept { return static_cast<T>(value); }
 
  constexpr value_type get() const noexcept { return value; }
  constexpr value_type &extract() noexcept { return value; }
  constexpr modular operator - () const noexcept { return modular(Modulus::mod() - value); }
  constexpr modular operator ~ () const noexcept { return inverse(*this); }
 
  constexpr modular operator + (const modular &rhs) const noexcept { return modular(*this) += rhs; }
  constexpr modular& operator += (const modular &rhs) noexcept { 
    if ((value += rhs.value) >= Modulus::mod()) value -= Modulus::mod(); 
    return *this; 
  }
 
  constexpr modular operator - (const modular &rhs) const noexcept { return modular(*this) -= rhs; }
  constexpr modular& operator -= (const modular &rhs) noexcept { 
    if ((value += Modulus::mod() - rhs.value) >= Modulus::mod()) value -= Modulus::mod(); 
    return *this; 
  }
 
  constexpr modular operator * (const modular &rhs) const noexcept { return modular(*this) *= rhs; }
  constexpr modular& operator *= (const modular &rhs) noexcept { 
    value = (cover_type) value * rhs.value % Modulus::mod();
    return *this;
  }
 
  constexpr modular operator / (const modular &rhs) const noexcept { return modular(*this) /= rhs; }
  constexpr modular& operator /= (const modular &rhs) noexcept { return (*this) *= inverse(rhs); }
 
  constexpr bool zero() const noexcept { return value == 0; }
  constexpr bool operator == (const modular &rhs) const noexcept { return value == rhs.value; }
  constexpr bool operator != (const modular &rhs) const noexcept { return value != rhs.value; }
 
  friend std::ostream& operator << (std::ostream &stream, const modular &rhs) { return stream << rhs.value; }
  friend constexpr modular inverse(const modular &val) noexcept { return val.inverse_helper<Modulus::is_prime>(); }
  friend constexpr modular power(modular val, cover_type exp) noexcept { 
    modular res(1);
    for (; exp > 0; exp >>= 1, val *= val) if (exp & 1) res *= val;
    return res;
  }
 
};
 
template <uint32_t Mod, bool IsPrime = true>
struct static_modulus { 
  static constexpr uint32_t mod() noexcept { return Mod; } 
  static constexpr bool is_prime = IsPrime;
};

template <uint32_t Id = 0, bool IsPrime = false>
struct dynamic_modulus {
  static uint32_t &mod() noexcept { static uint32_t val = 0; return val; }
  static constexpr bool is_prime = IsPrime;
};

template <uint32_t Mod>
using mint32_t = modular<static_modulus<Mod>>;
using rmint32_t = modular<dynamic_modulus<>>;

/*
 * @title Modint
 */