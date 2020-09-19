#pragma once

#include <utility>
#include <cstdint>

constexpr std::pair<int64_t, int64_t> ext_gcd(int64_t a, int64_t b) {
  if ((a %= b) == 0) return { b, 0 };
  int64_t s = b, t = (a < 0 ? a + b : a);
  int64_t m0 = 0, m1 = 1;
  while (t > 0) {
    const auto u = s / t;
    s -= t * u; m0 -= m1 * u;
    std::swap(s, t); std::swap(m0, m1);
  }
  return { s, (m0 < 0 ? m0 + b / s : m0) };
}

/**
 * @title Extended GCD
 */