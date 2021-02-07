---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Manacher
    links: []
  bundledCode: "#line 2 \"string/manacher.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    #include <vector>\n#include <iterator>\n\ntemplate <class InputIterator>\nclass\
    \ manacher_impl {\npublic:\n  using value_type = typename InputIterator::value_type;\n\
    \npublic:\n  std::vector<size_t> odd, even;\n\n  explicit manacher_impl(InputIterator\
    \ first, InputIterator last, const value_type &never) {\n    const size_t size\
    \ = std::distance(first, last);\n    odd.resize(size);\n    even.resize(size -\
    \ 1);\n    std::vector<value_type> str;\n    str.reserve(2 * size + 1);\n    for\
    \ (; first != last; ++first) {\n      str.push_back(never);\n      str.push_back(*first);\n\
    \    }\n    str.push_back(never);\n    std::vector<int32_t> calc(str.size());\n\
    \    int32_t i = 0, j = 0;\n    while (i < (int32_t) str.size()) {\n      while\
    \ (i - j >= 0 && i + j < (int32_t) str.size() && str[i - j] == str[i + j]) {\n\
    \        ++j;\n      }\n      calc[i] = j;\n      int32_t k = 1;\n      while\
    \ (i - k >= 0 && k + calc[i - k] < j) {\n        calc[i + k] = calc[i - k];\n\
    \        ++k;\n      }\n      i += k;\n      j -= k;\n    }\n    for (size_t k\
    \ = 1; k + 1 < str.size(); ++k) {\n      if (k % 2 == 1) {\n        odd[k / 2]\
    \ = calc[k] - 1;\n      }\n      else {\n        even[k / 2 - 1] = calc[k] - 1;\n\
    \      }\n    }\n  }\n};\n\ntemplate <class InputIterator>\nmanacher_impl<InputIterator>\
    \ manacher(InputIterator first, InputIterator last, const typename InputIterator::value_type\
    \ &never) {\n  return manacher_impl<InputIterator>(first, last, never);\n}\n\n\
    /**\n * @title Manacher\n */\n"
  code: "#pragma once\n\n#include <cstddef>\n#include <cstdint>\n#include <vector>\n\
    #include <iterator>\n\ntemplate <class InputIterator>\nclass manacher_impl {\n\
    public:\n  using value_type = typename InputIterator::value_type;\n\npublic:\n\
    \  std::vector<size_t> odd, even;\n\n  explicit manacher_impl(InputIterator first,\
    \ InputIterator last, const value_type &never) {\n    const size_t size = std::distance(first,\
    \ last);\n    odd.resize(size);\n    even.resize(size - 1);\n    std::vector<value_type>\
    \ str;\n    str.reserve(2 * size + 1);\n    for (; first != last; ++first) {\n\
    \      str.push_back(never);\n      str.push_back(*first);\n    }\n    str.push_back(never);\n\
    \    std::vector<int32_t> calc(str.size());\n    int32_t i = 0, j = 0;\n    while\
    \ (i < (int32_t) str.size()) {\n      while (i - j >= 0 && i + j < (int32_t) str.size()\
    \ && str[i - j] == str[i + j]) {\n        ++j;\n      }\n      calc[i] = j;\n\
    \      int32_t k = 1;\n      while (i - k >= 0 && k + calc[i - k] < j) {\n   \
    \     calc[i + k] = calc[i - k];\n        ++k;\n      }\n      i += k;\n     \
    \ j -= k;\n    }\n    for (size_t k = 1; k + 1 < str.size(); ++k) {\n      if\
    \ (k % 2 == 1) {\n        odd[k / 2] = calc[k] - 1;\n      }\n      else {\n \
    \       even[k / 2 - 1] = calc[k] - 1;\n      }\n    }\n  }\n};\n\ntemplate <class\
    \ InputIterator>\nmanacher_impl<InputIterator> manacher(InputIterator first, InputIterator\
    \ last, const typename InputIterator::value_type &never) {\n  return manacher_impl<InputIterator>(first,\
    \ last, never);\n}\n\n/**\n * @title Manacher\n */"
  dependsOn: []
  isVerificationFile: false
  path: string/manacher.cpp
  requiredBy: []
  timestamp: '2020-09-09 18:08:09+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: string/manacher.cpp
layout: document
redirect_from:
- /library/string/manacher.cpp
- /library/string/manacher.cpp.html
title: Manacher
---
