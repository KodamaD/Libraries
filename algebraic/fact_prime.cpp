#pragma once

#include "../other/fix_point.cpp"
#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>
#include <algorithm>

namespace fact_prime_detail {

  class mod64 {
  public:
    static inline uint64_t mod;

    static void set_mod(uint64_t x) {
      mod = x;
      encode = -__uint128_t(mod) % mod;
      decode = [] {
        uint64_t res = 0, cur = 0;
        for (size_t i = 0; i < 64; ++i) {
          if (!(cur & 1)) { res += uint64_t(1) << i; cur += mod; }
          cur >>= 1;
        }
        return res;
      }();
    }

  private:
    static inline uint64_t encode;
    static inline uint64_t decode;

    static uint64_t reduce(__uint128_t x) {
      uint64_t res = uint64_t((__uint128_t(uint64_t(x) * decode) * mod + x) >> 64);
      return res >= mod ? res - mod : res;
    }

    uint64_t value;

  public:
    mod64(): value(0) { }
    explicit mod64(uint64_t x): value(reduce((__uint128_t) x * encode)) { }

    uint64_t get() const {
      uint64_t res = reduce(value);
      return res >= mod ? res - mod : res;
    }

    mod64 power(uint64_t exp) const {
      mod64 res(1), mult(*this);
      while (exp > 0) {
        if (exp & 1) res *= mult;
        mult *= mult;
        exp >>= 1;
      }
      return res;
    }

    mod64 operator + (const mod64 &rhs) const { return mod64(*this) += rhs; }
    mod64& operator += (const mod64 &rhs) { 
      if ((value += rhs.value) >= mod) value -= mod;
      return *this; 
    }
    mod64 operator * (const mod64 &rhs) const { return mod64(*this) *= rhs; }
    mod64& operator *= (const mod64 &rhs) { 
      value = reduce((__uint128_t) value * rhs.value);
      return *this;
    }
    bool operator == (const mod64 &rhs) const { return value == rhs.value; }
    bool operator != (const mod64 &rhs) const { return value != rhs.value; }

  };

  uint64_t gcd64(uint64_t a, uint64_t b) {
    if (a == 0) return b;
    if (b == 0) return a;
    if (a < b) std::swap(a, b);
    while (uint64_t r = a % b) a = b, b = r;
    return b;
  }

  bool test_prime(uint64_t a, uint64_t s, uint64_t d, uint64_t n) {
    mod64::set_mod(n);
    mod64 cur = mod64(a).power(d);
    if (cur == mod64(1)) return true;
    mod64 bad(n - 1);
    for (size_t i = 0; i < s; ++i) {
      if (cur == bad) return true;
      cur *= cur;
    }
    return false;
  }

  template <class T>
  bool miller_rabin(T n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (!(n & 1)) return false;
    uint64_t d = n - 1, s = 0;
    while (!(d & 1)) { d >>= 1; ++s; }
    if (n < 4759123141) {
      for (auto p: { 2, 7, 61 }) {
        if (p >= n) break;
        if (!test_prime(p, s, d, n)) return false;
      }
    } 
    else {
      for (auto p: { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 }) {
        if (p >= n) break;
        if (!test_prime(p, s, d, n)) return false;
      }
    }
    return true;
  }

  template <class T>
  T pollard_rho(T n) {
    if (!(n & 1)) return 2;
    mod64::set_mod(n);
    mod64 add(1);
    const auto transit = [&add](mod64 m) { return m * m + add; };
    const auto dif_abs = [](uint64_t x, uint64_t y) { return x > y ? x - y : y - x; };
    uint64_t initial = 0;
    while (true) {
      ++initial;
      mod64 x(initial);
      mod64 y = transit(x);
      while (true) {
        uint64_t g = fact_prime_detail::gcd64(dif_abs(x.get(), y.get()), n);
        if (g == 1) {
          x = transit(x);
          y = transit(transit(y));
          continue;
        }
        if (g == n) break;
        return g;
      }
    }
  }

};

template <class T>
bool is_prime(T x) {
  return fact_prime_detail::miller_rabin(x);
}

template <class T>
std::vector<T> enumerate_factors(T n, bool sort = true) {
  if (n == 1) return { };
  if (is_prime(n)) return { n };
  T d = fact_prime_detail::pollard_rho(n);
  auto res = enumerate_factors(d);
  auto add = enumerate_factors(n / d);
  size_t size = res.size();
  res.resize(size + add.size());
  std::copy(add.cbegin(), add.cend(), res.begin() + size);
  if (sort) std::inplace_merge(res.begin(), res.begin() + size, res.end());
  return res;
}

template <class T>
std::vector<std::pair<T, size_t>> factorize(T n) {
  std::vector<std::pair<T, size_t>> res;
  T cur = 0;
  for (auto p: enumerate_factors(n)) {
    if (p != cur) {
      cur = p;
      res.emplace_back(p, 0);
    }
    ++res.back().second;
  }
  return res;
}

template <class T>
std::vector<T> enumerate_divisors(T n, bool sort = true) {
  auto factors = factorize(n);
  std::vector<T> res;
  size_t size = 1;
  for (auto [p, e]: factors) {
    size *= (e + 1);
  }
  res.reserve(size);
  make_fix_point([&](auto dfs, size_t i, T x) -> void {
    if (i == factors.size()) {
      res.push_back(x);
      return;
    }
    dfs(i + 1, x);
    auto [p, e] = factors[i];
    for (size_t j = 1; j <= e; ++j) {
      x *= p;
      dfs(i + 1, x);
    }
  })(0, 1);
  if (sort) std::sort(res.begin(), res.end());
  return res;
}

/**
 * @title Primes/Factors
 */