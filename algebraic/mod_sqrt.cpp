#pragma once

#include "../other/random_number.cpp"

#include <cstdint>

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

/**
 * @title Sqrt Mod
 */