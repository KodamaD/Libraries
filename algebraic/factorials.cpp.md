---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/factorials.test.cpp
    title: test/factorials.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Factorial
    links: []
  bundledCode: "#line 2 \"algebraic/factorials.cpp\"\n\n#include <cstddef>\n#include\
    \ <array>\n#include <cassert>\n\ntemplate <class T, size_t N>\nclass factorials\
    \ {\npublic:\n  using value_type = T;\n\npublic:\n  std::array<value_type, N +\
    \ 1> fact{};\n  std::array<value_type, N + 1> fact_inv{};\n\n  factorials() {\n\
    \    fact.front() = value_type(1);\n    for (size_t i = 1; i <= N; ++i) {\n  \
    \    fact[i] = fact[i - 1] * value_type(i);\n    }\n    fact_inv.back() = value_type(1)\
    \ / fact.back();\n    for (size_t i = N; i > 0; --i) {\n      fact_inv[i - 1]\
    \ = fact_inv[i] * value_type(i);\n    }\n  }\n\n  value_type operator () (size_t\
    \ n, size_t r) const {\n    assert(n <= N);\n    assert(n >= r);\n    return fact[n]\
    \ * fact_inv[n - r] * fact_inv[r];\n  }\n};\n\n/**\n * @title Factorial\n */\n"
  code: "#pragma once\n\n#include <cstddef>\n#include <array>\n#include <cassert>\n\
    \ntemplate <class T, size_t N>\nclass factorials {\npublic:\n  using value_type\
    \ = T;\n\npublic:\n  std::array<value_type, N + 1> fact{};\n  std::array<value_type,\
    \ N + 1> fact_inv{};\n\n  factorials() {\n    fact.front() = value_type(1);\n\
    \    for (size_t i = 1; i <= N; ++i) {\n      fact[i] = fact[i - 1] * value_type(i);\n\
    \    }\n    fact_inv.back() = value_type(1) / fact.back();\n    for (size_t i\
    \ = N; i > 0; --i) {\n      fact_inv[i - 1] = fact_inv[i] * value_type(i);\n \
    \   }\n  }\n\n  value_type operator () (size_t n, size_t r) const {\n    assert(n\
    \ <= N);\n    assert(n >= r);\n    return fact[n] * fact_inv[n - r] * fact_inv[r];\n\
    \  }\n};\n\n/**\n * @title Factorial\n */"
  dependsOn: []
  isVerificationFile: false
  path: algebraic/factorials.cpp
  requiredBy: []
  timestamp: '2020-10-09 16:14:32+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/factorials.test.cpp
documentation_of: algebraic/factorials.cpp
layout: document
redirect_from:
- /library/algebraic/factorials.cpp
- /library/algebraic/factorials.cpp.html
title: Factorial
---
