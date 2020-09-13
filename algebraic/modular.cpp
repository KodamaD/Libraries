#pragma once

#include <cstdint>
#include <iostream>

template <uint32_t Mod>
class static_modint {
public:
  using value_type = uint32_t;
  using cover_type = uint64_t;

  template <class T>
  static constexpr value_type normalize(T value_) noexcept {
    if (value_ < 0) {
      value_ = -value_;
      value_ %= Mod;
      if (value_ == 0) return 0;
      return Mod - value_;
    }
    return value_ % Mod;
  }

private:
  value_type value;

public:
  constexpr static_modint() noexcept : value(0) { }
  template <class T>
  explicit constexpr static_modint(T value_) noexcept : value(normalize(value_)) { }
  template <class T>
  explicit constexpr operator T() const noexcept { return static_cast<T>(value); }

  constexpr value_type get() const noexcept { return value; }
  constexpr value_type &extract() noexcept { return value; }
  constexpr static_modint operator - () const noexcept { return static_modint(Mod - value); }
  constexpr static_modint operator ~ () const noexcept { return inverse(*this); }

  constexpr static_modint operator + (const static_modint &rhs) const noexcept { return static_modint(*this) += rhs; }
  constexpr static_modint& operator += (const static_modint &rhs) noexcept { 
    if ((value += rhs.value) >= Mod) value -= Mod; 
    return *this; 
  }

  constexpr static_modint operator - (const static_modint &rhs) const noexcept { return static_modint(*this) -= rhs; }
  constexpr static_modint& operator -= (const static_modint &rhs) noexcept { 
    if ((value += Mod - rhs.value) >= Mod) value -= Mod; 
    return *this; 
  }

  constexpr static_modint operator * (const static_modint &rhs) const noexcept { return static_modint(*this) *= rhs; }
  constexpr static_modint& operator *= (const static_modint &rhs) noexcept { 
    value = (cover_type) value * rhs.value % Mod;
    return *this;
  }

  constexpr static_modint operator / (const static_modint &rhs) const noexcept { return static_modint(*this) /= rhs; }
  constexpr static_modint& operator /= (const static_modint &rhs) noexcept { return (*this) *= inverse(rhs); }

  constexpr bool zero() const noexcept { return value == 0; }
  constexpr bool operator == (const static_modint &rhs) const noexcept { return value == rhs.value; }
  constexpr bool operator != (const static_modint &rhs) const noexcept { return value != rhs.value; }

  friend std::ostream& operator << (std::ostream &stream, const static_modint &rhs) { return stream << rhs.value; }
  friend constexpr static_modint inverse(static_modint val) noexcept { return power(val, Mod - 2); }
  friend constexpr static_modint power(static_modint val, cover_type exp) noexcept { 
    static_modint res(1);
    for (; exp > 0; exp >>= 1, val *= val) if (exp & 1) res *= val;
    return res;
  }

};

template <uint32_t Mod>
using mint32_t = static_modint<Mod>;

/**
 * @title Static Modint
 */