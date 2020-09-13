#pragma once

#include <cstdint>
#include <type_traits>
#include <limits>

template <class T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
constexpr T isqrt(const T x) {
  T ok = 0, ng = std::numeric_limits<T>::max();
  while (ng - ok > 1) {
    const T md = ok + ((ng - ok) >> 1);
    (md > x / md ? ng : ok) = md;
  }
  return ok;
}

template <class T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
constexpr T ipower(T x, uint64_t e) {
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