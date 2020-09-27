---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/random_number.cpp
    title: Random Number
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    document_title: Randomized Queue
    links: []
  bundledCode: "#line 2 \"container/randomized_queue.cpp\"\n\n#line 2 \"other/random_number.cpp\"\
    \n\n#include <cstdint>\n#include <random>\n#include <chrono>\n#include <array>\n\
    #include <type_traits>\n\nuint64_t engine() {\n  static const auto rotate = [](const\
    \ uint64_t x, const size_t k) {\n    return (x << k) | (x >> (64 - k));\n  };\n\
    \  static auto array = [] {\n    uint64_t seed = static_cast<uint64_t>(std::chrono::system_clock::now().time_since_epoch().count());\n\
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
    }\n\n/** \n * @title Random Number\n */\n#line 4 \"container/randomized_queue.cpp\"\
    \n\n#include <cstddef>\n#line 7 \"container/randomized_queue.cpp\"\n#include <vector>\n\
    #include <iterator>\n#include <algorithm>\n#include <cassert>\n\ntemplate <class\
    \ T>\nclass randomized_queue {\npublic:\n  using value_type = T;\n  using size_type\
    \ = size_t;\n\nprivate:\n  std::vector<value_type> M_data;\n\npublic:\n  randomized_queue()\
    \ = default;\n  template <class InputIterator>\n  explicit randomized_queue(InputIterator\
    \ first, InputIterator last) { construct(first, last); }\n\n  template <class\
    \ InputIterator>\n  void construct(InputIterator first, InputIterator last) {\
    \ \n    clear();\n    const size_type size = std::distance(first, last);\n   \
    \ M_data.reserve(size);\n    std::copy(first, last, std::back_inserter(M_data));\n\
    \  }\n\n  void shuffle() {\n    assert(!empty());\n    std::swap(M_data.back(),\
    \ M_data[random_number<size_type>(0, M_data.size() - 1)]);\n  }\n\n  value_type\
    \ front() const {\n    assert(!empty());\n    return M_data.back();\n  }\n  bool\
    \ empty() const {\n    return M_data.empty();\n  }\n  size_type size() const {\n\
    \    return M_data.size();\n  }\n\n  void push(const value_type &val) {\n    M_data.push_back(val);\n\
    \    shuffle();\n  }\n  void pop() {\n    assert(!empty());\n    M_data.pop_back();\n\
    \    if (!M_data.empty()) {\n      shuffle();\n    }\n  }\n  void clear() {\n\
    \    M_data.clear();\n    M_data.shrink_to_fit();\n  }\n};\n\n/**\n * @title Randomized\
    \ Queue\n */\n"
  code: "#pragma once\n\n#include \"../other/random_number.cpp\"\n\n#include <cstddef>\n\
    #include <cstdint>\n#include <vector>\n#include <iterator>\n#include <algorithm>\n\
    #include <cassert>\n\ntemplate <class T>\nclass randomized_queue {\npublic:\n\
    \  using value_type = T;\n  using size_type = size_t;\n\nprivate:\n  std::vector<value_type>\
    \ M_data;\n\npublic:\n  randomized_queue() = default;\n  template <class InputIterator>\n\
    \  explicit randomized_queue(InputIterator first, InputIterator last) { construct(first,\
    \ last); }\n\n  template <class InputIterator>\n  void construct(InputIterator\
    \ first, InputIterator last) { \n    clear();\n    const size_type size = std::distance(first,\
    \ last);\n    M_data.reserve(size);\n    std::copy(first, last, std::back_inserter(M_data));\n\
    \  }\n\n  void shuffle() {\n    assert(!empty());\n    std::swap(M_data.back(),\
    \ M_data[random_number<size_type>(0, M_data.size() - 1)]);\n  }\n\n  value_type\
    \ front() const {\n    assert(!empty());\n    return M_data.back();\n  }\n  bool\
    \ empty() const {\n    return M_data.empty();\n  }\n  size_type size() const {\n\
    \    return M_data.size();\n  }\n\n  void push(const value_type &val) {\n    M_data.push_back(val);\n\
    \    shuffle();\n  }\n  void pop() {\n    assert(!empty());\n    M_data.pop_back();\n\
    \    if (!M_data.empty()) {\n      shuffle();\n    }\n  }\n  void clear() {\n\
    \    M_data.clear();\n    M_data.shrink_to_fit();\n  }\n};\n\n/**\n * @title Randomized\
    \ Queue\n */"
  dependsOn:
  - other/random_number.cpp
  isVerificationFile: false
  path: container/randomized_queue.cpp
  requiredBy: []
  timestamp: '2020-09-09 18:08:09+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: container/randomized_queue.cpp
layout: document
redirect_from:
- /library/container/randomized_queue.cpp
- /library/container/randomized_queue.cpp.html
title: Randomized Queue
---
