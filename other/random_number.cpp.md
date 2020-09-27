---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: string/rolling_hash.cpp
    title: Rolling Hash
  - icon: ':heavy_check_mark:'
    path: algebraic/mod_sqrt.cpp
    title: Sqrt Mod
  - icon: ':warning:'
    path: container/randomized_queue.cpp
    title: Randomized Queue
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/sqrt_mod.test.cpp
    title: test/sqrt_mod.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    document_title: Random Number
    links: []
  bundledCode: "#line 2 \"other/random_number.cpp\"\n\n#include <cstdint>\n#include\
    \ <random>\n#include <chrono>\n#include <array>\n#include <type_traits>\n\nuint64_t\
    \ engine() {\n  static const auto rotate = [](const uint64_t x, const size_t k)\
    \ {\n    return (x << k) | (x >> (64 - k));\n  };\n  static auto array = [] {\n\
    \    uint64_t seed = static_cast<uint64_t>(std::chrono::system_clock::now().time_since_epoch().count());\n\
    \    std::array<uint64_t, 4> res{};\n    for (size_t index = 0; index < 4; index++)\
    \ {\n      uint64_t value = (seed += 0x9e3779b97f4a7c15);\n      value = (value\
    \ ^ (value >> 30)) * 0xbf58476d1ce4e5b9;\n      value = (value ^ (value >> 27))\
    \ * 0x94d049bb133111eb;\n      res[index] = value ^ (value >> 31);\n    }\n  \
    \  return res;\n  }();\n  const uint64_t result = rotate(array[1] * 5, 7) * 9;\n\
    \  const uint64_t old_value = array[1] << 17;\n  array[2] ^= array[0];\n  array[3]\
    \ ^= array[1];\n  array[1] ^= array[2];\n  array[0] ^= array[3];\n  array[2] ^=\
    \ old_value;\n  array[3] = rotate(array[3], 45);\n  return result;\n}\n\ntemplate\
    \ <class Integer>\ntypename std::enable_if<std::is_integral<Integer>::value, Integer>::type\
    \ random_number(Integer lower, Integer upper) {\n  static std::default_random_engine\
    \ gen(engine());\n  return std::uniform_int_distribution<Integer>(lower, upper)(gen);\n\
    }\n\ntemplate <class Real>\ntypename std::enable_if<!std::is_integral<Real>::value,\
    \ Real>::type random_number(Real lower, Real upper) {\n  static std::default_random_engine\
    \ gen(engine());\n  return std::uniform_real_distribution<Real>(lower, upper)(gen);\n\
    }\n\n/** \n * @title Random Number\n */\n"
  code: "#pragma once\n\n#include <cstdint>\n#include <random>\n#include <chrono>\n\
    #include <array>\n#include <type_traits>\n\nuint64_t engine() {\n  static const\
    \ auto rotate = [](const uint64_t x, const size_t k) {\n    return (x << k) |\
    \ (x >> (64 - k));\n  };\n  static auto array = [] {\n    uint64_t seed = static_cast<uint64_t>(std::chrono::system_clock::now().time_since_epoch().count());\n\
    \    std::array<uint64_t, 4> res{};\n    for (size_t index = 0; index < 4; index++)\
    \ {\n      uint64_t value = (seed += 0x9e3779b97f4a7c15);\n      value = (value\
    \ ^ (value >> 30)) * 0xbf58476d1ce4e5b9;\n      value = (value ^ (value >> 27))\
    \ * 0x94d049bb133111eb;\n      res[index] = value ^ (value >> 31);\n    }\n  \
    \  return res;\n  }();\n  const uint64_t result = rotate(array[1] * 5, 7) * 9;\n\
    \  const uint64_t old_value = array[1] << 17;\n  array[2] ^= array[0];\n  array[3]\
    \ ^= array[1];\n  array[1] ^= array[2];\n  array[0] ^= array[3];\n  array[2] ^=\
    \ old_value;\n  array[3] = rotate(array[3], 45);\n  return result;\n}\n\ntemplate\
    \ <class Integer>\ntypename std::enable_if<std::is_integral<Integer>::value, Integer>::type\
    \ random_number(Integer lower, Integer upper) {\n  static std::default_random_engine\
    \ gen(engine());\n  return std::uniform_int_distribution<Integer>(lower, upper)(gen);\n\
    }\n\ntemplate <class Real>\ntypename std::enable_if<!std::is_integral<Real>::value,\
    \ Real>::type random_number(Real lower, Real upper) {\n  static std::default_random_engine\
    \ gen(engine());\n  return std::uniform_real_distribution<Real>(lower, upper)(gen);\n\
    }\n\n/** \n * @title Random Number\n */"
  dependsOn: []
  isVerificationFile: false
  path: other/random_number.cpp
  requiredBy:
  - string/rolling_hash.cpp
  - algebraic/mod_sqrt.cpp
  - container/randomized_queue.cpp
  timestamp: '2020-08-09 10:53:47+09:00'
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
