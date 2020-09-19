#pragma once

#include <utility>
#include <cstdint>

constexpr std::pair<int64_t, int64_t> ext_gcd(int64_t a, int64_t b) {
  if ((a %= b) == 0) return { b, 0 };
  int64_t s = b, t = (a < 0 ? a + b : a);
  int64_t m0 = 0, m1 = 1, tmp = 0;
  while (t > 0) {
    const auto u = s / t;
    s -= t * u; m0 -= m1 * u;
    tmp = s; s = t; t = tmp; tmp = m0; m0 = m1; m1 = tmp;
  }
  return { s, (m0 < 0 ? m0 + b / s : m0) };
}

/**
 * @title Extended GCD
 */