#pragma once

#include <cstddef>
#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <type_traits>

template <class T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
std::vector<std::pair<T, size_t>> factorize(T x) {
  assert(x > 0);
  if (x == 1) return { };
  std::vector<std::pair<T, size_t>> res;
  for (T i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
      res.emplace_back(i, 0);
      while (x % i == 0) {
        res.back().second++;
        x /= i;
      }
    }
  }
  if (x > 1) {
    res.emplace_back(x, 1);
  }
  return res;
}

template <class T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
std::vector<T> divisors(const T x) {
  std::vector<T> small, big;
  for (T i = 1; i * i <= x; ++i) {
    if (x % i == 0) {
      small.push_back(i);
      if (i * i != x) {
        big.push_back(x / i);
      }
    }
  }
  small.reserve(small.size() + big.size());
  std::copy(big.rbegin(), big.rend(), std::back_inserter(small));
  return small;
}

/**
 * @title Factors/Divisors
 */