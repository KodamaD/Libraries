#pragma once

#include "../other/random_number.cpp"

#include <cstdint>
#include <unordered_map>

template <class Modular>
Modular sqrt(const Modular value) {
  if (value == Modular(0)) return value;
  const auto mod = Modular::mod();
  if (mod == 2) return value;
  if (power(value, (mod - 1) >> 1) != Modular(1)) return Modular(0);
  if (mod % 4 == 3) return power(value, (mod + 1) >> 2);
  if (mod % 8 == 5) {
    if (power(value, (mod - 1) >> 2) == Modular(1)) return power(value, (mod + 3) >> 3);
    else return power(Modular(2), (mod - 1) >> 2) * power(value, (mod + 3) >> 3);
  }
  Modular f0, f1(1), g0(1), g1, D, tmp;
  while (true) {
    f0.extract() = random_number<uint32_t>(2, mod - 1);
    D = f0 * f0 - value;
    if (D == Modular(0)) return f0;
    if (power(D, (mod - 1) >> 1) == Modular(-1)) break;
  }
  for (uint32_t exp = (mod + 1) >> 1; exp > 0; exp >>= 1) {
    if (exp & 1) {
      tmp = g0 * f0 + D * (g1 * f1);
      g1 = g0 * f1 + g1 * f0;
      g0 = tmp;
    }
    tmp = f0 * f0 + D * (f1 * f1);
    f1 = Modular(2) * f0 * f1;
    f0 = tmp;
  }
  return g0;
}

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
 * @title Modular Operations
 */