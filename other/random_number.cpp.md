---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: algebraic/mod_sqrt.cpp
    title: Sqrt Mod
  - icon: ':warning:'
    path: container/randomized_queue.cpp
    title: Randomized Queue
  - icon: ':warning:'
    path: string/rolling_hash.cpp
    title: Rolling Hash
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/sqrt_mod.test.cpp
    title: test/sqrt_mod.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Random Number
    links: []
  bundledCode: "#line 2 \"other/random_number.cpp\"\n\n#include <cstdint>\n#include\
    \ <random>\n#include <chrono>\n#include <array>\n#include <type_traits>\n\nuint64_t\
    \ engine() {\n  static uint64_t result = static_cast<uint64_t>(std::chrono::system_clock::now().time_since_epoch().count());\n\
    \  result ^= result << 5;\n  result ^= result >> 13;\n  result ^= result << 7;\n\
    \  return result;\n}\n\ntemplate <class Integer>\ntypename std::enable_if<std::is_integral<Integer>::value,\
    \ Integer>::type random_number(Integer lower, Integer upper) {\n  static std::default_random_engine\
    \ gen(engine());\n  return std::uniform_int_distribution<Integer>(lower, upper)(gen);\n\
    }\n\ntemplate <class Real>\ntypename std::enable_if<!std::is_integral<Real>::value,\
    \ Real>::type random_number(Real lower, Real upper) {\n  static std::default_random_engine\
    \ gen(engine());\n  return std::uniform_real_distribution<Real>(lower, upper)(gen);\n\
    }\n\n/** \n * @title Random Number\n */\n"
  code: "#pragma once\n\n#include <cstdint>\n#include <random>\n#include <chrono>\n\
    #include <array>\n#include <type_traits>\n\nuint64_t engine() {\n  static uint64_t\
    \ result = static_cast<uint64_t>(std::chrono::system_clock::now().time_since_epoch().count());\n\
    \  result ^= result << 5;\n  result ^= result >> 13;\n  result ^= result << 7;\n\
    \  return result;\n}\n\ntemplate <class Integer>\ntypename std::enable_if<std::is_integral<Integer>::value,\
    \ Integer>::type random_number(Integer lower, Integer upper) {\n  static std::default_random_engine\
    \ gen(engine());\n  return std::uniform_int_distribution<Integer>(lower, upper)(gen);\n\
    }\n\ntemplate <class Real>\ntypename std::enable_if<!std::is_integral<Real>::value,\
    \ Real>::type random_number(Real lower, Real upper) {\n  static std::default_random_engine\
    \ gen(engine());\n  return std::uniform_real_distribution<Real>(lower, upper)(gen);\n\
    }\n\n/** \n * @title Random Number\n */"
  dependsOn: []
  isVerificationFile: false
  path: other/random_number.cpp
  requiredBy:
  - algebraic/mod_sqrt.cpp
  - container/randomized_queue.cpp
  - string/rolling_hash.cpp
  timestamp: '2021-02-07 17:51:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/sqrt_mod.test.cpp
documentation_of: other/random_number.cpp
layout: document
redirect_from:
- /library/other/random_number.cpp
- /library/other/random_number.cpp.html
title: Random Number
---
