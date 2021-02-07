---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algebraic/fact_prime.cpp
    title: Factors/Divisors
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_A
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_A
  bundledCode: "#line 1 \"test/enumerate_factors.test.cpp\"\n\n#define PROBLEM \"\
    https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_A\"\n\n#line 2\
    \ \"algebraic/fact_prime.cpp\"\n\n#include <cstddef>\n#include <utility>\n#include\
    \ <vector>\n#include <algorithm>\n#include <iterator>\n#include <cassert>\n#include\
    \ <type_traits>\n\ntemplate <class T, std::enable_if_t<std::is_integral<T>::value>*\
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
    \ */\n#line 5 \"test/enumerate_factors.test.cpp\"\n\n#include <cstdint>\n#include\
    \ <iostream>\n\nint main() {\n  uint32_t N;\n  std::cin >> N;\n  std::cout <<\
    \ N << ':';\n  for (auto [p, e]: factorize(N)) {\n    while (e--) {\n      std::cout\
    \ << ' ' << p;\n    }\n  }\n  std::cout << '\\n';\n  return 0;\n}\n"
  code: "\n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_A\"\
    \n\n#include \"../algebraic/fact_prime.cpp\"\n\n#include <cstdint>\n#include <iostream>\n\
    \nint main() {\n  uint32_t N;\n  std::cin >> N;\n  std::cout << N << ':';\n  for\
    \ (auto [p, e]: factorize(N)) {\n    while (e--) {\n      std::cout << ' ' <<\
    \ p;\n    }\n  }\n  std::cout << '\\n';\n  return 0;\n}\n"
  dependsOn:
  - algebraic/fact_prime.cpp
  isVerificationFile: true
  path: test/enumerate_factors.test.cpp
  requiredBy: []
  timestamp: '2020-09-13 16:51:07+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/enumerate_factors.test.cpp
layout: document
redirect_from:
- /verify/test/enumerate_factors.test.cpp
- /verify/test/enumerate_factors.test.cpp.html
title: test/enumerate_factors.test.cpp
---
