---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/enumerate_factors.test.cpp
    title: test/enumerate_factors.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    document_title: Factors/Divisors
    links: []
  bundledCode: "#line 2 \"algebraic/fact_prime.cpp\"\n\n#include <cstddef>\n#include\
    \ <utility>\n#include <vector>\n#include <algorithm>\n#include <iterator>\n#include\
    \ <cassert>\n#include <type_traits>\n\ntemplate <class T, std::enable_if_t<std::is_integral<T>::value>*\
    \ = nullptr>\nstd::vector<std::pair<T, size_t>> factorize(T x) {\n  assert(x >\
    \ 0);\n  if (x == 1) return { };\n  std::vector<std::pair<T, size_t>> res;\n \
    \ for (T i = 2; i * i <= x; ++i) {\n    if (x % i == 0) {\n      res.emplace_back(i,\
    \ 0);\n      while (x % i == 0) {\n        res.back().second++;\n        x /=\
    \ i;\n      }\n    }\n  }\n  if (x > 1) {\n    res.emplace_back(x, 1);\n  }\n\
    \  return res;\n}\n\ntemplate <class T, std::enable_if_t<std::is_integral<T>::value>*\
    \ = nullptr>\nstd::vector<T> divisors(const T x) {\n  std::vector<T> small, big;\n\
    \  for (T i = 1; i * i <= x; ++i) {\n    if (x % i == 0) {\n      small.push_back(i);\n\
    \      if (i * i != x) {\n        big.push_back(x / i);\n      }\n    }\n  }\n\
    \  small.reserve(small.size() + big.size());\n  std::copy(big.rbegin(), big.rend(),\
    \ std::back_inserter(small));\n  return small;\n}\n\n/**\n * @title Factors/Divisors\n\
    \ */\n"
  code: "#pragma once\n\n#include <cstddef>\n#include <utility>\n#include <vector>\n\
    #include <algorithm>\n#include <iterator>\n#include <cassert>\n#include <type_traits>\n\
    \ntemplate <class T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>\n\
    std::vector<std::pair<T, size_t>> factorize(T x) {\n  assert(x > 0);\n  if (x\
    \ == 1) return { };\n  std::vector<std::pair<T, size_t>> res;\n  for (T i = 2;\
    \ i * i <= x; ++i) {\n    if (x % i == 0) {\n      res.emplace_back(i, 0);\n \
    \     while (x % i == 0) {\n        res.back().second++;\n        x /= i;\n  \
    \    }\n    }\n  }\n  if (x > 1) {\n    res.emplace_back(x, 1);\n  }\n  return\
    \ res;\n}\n\ntemplate <class T, std::enable_if_t<std::is_integral<T>::value>*\
    \ = nullptr>\nstd::vector<T> divisors(const T x) {\n  std::vector<T> small, big;\n\
    \  for (T i = 1; i * i <= x; ++i) {\n    if (x % i == 0) {\n      small.push_back(i);\n\
    \      if (i * i != x) {\n        big.push_back(x / i);\n      }\n    }\n  }\n\
    \  small.reserve(small.size() + big.size());\n  std::copy(big.rbegin(), big.rend(),\
    \ std::back_inserter(small));\n  return small;\n}\n\n/**\n * @title Factors/Divisors\n\
    \ */"
  dependsOn: []
  isVerificationFile: false
  path: algebraic/fact_prime.cpp
  requiredBy: []
  timestamp: '2020-09-13 16:51:07+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/enumerate_factors.test.cpp
documentation_of: algebraic/fact_prime.cpp
layout: document
redirect_from:
- /library/algebraic/fact_prime.cpp
- /library/algebraic/fact_prime.cpp.html
title: Factors/Divisors
---
