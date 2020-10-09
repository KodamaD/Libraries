---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Sieve of Eratosthenes
    links: []
  bundledCode: "#line 2 \"algebraic/sieve.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    #include <array>\n#include <vector>\n#include <utility>\n#include <cassert>\n\
    #include <numeric>\n#include <type_traits>\n\ntemplate <size_t N>\nclass sieve\
    \ {\nprivate:\n  std::array<uint32_t, N + 1> M_smallest;\n\npublic:\n  sieve()\
    \ {\n    std::iota(M_smallest.begin(), M_smallest.end(), (uint32_t) 0);\n    for\
    \ (uint32_t i = 2; i <= N; ++i) {\n      if (M_smallest[i] == i) {\n        for\
    \ (uint32_t j = i + i; j <= N; j += i) {\n          if (M_smallest[j] == j) {\n\
    \            M_smallest[j] = i;\n          }\n        }\n      }\n    }\n  }\n\
    \n  template <class T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>\n\
    \  std::vector<std::pair<T, size_t>> factorize(T x) {\n    assert(x > 0);\n  \
    \  assert((size_t) x <= N);\n    std::vector<std::pair<T, size_t>> res;\n    while\
    \ (x != 1) {\n      const auto cur = M_smallest[x];\n      res.emplace_back((T)\
    \ cur, 0);\n      while (M_smallest[x] == cur) {\n        res.back().second++;\n\
    \        x /= cur;\n      }\n    }\n    return res;\n  }\n  bool operator [] (const\
    \ size_t n) const {\n    if (n <= 1) return false;\n    assert(n <= N);\n    return\
    \ (M_smallest[n] == (uint32_t) n);\n  }\n};\n\n/**\n * @title Sieve of Eratosthenes\n\
    \ */\n"
  code: "#pragma once\n\n#include <cstddef>\n#include <cstdint>\n#include <array>\n\
    #include <vector>\n#include <utility>\n#include <cassert>\n#include <numeric>\n\
    #include <type_traits>\n\ntemplate <size_t N>\nclass sieve {\nprivate:\n  std::array<uint32_t,\
    \ N + 1> M_smallest;\n\npublic:\n  sieve() {\n    std::iota(M_smallest.begin(),\
    \ M_smallest.end(), (uint32_t) 0);\n    for (uint32_t i = 2; i <= N; ++i) {\n\
    \      if (M_smallest[i] == i) {\n        for (uint32_t j = i + i; j <= N; j +=\
    \ i) {\n          if (M_smallest[j] == j) {\n            M_smallest[j] = i;\n\
    \          }\n        }\n      }\n    }\n  }\n\n  template <class T, std::enable_if_t<std::is_integral<T>::value>*\
    \ = nullptr>\n  std::vector<std::pair<T, size_t>> factorize(T x) {\n    assert(x\
    \ > 0);\n    assert((size_t) x <= N);\n    std::vector<std::pair<T, size_t>> res;\n\
    \    while (x != 1) {\n      const auto cur = M_smallest[x];\n      res.emplace_back((T)\
    \ cur, 0);\n      while (M_smallest[x] == cur) {\n        res.back().second++;\n\
    \        x /= cur;\n      }\n    }\n    return res;\n  }\n  bool operator [] (const\
    \ size_t n) const {\n    if (n <= 1) return false;\n    assert(n <= N);\n    return\
    \ (M_smallest[n] == (uint32_t) n);\n  }\n};\n\n/**\n * @title Sieve of Eratosthenes\n\
    \ */"
  dependsOn: []
  isVerificationFile: false
  path: algebraic/sieve.cpp
  requiredBy: []
  timestamp: '2020-09-19 12:22:26+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: algebraic/sieve.cpp
layout: document
redirect_from:
- /library/algebraic/sieve.cpp
- /library/algebraic/sieve.cpp.html
title: Sieve of Eratosthenes
---
