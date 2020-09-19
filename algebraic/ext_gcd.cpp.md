---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: algebraic/modular.cpp
    title: Modint
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/lazy_propagation_segment_tree.test.cpp
    title: test/lazy_propagation_segment_tree.test.cpp
  - icon: ':x:'
    path: test/factorials.test.cpp
    title: test/factorials.test.cpp
  - icon: ':x:'
    path: test/sliding_window_aggregation.test.cpp
    title: test/sliding_window_aggregation.test.cpp
  - icon: ':x:'
    path: test/segment_tree.test.cpp
    title: test/segment_tree.test.cpp
  - icon: ':x:'
    path: test/matrix.test.cpp
    title: test/matrix.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    document_title: Extended GCD
    links: []
  bundledCode: "#line 2 \"algebraic/ext_gcd.cpp\"\n\n#include <utility>\n#include\
    \ <cstdint>\n\nconstexpr std::pair<int64_t, int64_t> ext_gcd(int64_t a, int64_t\
    \ b) {\n  if ((a %= b) == 0) return { b, 0 };\n  int64_t s = b, t = (a < 0 ? a\
    \ + b : a);\n  int64_t m0 = 0, m1 = 1;\n  while (t > 0) {\n    const auto u =\
    \ s / t;\n    s -= t * u; m0 -= m1 * u;\n    std::swap(s, t); std::swap(m0, m1);\n\
    \  }\n  return { s, (m0 < 0 ? m0 + b / s : m0) };\n}\n\n/**\n * @title Extended\
    \ GCD\n */\n"
  code: "#pragma once\n\n#include <utility>\n#include <cstdint>\n\nconstexpr std::pair<int64_t,\
    \ int64_t> ext_gcd(int64_t a, int64_t b) {\n  if ((a %= b) == 0) return { b, 0\
    \ };\n  int64_t s = b, t = (a < 0 ? a + b : a);\n  int64_t m0 = 0, m1 = 1;\n \
    \ while (t > 0) {\n    const auto u = s / t;\n    s -= t * u; m0 -= m1 * u;\n\
    \    std::swap(s, t); std::swap(m0, m1);\n  }\n  return { s, (m0 < 0 ? m0 + b\
    \ / s : m0) };\n}\n\n/**\n * @title Extended GCD\n */"
  dependsOn: []
  isVerificationFile: false
  path: algebraic/ext_gcd.cpp
  requiredBy:
  - algebraic/modular.cpp
  timestamp: '2020-09-19 12:22:26+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/lazy_propagation_segment_tree.test.cpp
  - test/factorials.test.cpp
  - test/sliding_window_aggregation.test.cpp
  - test/segment_tree.test.cpp
  - test/matrix.test.cpp
documentation_of: algebraic/ext_gcd.cpp
layout: document
redirect_from:
- /library/algebraic/ext_gcd.cpp
- /library/algebraic/ext_gcd.cpp.html
title: Extended GCD
---
