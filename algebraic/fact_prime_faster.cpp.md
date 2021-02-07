---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/fix_point.cpp
    title: Lambda Recursion
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/enumerate_divisors_faster.test.cpp
    title: test/enumerate_divisors_faster.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/enumerate_factors_faster.test.cpp
    title: test/enumerate_factors_faster.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Fast Factorization
    links: []
  bundledCode: "#line 2 \"algebraic/fact_prime_faster.cpp\"\n\n#line 2 \"other/fix_point.cpp\"\
    \n\n#include <utility>\n\ntemplate <class Func>\nstruct fix_point_impl: private\
    \ Func {\n  explicit constexpr fix_point_impl(Func &&func): Func(std::forward<Func>(func))\
    \ { }\n  template <class... Args>\n  constexpr decltype(auto) operator () (Args\
    \ &&... args) const {\n    return Func::operator()(*this, std::forward<Args>(args)...);\n\
    \  }\n};\n\ntemplate <class Func>\nconstexpr decltype(auto) fix_point(Func &&func)\
    \ {\n  return fix_point_impl<Func>(std::forward<Func>(func));\n}\n\n/**\n * @title\
    \ Lambda Recursion\n */\n#line 4 \"algebraic/fact_prime_faster.cpp\"\n\n#include\
    \ <cstddef>\n#include <cstdint>\n#line 8 \"algebraic/fact_prime_faster.cpp\"\n\
    #include <vector>\n#include <algorithm>\n#include <cassert>\n\nnamespace fact_prime_detail\
    \ {\n\nclass mint64_t {\npublic:\n  static uint64_t mod;\n\n  static void set_mod(uint64_t\
    \ x) {\n    assert((x & 1));\n    mod = x;\n    encode = -__uint128_t(mod) % mod;\n\
    \    decode = [] {\n      uint64_t res = 0, cur = 0;\n      for (size_t i = 0;\
    \ i < 64; ++i) {\n        if (!(cur & 1)) { res += uint64_t(1) << i; cur += mod;\
    \ }\n        cur >>= 1;\n      }\n      return res;\n    }();\n  }\n\nprivate:\n\
    \  static uint64_t encode;\n  static uint64_t decode;\n\n  static uint64_t reduce(__uint128_t\
    \ x) {\n    uint64_t res = uint64_t((__uint128_t(uint64_t(x) * decode) * mod +\
    \ x) >> 64);\n    return res >= mod ? res - mod : res;\n  }\n\n  uint64_t value;\n\
    \npublic:\n  mint64_t(): value(0) { }\n  explicit mint64_t(uint64_t x): value(reduce((__uint128_t)\
    \ x * encode)) { }\n\n  uint64_t get() const {\n    uint64_t res = reduce(value);\n\
    \    return res >= mod ? res - mod : res;\n  }\n\n  mint64_t power(uint64_t exp)\
    \ const {\n    mint64_t res(1), mult(*this);\n    while (exp > 0) {\n      if\
    \ (exp & 1) res *= mult;\n      mult *= mult;\n      exp >>= 1;\n    }\n    return\
    \ res;\n  }\n\n  mint64_t operator + (const mint64_t &rhs) const { return mint64_t(*this)\
    \ += rhs; }\n  mint64_t& operator += (const mint64_t &rhs) { \n    if ((value\
    \ += rhs.value) >= mod) value -= mod;\n    return *this; \n  }\n  mint64_t operator\
    \ * (const mint64_t &rhs) const { return mint64_t(*this) *= rhs; }\n  mint64_t&\
    \ operator *= (const mint64_t &rhs) { \n    value = reduce((__uint128_t) value\
    \ * rhs.value);\n    return *this;\n  }\n  bool operator == (const mint64_t &rhs)\
    \ const { return value == rhs.value; }\n  bool operator != (const mint64_t &rhs)\
    \ const { return value != rhs.value; }\n\n};\n\nuint64_t mint64_t::mod;\nuint64_t\
    \ mint64_t::encode;\nuint64_t mint64_t::decode;\n\nuint64_t gcd64(uint64_t a,\
    \ uint64_t b) {\n  if (a == 0) return b;\n  if (b == 0) return a;\n  if (a < b)\
    \ std::swap(a, b);\n  while (uint64_t r = a % b) a = b, b = r;\n  return b;\n\
    }\n\nbool test_prime(uint64_t a, uint64_t s, uint64_t d, uint64_t n) {\n  mint64_t::set_mod(n);\n\
    \  mint64_t cur = mint64_t(a).power(d);\n  if (cur == mint64_t(1)) return true;\n\
    \  mint64_t bad(n - 1);\n  for (size_t i = 0; i < s; ++i) {\n    if (cur == bad)\
    \ return true;\n    cur *= cur;\n  }\n  return false;\n}\n\ntemplate <class T>\n\
    bool miller_rabin(T n) {\n  if (n <= 1) return false;\n  if (n == 2) return true;\n\
    \  if (!(n & 1)) return false;\n  uint64_t d = n - 1, s = 0;\n  while (!(d & 1))\
    \ { d >>= 1; ++s; }\n  if (n < 4759123141) {\n    for (auto p: { 2, 7, 61 }) {\n\
    \      if (p >= n) break;\n      if (!test_prime(p, s, d, n)) return false;\n\
    \    }\n  } \n  else {\n    for (auto p: { 2, 325, 9375, 28178, 450775, 9780504,\
    \ 1795265022 }) {\n      if (p >= n) break;\n      if (!test_prime(p, s, d, n))\
    \ return false;\n    }\n  }\n  return true;\n}\n\ntemplate <class T>\nT pollard_rho(T\
    \ n) {\n  if (!(n & 1)) return 2;\n  mint64_t::set_mod(n);\n  mint64_t add(1);\n\
    \  const auto transit = [&add](mint64_t m) { return m * m + add; };\n  const auto\
    \ dif_abs = [](uint64_t x, uint64_t y) { return x > y ? x - y : y - x; };\n  uint64_t\
    \ initial = 0;\n  while (true) {\n    ++initial;\n    mint64_t x(initial);\n \
    \   mint64_t y = transit(x);\n    while (true) {\n      uint64_t g = fact_prime_detail::gcd64(dif_abs(x.get(),\
    \ y.get()), n);\n      if (g == 1) {\n        x = transit(x);\n        y = transit(transit(y));\n\
    \        continue;\n      }\n      if (g == n) break;\n      return g;\n    }\n\
    \  }\n}\n\n};\n\ntemplate <class T>\nbool is_prime(T x) {\n  return fact_prime_detail::miller_rabin(x);\n\
    }\n\ntemplate <class T>\nstd::vector<T> enumerate_factors(T n, bool sort = true)\
    \ {\n  assert(n >= 1);\n  if (n == 1) return { };\n  if (is_prime(n)) return {\
    \ n };\n  T d = fact_prime_detail::pollard_rho(n);\n  auto res = enumerate_factors(d);\n\
    \  auto add = enumerate_factors(n / d);\n  size_t size = res.size();\n  res.resize(size\
    \ + add.size());\n  std::copy(add.cbegin(), add.cend(), res.begin() + size);\n\
    \  if (sort) std::inplace_merge(res.begin(), res.begin() + size, res.end());\n\
    \  return res;\n}\n\ntemplate <class T>\nstd::vector<std::pair<T, size_t>> factorize(T\
    \ n) {\n  assert(n >= 1);\n  std::vector<std::pair<T, size_t>> res;\n  T cur =\
    \ 0;\n  for (auto p: enumerate_factors(n)) {\n    if (p != cur) {\n      cur =\
    \ p;\n      res.emplace_back(p, 0);\n    }\n    ++res.back().second;\n  }\n  return\
    \ res;\n}\n\ntemplate <class T>\nstd::vector<T> enumerate_divisors(T n, bool sort\
    \ = true) {\n  assert(n >= 1);\n  auto factors = factorize(n);\n  std::vector<T>\
    \ res;\n  size_t size = 1;\n  for (auto [p, e]: factors) {\n    size *= (e + 1);\n\
    \  }\n  res.reserve(size);\n  fix_point([&](auto dfs, size_t i, T x) -> void {\n\
    \    if (i == factors.size()) {\n      res.push_back(x);\n      return;\n    }\n\
    \    dfs(i + 1, x);\n    auto [p, e] = factors[i];\n    for (size_t j = 1; j <=\
    \ e; ++j) {\n      x *= p;\n      dfs(i + 1, x);\n    }\n  })(0, 1);\n  if (sort)\
    \ std::sort(res.begin(), res.end());\n  return res;\n}\n\n/**\n * @title Fast\
    \ Factorization\n */\n"
  code: "#pragma once\n\n#include \"../other/fix_point.cpp\"\n\n#include <cstddef>\n\
    #include <cstdint>\n#include <utility>\n#include <vector>\n#include <algorithm>\n\
    #include <cassert>\n\nnamespace fact_prime_detail {\n\nclass mint64_t {\npublic:\n\
    \  static uint64_t mod;\n\n  static void set_mod(uint64_t x) {\n    assert((x\
    \ & 1));\n    mod = x;\n    encode = -__uint128_t(mod) % mod;\n    decode = []\
    \ {\n      uint64_t res = 0, cur = 0;\n      for (size_t i = 0; i < 64; ++i) {\n\
    \        if (!(cur & 1)) { res += uint64_t(1) << i; cur += mod; }\n        cur\
    \ >>= 1;\n      }\n      return res;\n    }();\n  }\n\nprivate:\n  static uint64_t\
    \ encode;\n  static uint64_t decode;\n\n  static uint64_t reduce(__uint128_t x)\
    \ {\n    uint64_t res = uint64_t((__uint128_t(uint64_t(x) * decode) * mod + x)\
    \ >> 64);\n    return res >= mod ? res - mod : res;\n  }\n\n  uint64_t value;\n\
    \npublic:\n  mint64_t(): value(0) { }\n  explicit mint64_t(uint64_t x): value(reduce((__uint128_t)\
    \ x * encode)) { }\n\n  uint64_t get() const {\n    uint64_t res = reduce(value);\n\
    \    return res >= mod ? res - mod : res;\n  }\n\n  mint64_t power(uint64_t exp)\
    \ const {\n    mint64_t res(1), mult(*this);\n    while (exp > 0) {\n      if\
    \ (exp & 1) res *= mult;\n      mult *= mult;\n      exp >>= 1;\n    }\n    return\
    \ res;\n  }\n\n  mint64_t operator + (const mint64_t &rhs) const { return mint64_t(*this)\
    \ += rhs; }\n  mint64_t& operator += (const mint64_t &rhs) { \n    if ((value\
    \ += rhs.value) >= mod) value -= mod;\n    return *this; \n  }\n  mint64_t operator\
    \ * (const mint64_t &rhs) const { return mint64_t(*this) *= rhs; }\n  mint64_t&\
    \ operator *= (const mint64_t &rhs) { \n    value = reduce((__uint128_t) value\
    \ * rhs.value);\n    return *this;\n  }\n  bool operator == (const mint64_t &rhs)\
    \ const { return value == rhs.value; }\n  bool operator != (const mint64_t &rhs)\
    \ const { return value != rhs.value; }\n\n};\n\nuint64_t mint64_t::mod;\nuint64_t\
    \ mint64_t::encode;\nuint64_t mint64_t::decode;\n\nuint64_t gcd64(uint64_t a,\
    \ uint64_t b) {\n  if (a == 0) return b;\n  if (b == 0) return a;\n  if (a < b)\
    \ std::swap(a, b);\n  while (uint64_t r = a % b) a = b, b = r;\n  return b;\n\
    }\n\nbool test_prime(uint64_t a, uint64_t s, uint64_t d, uint64_t n) {\n  mint64_t::set_mod(n);\n\
    \  mint64_t cur = mint64_t(a).power(d);\n  if (cur == mint64_t(1)) return true;\n\
    \  mint64_t bad(n - 1);\n  for (size_t i = 0; i < s; ++i) {\n    if (cur == bad)\
    \ return true;\n    cur *= cur;\n  }\n  return false;\n}\n\ntemplate <class T>\n\
    bool miller_rabin(T n) {\n  if (n <= 1) return false;\n  if (n == 2) return true;\n\
    \  if (!(n & 1)) return false;\n  uint64_t d = n - 1, s = 0;\n  while (!(d & 1))\
    \ { d >>= 1; ++s; }\n  if (n < 4759123141) {\n    for (auto p: { 2, 7, 61 }) {\n\
    \      if (p >= n) break;\n      if (!test_prime(p, s, d, n)) return false;\n\
    \    }\n  } \n  else {\n    for (auto p: { 2, 325, 9375, 28178, 450775, 9780504,\
    \ 1795265022 }) {\n      if (p >= n) break;\n      if (!test_prime(p, s, d, n))\
    \ return false;\n    }\n  }\n  return true;\n}\n\ntemplate <class T>\nT pollard_rho(T\
    \ n) {\n  if (!(n & 1)) return 2;\n  mint64_t::set_mod(n);\n  mint64_t add(1);\n\
    \  const auto transit = [&add](mint64_t m) { return m * m + add; };\n  const auto\
    \ dif_abs = [](uint64_t x, uint64_t y) { return x > y ? x - y : y - x; };\n  uint64_t\
    \ initial = 0;\n  while (true) {\n    ++initial;\n    mint64_t x(initial);\n \
    \   mint64_t y = transit(x);\n    while (true) {\n      uint64_t g = fact_prime_detail::gcd64(dif_abs(x.get(),\
    \ y.get()), n);\n      if (g == 1) {\n        x = transit(x);\n        y = transit(transit(y));\n\
    \        continue;\n      }\n      if (g == n) break;\n      return g;\n    }\n\
    \  }\n}\n\n};\n\ntemplate <class T>\nbool is_prime(T x) {\n  return fact_prime_detail::miller_rabin(x);\n\
    }\n\ntemplate <class T>\nstd::vector<T> enumerate_factors(T n, bool sort = true)\
    \ {\n  assert(n >= 1);\n  if (n == 1) return { };\n  if (is_prime(n)) return {\
    \ n };\n  T d = fact_prime_detail::pollard_rho(n);\n  auto res = enumerate_factors(d);\n\
    \  auto add = enumerate_factors(n / d);\n  size_t size = res.size();\n  res.resize(size\
    \ + add.size());\n  std::copy(add.cbegin(), add.cend(), res.begin() + size);\n\
    \  if (sort) std::inplace_merge(res.begin(), res.begin() + size, res.end());\n\
    \  return res;\n}\n\ntemplate <class T>\nstd::vector<std::pair<T, size_t>> factorize(T\
    \ n) {\n  assert(n >= 1);\n  std::vector<std::pair<T, size_t>> res;\n  T cur =\
    \ 0;\n  for (auto p: enumerate_factors(n)) {\n    if (p != cur) {\n      cur =\
    \ p;\n      res.emplace_back(p, 0);\n    }\n    ++res.back().second;\n  }\n  return\
    \ res;\n}\n\ntemplate <class T>\nstd::vector<T> enumerate_divisors(T n, bool sort\
    \ = true) {\n  assert(n >= 1);\n  auto factors = factorize(n);\n  std::vector<T>\
    \ res;\n  size_t size = 1;\n  for (auto [p, e]: factors) {\n    size *= (e + 1);\n\
    \  }\n  res.reserve(size);\n  fix_point([&](auto dfs, size_t i, T x) -> void {\n\
    \    if (i == factors.size()) {\n      res.push_back(x);\n      return;\n    }\n\
    \    dfs(i + 1, x);\n    auto [p, e] = factors[i];\n    for (size_t j = 1; j <=\
    \ e; ++j) {\n      x *= p;\n      dfs(i + 1, x);\n    }\n  })(0, 1);\n  if (sort)\
    \ std::sort(res.begin(), res.end());\n  return res;\n}\n\n/**\n * @title Fast\
    \ Factorization\n */"
  dependsOn:
  - other/fix_point.cpp
  isVerificationFile: false
  path: algebraic/fact_prime_faster.cpp
  requiredBy: []
  timestamp: '2020-09-13 16:51:07+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/enumerate_factors_faster.test.cpp
  - test/enumerate_divisors_faster.test.cpp
documentation_of: algebraic/fact_prime_faster.cpp
layout: document
redirect_from:
- /library/algebraic/fact_prime_faster.cpp
- /library/algebraic/fact_prime_faster.cpp.html
title: Fast Factorization
---
