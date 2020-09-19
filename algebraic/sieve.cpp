#pragma once

#include <cstddef>
#include <cstdint>
#include <array>
#include <vector>
#include <utility>
#include <cassert>
#include <numeric>
#include <type_traits>

template <size_t N>
class sieve {
private:
  std::array<uint32_t, N + 1> M_smallest;

public:
  sieve() {
    std::iota(M_smallest.begin(), M_smallest.end(), (uint32_t) 0);
    for (uint32_t i = 2; i <= N; ++i) {
      if (M_smallest[i] == i) {
        for (uint32_t j = i + i; j <= N; j += i) {
          if (M_smallest[j] == j) {
            M_smallest[j] = i;
          }
        }
      }
    }
  }

  template <class T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
  std::vector<std::pair<T, size_t>> factorize(T x) {
    assert(x > 0);
    assert((size_t) x <= N);
    std::vector<std::pair<T, size_t>> res;
    while (x != 1) {
      const auto cur = M_smallest[x];
      res.emplace_back((T) cur, 0);
      while (M_smallest[x] == cur) {
        res.back().second++;
        x /= cur;
      }
    }
    return res;
  }
  bool operator [] (const size_t n) const {
    if (n <= 1) return false;
    assert(n <= N);
    return (M_smallest[n] == (uint32_t) n);
  }
};

/**
 * @title Sieve of Eratosthenes
 */