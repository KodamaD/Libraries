#pragma once

#include <cstddef>
#include <array>
#include <cassert>

template <class T, size_t N>
class factorials {
public:
  using value_type = T;

public:
  std::array<value_type, N + 1> fact{};
  std::array<value_type, N + 1> fact_inv{};

  factorials() {
    fact.front() = value_type(1);
    for (size_t i = 1; i <= N; ++i) {
      fact[i] = fact[i - 1] * value_type(i);
    }
    fact_inv.back() = ~fact.back();
    for (size_t i = N; i > 0; --i) {
      fact_inv[i - 1] = fact_inv[i] * value_type(i);
    }
  }

  value_type operator () (size_t n, size_t r) const {
    assert(n <= N);
    assert(n >= r);
    return fact[n] * fact_inv[n - r] * fact_inv[r];
  }
};

/**
 * @title Factorial
 */