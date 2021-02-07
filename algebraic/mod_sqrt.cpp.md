---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/random_number.cpp
    title: Random Number
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/sqrt_mod.test.cpp
    title: test/sqrt_mod.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Sqrt Mod
    links: []
  bundledCode: "#line 2 \"algebraic/mod_sqrt.cpp\"\n\n#line 2 \"other/random_number.cpp\"\
    \n\n#include <cstdint>\n#include <random>\n#include <chrono>\n#include <array>\n\
    #include <type_traits>\n\nuint64_t engine() {\n  static uint64_t result = static_cast<uint64_t>(std::chrono::system_clock::now().time_since_epoch().count());\n\
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
    \  f0 = tmp;\n  }\n  return g0;\n}\n\n/**\n * @title Sqrt Mod\n */\n"
  code: "#pragma once\n\n#include \"../other/random_number.cpp\"\n\n#include <cstdint>\n\
    \ntemplate <class Modular>\nModular sqrt(const Modular value) {\n  if (value ==\
    \ Modular(0)) return value;\n  const auto mod = Modular::mod();\n  if (mod ==\
    \ 2) return value;\n  if (power(value, (mod - 1) >> 1) != Modular(1)) return Modular(0);\n\
    \  if (mod % 4 == 3) return power(value, (mod + 1) >> 2);\n  if (mod % 8 == 5)\
    \ {\n    if (power(value, (mod - 1) >> 2) == Modular(1)) return power(value, (mod\
    \ + 3) >> 3);\n    else return power(Modular(2), (mod - 1) >> 2) * power(value,\
    \ (mod + 3) >> 3);\n  }\n  Modular f0, f1(1), g0(1), g1, D, tmp;\n  while (true)\
    \ {\n    f0.extract() = random_number<uint32_t>(2, mod - 1);\n    D = f0 * f0\
    \ - value;\n    if (D == Modular(0)) return f0;\n    if (power(D, (mod - 1) >>\
    \ 1) == Modular(-1)) break;\n  }\n  for (uint32_t exp = (mod + 1) >> 1; exp >\
    \ 0; exp >>= 1) {\n    if (exp & 1) {\n      tmp = g0 * f0 + D * (g1 * f1);\n\
    \      g1 = g0 * f1 + g1 * f0;\n      g0 = tmp;\n    }\n    tmp = f0 * f0 + D\
    \ * (f1 * f1);\n    f1 = Modular(2) * f0 * f1;\n    f0 = tmp;\n  }\n  return g0;\n\
    }\n\n/**\n * @title Sqrt Mod\n */"
  dependsOn:
  - other/random_number.cpp
  isVerificationFile: false
  path: algebraic/mod_sqrt.cpp
  requiredBy: []
  timestamp: '2021-02-07 17:51:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/sqrt_mod.test.cpp
documentation_of: algebraic/mod_sqrt.cpp
layout: document
redirect_from:
- /library/algebraic/mod_sqrt.cpp
- /library/algebraic/mod_sqrt.cpp.html
title: Sqrt Mod
---
