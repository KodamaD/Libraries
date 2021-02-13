---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: algebraic/modular.cpp
    title: Modint
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/discrete_log.test.cpp
    title: test/discrete_log.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/factorials.test.cpp
    title: test/factorials.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/lazy_propagation_segment_tree.test.cpp
    title: test/lazy_propagation_segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/matrix.test.cpp
    title: test/matrix.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/segment_tree.test.cpp
    title: test/segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/sliding_window_aggregation.test.cpp
    title: test/sliding_window_aggregation.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/sqrt_mod.test.cpp
    title: test/sqrt_mod.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Extended GCD
    links: []
  bundledCode: "#line 2 \"algebraic/mod_inv.cpp\"\n\n#include <utility>\n#include\
    \ <cstdint>\n\nconstexpr std::pair<int64_t, int64_t> mod_inv(int64_t a, int64_t\
    \ b) {\n  if ((a %= b) == 0) return { b, 0 };\n  int64_t s = b, t = (a < 0 ? a\
    \ + b : a);\n  int64_t m0 = 0, m1 = 1, tmp = 0;\n  while (t > 0) {\n    const\
    \ auto u = s / t;\n    s -= t * u; m0 -= m1 * u;\n    tmp = s; s = t; t = tmp;\
    \ tmp = m0; m0 = m1; m1 = tmp;\n  }\n  return { s, (m0 < 0 ? m0 + b / s : m0)\
    \ };\n}\n\n/**\n * @title Extended GCD\n */\n"
  code: "#pragma once\n\n#include <utility>\n#include <cstdint>\n\nconstexpr std::pair<int64_t,\
    \ int64_t> mod_inv(int64_t a, int64_t b) {\n  if ((a %= b) == 0) return { b, 0\
    \ };\n  int64_t s = b, t = (a < 0 ? a + b : a);\n  int64_t m0 = 0, m1 = 1, tmp\
    \ = 0;\n  while (t > 0) {\n    const auto u = s / t;\n    s -= t * u; m0 -= m1\
    \ * u;\n    tmp = s; s = t; t = tmp; tmp = m0; m0 = m1; m1 = tmp;\n  }\n  return\
    \ { s, (m0 < 0 ? m0 + b / s : m0) };\n}\n\n/**\n * @title Extended GCD\n */"
  dependsOn: []
  isVerificationFile: false
  path: algebraic/mod_inv.cpp
  requiredBy:
  - algebraic/modular.cpp
  timestamp: '2020-09-21 19:57:57+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/matrix.test.cpp
  - test/discrete_log.test.cpp
  - test/segment_tree.test.cpp
  - test/sqrt_mod.test.cpp
  - test/sliding_window_aggregation.test.cpp
  - test/factorials.test.cpp
  - test/lazy_propagation_segment_tree.test.cpp
documentation_of: algebraic/mod_inv.cpp
layout: document
redirect_from:
- /library/algebraic/mod_inv.cpp
- /library/algebraic/mod_inv.cpp.html
title: Extended GCD
---
