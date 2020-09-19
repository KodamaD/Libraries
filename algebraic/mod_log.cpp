#pragma once

#include <cstdint>
#include <unordered_map>

template <class Modular>
uint64_t log(const Modular x, const Modular y) {
  static const auto gcd = [&](uint64_t a, uint64_t b) {
    while (b != 0) std::swap(a %= b, b);
    return a;
  };
  const auto mod = Modular::mod();
  const uint64_t base = uint64_t(x);
  uint64_t anti = uint64_t(y);
  uint64_t g = 1;
  for (uint64_t m = mod; m > 0; m >>= 1) (g *= base) %= mod;
  g = gcd(g, mod);
  uint64_t c = 0, t = 1;
  while (t % g != 0) {
    if (t == anti) return c;
    (t *= base) %= mod;
    ++c;
  }
  if (anti % g != 0) return mod;
  t /= g, anti /= g;
  const uint64_t n = mod / g;
  uint64_t h = 0, gs = 1;
  while (h * h < n) (gs *= base) %= n, ++h;
  std::unordered_map<uint64_t, uint64_t> bs;
  uint64_t s = 0, e = anti;
  while (s < h) {
    (e *= base) %= n;
    bs[e] = ++s;
  }
  s = 0, e = t;
  while (s < n) {
    (e *= gs) %= n;
    s += h;
    if (bs.count(e)) return c + s - bs[e];
  }
  return mod;
}

/**
 * @title Discrete Logarithm
 */