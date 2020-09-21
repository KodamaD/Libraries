---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algebraic/mod_inv.cpp
    title: Extended GCD
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/lazy_propagation_segment_tree.test.cpp
    title: test/lazy_propagation_segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/factorials.test.cpp
    title: test/factorials.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/sliding_window_aggregation.test.cpp
    title: test/sliding_window_aggregation.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/segment_tree.test.cpp
    title: test/segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/matrix.test.cpp
    title: test/matrix.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    document_title: Modint
    links: []
  bundledCode: "#line 2 \"algebraic/modular.cpp\"\n\n#line 2 \"algebraic/mod_inv.cpp\"\
    \n\n#include <utility>\n#include <cstdint>\n\nconstexpr std::pair<int64_t, int64_t>\
    \ mod_inv(int64_t a, int64_t b) {\n  if ((a %= b) == 0) return { b, 0 };\n  int64_t\
    \ s = b, t = (a < 0 ? a + b : a);\n  int64_t m0 = 0, m1 = 1, tmp = 0;\n  while\
    \ (t > 0) {\n    const auto u = s / t;\n    s -= t * u; m0 -= m1 * u;\n    tmp\
    \ = s; s = t; t = tmp; tmp = m0; m0 = m1; m1 = tmp;\n  }\n  return { s, (m0 <\
    \ 0 ? m0 + b / s : m0) };\n}\n\n/**\n * @title Extended GCD\n */\n#line 4 \"algebraic/modular.cpp\"\
    \n\n#line 6 \"algebraic/modular.cpp\"\n#include <iostream>\n#include <cassert>\n\
    #include <type_traits>\n\ntemplate <class Modulus>\nclass modular {\npublic:\n\
    \  using value_type = uint32_t;\n  using cover_type = uint64_t;\n \n  template\
    \ <class T>\n  static constexpr value_type normalize(T value_) noexcept {\n  \
    \  if (value_ < 0) {\n      value_ = -value_;\n      value_ %= Modulus::mod();\n\
    \      if (value_ == 0) return 0;\n      return Modulus::mod() - value_;\n   \
    \ }\n    return value_ % Modulus::mod();\n  }\n\nprivate:\n  value_type value;\n\
    \n  template <bool IsPrime, std::enable_if_t<IsPrime>* = nullptr>\n  constexpr\
    \ modular inverse_helper() const noexcept { return power(*this, Modulus::mod()\
    \ - 2); }\n  template <bool IsPrime, std::enable_if_t<!IsPrime>* = nullptr>\n\
    \  constexpr modular inverse_helper() const noexcept {\n    const auto tmp = mod_inv(value,\
    \ Modulus::mod());\n    assert(tmp.first == 1);\n    return modular(tmp.second);\n\
    \  }\n\npublic:\n  constexpr modular() noexcept : value(0) { }\n  template <class\
    \ T>\n  explicit constexpr modular(T value_) noexcept : value(normalize(value_))\
    \ { }\n  template <class T>\n  explicit constexpr operator T() const noexcept\
    \ { return static_cast<T>(value); }\n \n  constexpr value_type get() const noexcept\
    \ { return value; }\n  constexpr value_type &extract() noexcept { return value;\
    \ }\n  constexpr modular operator - () const noexcept { return modular(Modulus::mod()\
    \ - value); }\n  constexpr modular operator ~ () const noexcept { return inverse(*this);\
    \ }\n \n  constexpr modular operator + (const modular &rhs) const noexcept { return\
    \ modular(*this) += rhs; }\n  constexpr modular& operator += (const modular &rhs)\
    \ noexcept { \n    if ((value += rhs.value) >= Modulus::mod()) value -= Modulus::mod();\
    \ \n    return *this; \n  }\n \n  constexpr modular operator - (const modular\
    \ &rhs) const noexcept { return modular(*this) -= rhs; }\n  constexpr modular&\
    \ operator -= (const modular &rhs) noexcept { \n    if ((value += Modulus::mod()\
    \ - rhs.value) >= Modulus::mod()) value -= Modulus::mod(); \n    return *this;\
    \ \n  }\n \n  constexpr modular operator * (const modular &rhs) const noexcept\
    \ { return modular(*this) *= rhs; }\n  constexpr modular& operator *= (const modular\
    \ &rhs) noexcept { \n    value = (cover_type) value * rhs.value % Modulus::mod();\n\
    \    return *this;\n  }\n \n  constexpr modular operator / (const modular &rhs)\
    \ const noexcept { return modular(*this) /= rhs; }\n  constexpr modular& operator\
    \ /= (const modular &rhs) noexcept { return (*this) *= inverse(rhs); }\n \n  constexpr\
    \ bool zero() const noexcept { return value == 0; }\n  constexpr bool operator\
    \ == (const modular &rhs) const noexcept { return value == rhs.value; }\n  constexpr\
    \ bool operator != (const modular &rhs) const noexcept { return value != rhs.value;\
    \ }\n \n  friend std::ostream& operator << (std::ostream &stream, const modular\
    \ &rhs) { return stream << rhs.value; }\n  friend constexpr modular inverse(const\
    \ modular &val) noexcept { return val.inverse_helper<Modulus::is_prime>(); }\n\
    \  friend constexpr modular power(modular val, cover_type exp) noexcept { \n \
    \   modular res(1);\n    for (; exp > 0; exp >>= 1, val *= val) if (exp & 1) res\
    \ *= val;\n    return res;\n  }\n \n};\n \ntemplate <uint32_t Mod, bool IsPrime\
    \ = true>\nstruct static_modulus { \n  static constexpr uint32_t mod() noexcept\
    \ { return Mod; } \n  static constexpr bool is_prime = IsPrime;\n};\n\ntemplate\
    \ <uint32_t Id = 0, bool IsPrime = false>\nstruct dynamic_modulus {\n  static\
    \ uint32_t &mod() noexcept { static uint32_t val = 0; return val; }\n  static\
    \ constexpr bool is_prime = IsPrime;\n};\n\ntemplate <uint32_t Mod>\nusing mint32_t\
    \ = modular<static_modulus<Mod>>;\nusing rmint32_t = modular<dynamic_modulus<>>;\n\
    \n/*\n * @title Modint\n */\n"
  code: "#pragma once\n\n#include \"../algebraic/mod_inv.cpp\"\n\n#include <cstdint>\n\
    #include <iostream>\n#include <cassert>\n#include <type_traits>\n\ntemplate <class\
    \ Modulus>\nclass modular {\npublic:\n  using value_type = uint32_t;\n  using\
    \ cover_type = uint64_t;\n \n  template <class T>\n  static constexpr value_type\
    \ normalize(T value_) noexcept {\n    if (value_ < 0) {\n      value_ = -value_;\n\
    \      value_ %= Modulus::mod();\n      if (value_ == 0) return 0;\n      return\
    \ Modulus::mod() - value_;\n    }\n    return value_ % Modulus::mod();\n  }\n\n\
    private:\n  value_type value;\n\n  template <bool IsPrime, std::enable_if_t<IsPrime>*\
    \ = nullptr>\n  constexpr modular inverse_helper() const noexcept { return power(*this,\
    \ Modulus::mod() - 2); }\n  template <bool IsPrime, std::enable_if_t<!IsPrime>*\
    \ = nullptr>\n  constexpr modular inverse_helper() const noexcept {\n    const\
    \ auto tmp = mod_inv(value, Modulus::mod());\n    assert(tmp.first == 1);\n  \
    \  return modular(tmp.second);\n  }\n\npublic:\n  constexpr modular() noexcept\
    \ : value(0) { }\n  template <class T>\n  explicit constexpr modular(T value_)\
    \ noexcept : value(normalize(value_)) { }\n  template <class T>\n  explicit constexpr\
    \ operator T() const noexcept { return static_cast<T>(value); }\n \n  constexpr\
    \ value_type get() const noexcept { return value; }\n  constexpr value_type &extract()\
    \ noexcept { return value; }\n  constexpr modular operator - () const noexcept\
    \ { return modular(Modulus::mod() - value); }\n  constexpr modular operator ~\
    \ () const noexcept { return inverse(*this); }\n \n  constexpr modular operator\
    \ + (const modular &rhs) const noexcept { return modular(*this) += rhs; }\n  constexpr\
    \ modular& operator += (const modular &rhs) noexcept { \n    if ((value += rhs.value)\
    \ >= Modulus::mod()) value -= Modulus::mod(); \n    return *this; \n  }\n \n \
    \ constexpr modular operator - (const modular &rhs) const noexcept { return modular(*this)\
    \ -= rhs; }\n  constexpr modular& operator -= (const modular &rhs) noexcept {\
    \ \n    if ((value += Modulus::mod() - rhs.value) >= Modulus::mod()) value -=\
    \ Modulus::mod(); \n    return *this; \n  }\n \n  constexpr modular operator *\
    \ (const modular &rhs) const noexcept { return modular(*this) *= rhs; }\n  constexpr\
    \ modular& operator *= (const modular &rhs) noexcept { \n    value = (cover_type)\
    \ value * rhs.value % Modulus::mod();\n    return *this;\n  }\n \n  constexpr\
    \ modular operator / (const modular &rhs) const noexcept { return modular(*this)\
    \ /= rhs; }\n  constexpr modular& operator /= (const modular &rhs) noexcept {\
    \ return (*this) *= inverse(rhs); }\n \n  constexpr bool zero() const noexcept\
    \ { return value == 0; }\n  constexpr bool operator == (const modular &rhs) const\
    \ noexcept { return value == rhs.value; }\n  constexpr bool operator != (const\
    \ modular &rhs) const noexcept { return value != rhs.value; }\n \n  friend std::ostream&\
    \ operator << (std::ostream &stream, const modular &rhs) { return stream << rhs.value;\
    \ }\n  friend constexpr modular inverse(const modular &val) noexcept { return\
    \ val.inverse_helper<Modulus::is_prime>(); }\n  friend constexpr modular power(modular\
    \ val, cover_type exp) noexcept { \n    modular res(1);\n    for (; exp > 0; exp\
    \ >>= 1, val *= val) if (exp & 1) res *= val;\n    return res;\n  }\n \n};\n \n\
    template <uint32_t Mod, bool IsPrime = true>\nstruct static_modulus { \n  static\
    \ constexpr uint32_t mod() noexcept { return Mod; } \n  static constexpr bool\
    \ is_prime = IsPrime;\n};\n\ntemplate <uint32_t Id = 0, bool IsPrime = false>\n\
    struct dynamic_modulus {\n  static uint32_t &mod() noexcept { static uint32_t\
    \ val = 0; return val; }\n  static constexpr bool is_prime = IsPrime;\n};\n\n\
    template <uint32_t Mod>\nusing mint32_t = modular<static_modulus<Mod>>;\nusing\
    \ rmint32_t = modular<dynamic_modulus<>>;\n\n/*\n * @title Modint\n */"
  dependsOn:
  - algebraic/mod_inv.cpp
  isVerificationFile: false
  path: algebraic/modular.cpp
  requiredBy: []
  timestamp: '2020-09-21 19:57:57+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/lazy_propagation_segment_tree.test.cpp
  - test/factorials.test.cpp
  - test/sliding_window_aggregation.test.cpp
  - test/segment_tree.test.cpp
  - test/matrix.test.cpp
documentation_of: algebraic/modular.cpp
layout: document
redirect_from:
- /library/algebraic/modular.cpp
- /library/algebraic/modular.cpp.html
title: Modint
---
