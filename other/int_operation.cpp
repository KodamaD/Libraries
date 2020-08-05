#pragma once

#include <cstdint>
#include <type_traits>
#include <limits>

template <class T>
constexpr typename std::make_unsigned<T>::type negation_impl(const T x) {
  using unsigned_type = typename std::make_unsigned<T>::type;
  if (x == std::numeric_limits<T>::min()) {
    return static_cast<unsigned_type>(x);
  }
  return static_cast<unsigned_type>(-x);
}

template <class T>
constexpr typename std::enable_if<std::is_unsigned<T>::value && std::is_integral<T>::value, bool>::type
mul_overflow(const T x, const T y, const T z) {
  if (x == 0 || y == 0) return false;
  return x > z / y;
}

template <class T>
constexpr typename std::enable_if<std::is_signed<T>::value && std::is_integral<T>::value, bool>::type
mul_overflow(const T x, const T y, const T z) {
  if (x == 0 || y == 0) return z < 0;
  using unsigned_type = typename std::make_unsigned<T>::type;
  if (x > 0 && y > 0) {
    if (z <= 0) return true;
    return mul_overflow<unsigned_type>(x, y, z);
  }
  if (x > 0) {
    if (z >= 0) return false;
    return mul_overflow<unsigned_type>(x, negation_impl(y), negation_impl(z));
  }
  if (y > 0) {
    if (z >= 0) return false;
    return mul_overflow<unsigned_type>(negation_impl(x), y, negation_impl(z));
  }
  return mul_overflow<unsigned_type>(negation_impl(x), negation_impl(y), z);
}

template <class T>
constexpr typename std::enable_if<std::is_integral<T>::value, T>::type
isqrt(T x) {
  T ok = 0, ng = std::numeric_limits<T>::max();
  while (ng - ok > 1) {
    const T md = ok + ((ng - ok) >> 1);
    (mul_overflow(md, md, x) ? ng : ok) = md;
  }
  return ok;
}

template <class T>
constexpr typename std::enable_if<std::is_integral<T>::value, T>::type
ipower(T x, uint64_t e) {
  T res = 1;
  while (e > 0) {
    if (e & 1) res *= x;
    e >>= 1;
    if (e > 0) x *= x;
  }
  return res;
}

/**
 * @title Integer Operations
 */