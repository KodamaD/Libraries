---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/discrete_log.test.cpp
    title: test/discrete_log.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    document_title: Discrete Logarithm
    links: []
  bundledCode: "#line 2 \"algebraic/mod_log.cpp\"\n\n#include <cstdint>\n#include\
    \ <unordered_map>\n\ntemplate <class Modular>\nuint64_t log(const Modular x, const\
    \ Modular y) {\n  static const auto gcd = [&](uint64_t a, uint64_t b) {\n    while\
    \ (b != 0) std::swap(a %= b, b);\n    return a;\n  };\n  const auto mod = Modular::mod();\n\
    \  const uint64_t base = uint64_t(x);\n  uint64_t anti = uint64_t(y);\n  uint64_t\
    \ g = 1;\n  for (uint64_t m = mod; m > 0; m >>= 1) (g *= base) %= mod;\n  g =\
    \ gcd(g, mod);\n  uint64_t c = 0, t = 1;\n  while (t % g != 0) {\n    if (t ==\
    \ anti) return c;\n    (t *= base) %= mod;\n    ++c;\n  }\n  if (anti % g != 0)\
    \ return mod;\n  t /= g, anti /= g;\n  const uint64_t n = mod / g;\n  uint64_t\
    \ h = 0, gs = 1;\n  while (h * h < n) (gs *= base) %= n, ++h;\n  std::unordered_map<uint64_t,\
    \ uint64_t> bs;\n  uint64_t s = 0, e = anti;\n  while (s < h) {\n    (e *= base)\
    \ %= n;\n    bs[e] = ++s;\n  }\n  s = 0, e = t;\n  while (s < n) {\n    (e *=\
    \ gs) %= n;\n    s += h;\n    if (bs.count(e)) return c + s - bs[e];\n  }\n  return\
    \ mod;\n}\n\n/**\n * @title Discrete Logarithm\n */\n"
  code: "#pragma once\n\n#include <cstdint>\n#include <unordered_map>\n\ntemplate\
    \ <class Modular>\nuint64_t log(const Modular x, const Modular y) {\n  static\
    \ const auto gcd = [&](uint64_t a, uint64_t b) {\n    while (b != 0) std::swap(a\
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
    \ mod;\n}\n\n/**\n * @title Discrete Logarithm\n */"
  dependsOn: []
  isVerificationFile: false
  path: algebraic/mod_log.cpp
  requiredBy: []
  timestamp: '2020-09-19 12:22:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/discrete_log.test.cpp
documentation_of: algebraic/mod_log.cpp
layout: document
redirect_from:
- /library/algebraic/mod_log.cpp
- /library/algebraic/mod_log.cpp.html
title: Discrete Logarithm
---
