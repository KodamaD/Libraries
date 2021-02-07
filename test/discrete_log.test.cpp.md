---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algebraic/mod_inv.cpp
    title: Extended GCD
  - icon: ':heavy_check_mark:'
    path: algebraic/mod_log.cpp
    title: Discrete Logarithm
  - icon: ':heavy_check_mark:'
    path: algebraic/modular.cpp
    title: Modint
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/discrete_logarithm_mod
    links:
    - https://judge.yosupo.jp/problem/discrete_logarithm_mod
  bundledCode: "#line 1 \"test/discrete_log.test.cpp\"\n\n#define PROBLEM \"https://judge.yosupo.jp/problem/discrete_logarithm_mod\"\
    \n\n#line 2 \"algebraic/modular.cpp\"\n\n#line 2 \"algebraic/mod_inv.cpp\"\n\n\
    #include <utility>\n#include <cstdint>\n\nconstexpr std::pair<int64_t, int64_t>\
    \ mod_inv(int64_t a, int64_t b) {\n  if ((a %= b) == 0) return { b, 0 };\n  int64_t\
    \ s = b, t = (a < 0 ? a + b : a);\n  int64_t m0 = 0, m1 = 1, tmp = 0;\n  while\
    \ (t > 0) {\n    const auto u = s / t;\n    s -= t * u; m0 -= m1 * u;\n    tmp\
    \ = s; s = t; t = tmp; tmp = m0; m0 = m1; m1 = tmp;\n  }\n  return { s, (m0 <\
    \ 0 ? m0 + b / s : m0) };\n}\n\n/**\n * @title Extended GCD\n */\n#line 4 \"algebraic/modular.cpp\"\
    \n\n#line 6 \"algebraic/modular.cpp\"\n#include <iostream>\n#include <cassert>\n\
    #include <type_traits>\n\ntemplate <class Modulus>\nclass modular {\npublic:\n\
    \  using value_type = uint32_t;\n  using cover_type = uint64_t;\n \n  static constexpr\
    \ uint32_t mod() { return Modulus::mod(); }\n  template <class T>\n  static constexpr\
    \ value_type normalize(T value_) noexcept {\n    if (value_ < 0) {\n      value_\
    \ = -value_;\n      value_ %= mod();\n      if (value_ == 0) return 0;\n     \
    \ return mod() - value_;\n    }\n    return value_ % mod();\n  }\n\nprivate:\n\
    \  value_type value;\n\n  template <bool IsPrime, std::enable_if_t<IsPrime>* =\
    \ nullptr>\n  constexpr modular inverse_helper() const noexcept { return power(*this,\
    \ mod() - 2); }\n  template <bool IsPrime, std::enable_if_t<!IsPrime>* = nullptr>\n\
    \  constexpr modular inverse_helper() const noexcept {\n    const auto tmp = mod_inv(value,\
    \ mod());\n    assert(tmp.first == 1);\n    return modular(tmp.second);\n  }\n\
    \npublic:\n  constexpr modular() noexcept : value(0) { }\n  template <class T>\n\
    \  explicit constexpr modular(T value_) noexcept : value(normalize(value_)) {\
    \ }\n  template <class T>\n  explicit constexpr operator T() const noexcept {\
    \ return static_cast<T>(value); }\n \n  constexpr value_type get() const noexcept\
    \ { return value; }\n  constexpr value_type &extract() noexcept { return value;\
    \ }\n  constexpr modular operator - () const noexcept { return modular(mod() -\
    \ value); }\n  constexpr modular operator ~ () const noexcept { return inverse(*this);\
    \ }\n \n  constexpr modular operator + (const modular &rhs) const noexcept { return\
    \ modular(*this) += rhs; }\n  constexpr modular& operator += (const modular &rhs)\
    \ noexcept { \n    if ((value += rhs.value) >= mod()) value -= mod(); \n    return\
    \ *this; \n  }\n \n  constexpr modular operator - (const modular &rhs) const noexcept\
    \ { return modular(*this) -= rhs; }\n  constexpr modular& operator -= (const modular\
    \ &rhs) noexcept { \n    if ((value += mod() - rhs.value) >= mod()) value -= mod();\
    \ \n    return *this; \n  }\n \n  constexpr modular operator * (const modular\
    \ &rhs) const noexcept { return modular(*this) *= rhs; }\n  constexpr modular&\
    \ operator *= (const modular &rhs) noexcept { \n    value = (cover_type) value\
    \ * rhs.value % mod();\n    return *this;\n  }\n \n  constexpr modular operator\
    \ / (const modular &rhs) const noexcept { return modular(*this) /= rhs; }\n  constexpr\
    \ modular& operator /= (const modular &rhs) noexcept { return (*this) *= inverse(rhs);\
    \ }\n \n  constexpr bool zero() const noexcept { return value == 0; }\n  constexpr\
    \ bool operator == (const modular &rhs) const noexcept { return value == rhs.value;\
    \ }\n  constexpr bool operator != (const modular &rhs) const noexcept { return\
    \ value != rhs.value; }\n \n  friend std::ostream& operator << (std::ostream &stream,\
    \ const modular &rhs) { return stream << rhs.value; }\n  friend constexpr modular\
    \ inverse(const modular &val) noexcept { return val.inverse_helper<Modulus::is_prime>();\
    \ }\n  friend constexpr modular power(modular val, cover_type exp) noexcept {\
    \ \n    modular res(1);\n    for (; exp > 0; exp >>= 1, val *= val) if (exp &\
    \ 1) res *= val;\n    return res;\n  }\n \n};\n \ntemplate <uint32_t Mod, bool\
    \ IsPrime = true>\nstruct static_modulus { \n  static constexpr uint32_t mod()\
    \ noexcept { return Mod; } \n  static constexpr bool is_prime = IsPrime;\n};\n\
    \ntemplate <uint32_t Id = 0, bool IsPrime = false>\nstruct dynamic_modulus {\n\
    \  static uint32_t &mod() noexcept { static uint32_t val = 0; return val; }\n\
    \  static constexpr bool is_prime = IsPrime;\n};\n\ntemplate <uint32_t Mod, bool\
    \ IsPrime = true>\nusing mint32_t = modular<static_modulus<Mod, IsPrime>>;\nusing\
    \ rmint32_t = modular<dynamic_modulus<>>;\n\n/*\n * @title Modint\n */\n#line\
    \ 2 \"algebraic/mod_log.cpp\"\n\n#line 4 \"algebraic/mod_log.cpp\"\n#include <unordered_map>\n\
    \ntemplate <class Modular>\nuint64_t log(const Modular x, const Modular y) {\n\
    \  static const auto gcd = [&](uint64_t a, uint64_t b) {\n    while (b != 0) std::swap(a\
    \ %= b, b);\n    return a;\n  };\n  const auto mod = Modular::mod();\n  const\
    \ uint64_t base = uint64_t(x);\n  uint64_t anti = uint64_t(y);\n  uint64_t g =\
    \ 1;\n  for (uint64_t m = mod; m > 0; m >>= 1) (g *= base) %= mod;\n  g = gcd(g,\
    \ mod);\n  uint64_t c = 0, t = 1;\n  while (t % g != 0) {\n    if (t == anti)\
    \ return c;\n    (t *= base) %= mod;\n    ++c;\n  }\n  if (anti % g != 0) return\
    \ mod;\n  t /= g, anti /= g;\n  const uint64_t n = mod / g;\n  uint64_t h = 0,\
    \ gs = 1;\n  while (h * h < n) (gs *= base) %= n, ++h;\n  std::unordered_map<uint64_t,\
    \ uint64_t> bs;\n  uint64_t s = 0, e = anti;\n  while (s < h) {\n    (e *= base)\
    \ %= n;\n    bs[e] = ++s;\n  }\n  s = 0, e = t;\n  while (s < n) {\n    (e *=\
    \ gs) %= n;\n    s += h;\n    if (bs.count(e)) return c + s - bs[e];\n  }\n  return\
    \ mod;\n}\n\n/**\n * @title Discrete Logarithm\n */\n#line 6 \"test/discrete_log.test.cpp\"\
    \n\n#include <cstddef>\n#line 10 \"test/discrete_log.test.cpp\"\n\nint main()\
    \ {\n  size_t Q;\n  std::cin >> Q;\n  while (Q--) {\n    uint32_t x, y;\n    std::cin\
    \ >> x >> y >> dynamic_modulus<>::mod();\n    const auto ans = log(rmint32_t(x),\
    \ rmint32_t(y));\n    if (ans == dynamic_modulus<>::mod()) {\n      std::cout\
    \ << \"-1\\n\";\n    }\n    else {\n      std::cout << ans << '\\n';\n    }\n\
    \  }\n  return 0;\n}\n"
  code: "\n#define PROBLEM \"https://judge.yosupo.jp/problem/discrete_logarithm_mod\"\
    \n\n#include \"../algebraic/modular.cpp\"\n#include \"../algebraic/mod_log.cpp\"\
    \n\n#include <cstddef>\n#include <cstdint>\n#include <iostream>\n\nint main()\
    \ {\n  size_t Q;\n  std::cin >> Q;\n  while (Q--) {\n    uint32_t x, y;\n    std::cin\
    \ >> x >> y >> dynamic_modulus<>::mod();\n    const auto ans = log(rmint32_t(x),\
    \ rmint32_t(y));\n    if (ans == dynamic_modulus<>::mod()) {\n      std::cout\
    \ << \"-1\\n\";\n    }\n    else {\n      std::cout << ans << '\\n';\n    }\n\
    \  }\n  return 0;\n}\n"
  dependsOn:
  - algebraic/modular.cpp
  - algebraic/mod_inv.cpp
  - algebraic/mod_log.cpp
  isVerificationFile: true
  path: test/discrete_log.test.cpp
  requiredBy: []
  timestamp: '2020-09-27 11:10:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/discrete_log.test.cpp
layout: document
redirect_from:
- /verify/test/discrete_log.test.cpp
- /verify/test/discrete_log.test.cpp.html
title: test/discrete_log.test.cpp
---
