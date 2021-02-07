---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algebraic/mod_inv.cpp
    title: Extended GCD
  - icon: ':heavy_check_mark:'
    path: algebraic/mod_sqrt.cpp
    title: Sqrt Mod
  - icon: ':heavy_check_mark:'
    path: algebraic/modular.cpp
    title: Modint
  - icon: ':heavy_check_mark:'
    path: other/random_number.cpp
    title: Random Number
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sqrt_mod
    links:
    - https://judge.yosupo.jp/problem/sqrt_mod
  bundledCode: "#line 1 \"test/sqrt_mod.test.cpp\"\n\n#define PROBLEM \"https://judge.yosupo.jp/problem/sqrt_mod\"\
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
    \ 2 \"algebraic/mod_sqrt.cpp\"\n\n#line 2 \"other/random_number.cpp\"\n\n#line\
    \ 4 \"other/random_number.cpp\"\n#include <random>\n#include <chrono>\n#include\
    \ <array>\n#line 8 \"other/random_number.cpp\"\n\nuint64_t engine() {\n  static\
    \ uint64_t result = static_cast<uint64_t>(std::chrono::system_clock::now().time_since_epoch().count());\n\
    \  result ^= result << 5;\n  result ^= result >> 13;\n  result ^= result << 7;\n\
    \  return result;\n}\n\ntemplate <class Integer>\ntypename std::enable_if<std::is_integral<Integer>::value,\
    \ Integer>::type random_number(Integer lower, Integer upper) {\n  static std::default_random_engine\
    \ gen(engine());\n  return std::uniform_int_distribution<Integer>(lower, upper)(gen);\n\
    }\n\ntemplate <class Real>\ntypename std::enable_if<!std::is_integral<Real>::value,\
    \ Real>::type random_number(Real lower, Real upper) {\n  static std::default_random_engine\
    \ gen(engine());\n  return std::uniform_real_distribution<Real>(lower, upper)(gen);\n\
    }\n\n/** \n * @title Random Number\n */\n#line 4 \"algebraic/mod_sqrt.cpp\"\n\n\
    #line 6 \"algebraic/mod_sqrt.cpp\"\n\ntemplate <class Modular>\nModular sqrt(const\
    \ Modular value) {\n  if (value == Modular(0)) return value;\n  const auto mod\
    \ = Modular::mod();\n  if (mod == 2) return value;\n  if (power(value, (mod -\
    \ 1) >> 1) != Modular(1)) return Modular(0);\n  if (mod % 4 == 3) return power(value,\
    \ (mod + 1) >> 2);\n  if (mod % 8 == 5) {\n    if (power(value, (mod - 1) >> 2)\
    \ == Modular(1)) return power(value, (mod + 3) >> 3);\n    else return power(Modular(2),\
    \ (mod - 1) >> 2) * power(value, (mod + 3) >> 3);\n  }\n  Modular f0, f1(1), g0(1),\
    \ g1, D, tmp;\n  while (true) {\n    f0.extract() = random_number<uint32_t>(2,\
    \ mod - 1);\n    D = f0 * f0 - value;\n    if (D == Modular(0)) return f0;\n \
    \   if (power(D, (mod - 1) >> 1) == Modular(-1)) break;\n  }\n  for (uint32_t\
    \ exp = (mod + 1) >> 1; exp > 0; exp >>= 1) {\n    if (exp & 1) {\n      tmp =\
    \ g0 * f0 + D * (g1 * f1);\n      g1 = g0 * f1 + g1 * f0;\n      g0 = tmp;\n \
    \   }\n    tmp = f0 * f0 + D * (f1 * f1);\n    f1 = Modular(2) * f0 * f1;\n  \
    \  f0 = tmp;\n  }\n  return g0;\n}\n\n/**\n * @title Sqrt Mod\n */\n#line 6 \"\
    test/sqrt_mod.test.cpp\"\n\n#include <cstddef>\n#line 10 \"test/sqrt_mod.test.cpp\"\
    \n\nint main() {\n  size_t Q;\n  std::cin >> Q;\n  while (Q--) {\n    uint32_t\
    \ x;\n    std::cin >> x >> dynamic_modulus<>::mod();\n    if (x == 0) std::cout\
    \ << \"0\\n\";\n    else {\n      const auto ans = sqrt(rmint32_t(x));\n     \
    \ if (ans.zero()) std::cout << \"-1\\n\";\n      else std::cout << ans << '\\\
    n';\n    }\n  }\n  return 0;\n}\n"
  code: "\n#define PROBLEM \"https://judge.yosupo.jp/problem/sqrt_mod\"\n\n#include\
    \ \"../algebraic/modular.cpp\"\n#include \"../algebraic/mod_sqrt.cpp\"\n\n#include\
    \ <cstddef>\n#include <cstdint>\n#include <iostream>\n\nint main() {\n  size_t\
    \ Q;\n  std::cin >> Q;\n  while (Q--) {\n    uint32_t x;\n    std::cin >> x >>\
    \ dynamic_modulus<>::mod();\n    if (x == 0) std::cout << \"0\\n\";\n    else\
    \ {\n      const auto ans = sqrt(rmint32_t(x));\n      if (ans.zero()) std::cout\
    \ << \"-1\\n\";\n      else std::cout << ans << '\\n';\n    }\n  }\n  return 0;\n\
    }\n"
  dependsOn:
  - algebraic/modular.cpp
  - algebraic/mod_inv.cpp
  - algebraic/mod_sqrt.cpp
  - other/random_number.cpp
  isVerificationFile: true
  path: test/sqrt_mod.test.cpp
  requiredBy: []
  timestamp: '2021-02-07 17:51:45+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/sqrt_mod.test.cpp
layout: document
redirect_from:
- /verify/test/sqrt_mod.test.cpp
- /verify/test/sqrt_mod.test.cpp.html
title: test/sqrt_mod.test.cpp
---
