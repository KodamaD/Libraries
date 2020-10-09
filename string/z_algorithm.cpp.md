---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/z_algorithm.test.cpp
    title: test/z_algorithm.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Z-Algorithm
    links: []
  bundledCode: "#line 2 \"string/z_algorithm.cpp\"\n\n#include <cstddef>\n#include\
    \ <vector>\n\ntemplate <class InputIterator>\nstd::vector<size_t> z_algorithm(InputIterator\
    \ first, InputIterator last) {\n  const std::vector<typename InputIterator::value_type>\
    \ str(first, last);\n  const size_t size = str.size();\n  std::vector<size_t>\
    \ result(size);\n  result[0] = size;\n  size_t i = 1, j = 0;\n  while (i < size)\
    \ {\n    while (i + j < size && str[i + j] == str[j]) {\n      ++j;\n    }\n \
    \   result[i] = j;\n    if (j == 0) { \n      ++i; \n      continue; \n    }\n\
    \    size_t k = 1;\n    while (i + k < size && k + result[k] < j) { \n      result[i\
    \ + k] = result[k];\n      ++k; \n    }\n    i += k;\n    j -= k;\n  }\n  return\
    \ result;\n}\n\n/**\n * @title Z-Algorithm\n */\n"
  code: "#pragma once\n\n#include <cstddef>\n#include <vector>\n\ntemplate <class\
    \ InputIterator>\nstd::vector<size_t> z_algorithm(InputIterator first, InputIterator\
    \ last) {\n  const std::vector<typename InputIterator::value_type> str(first,\
    \ last);\n  const size_t size = str.size();\n  std::vector<size_t> result(size);\n\
    \  result[0] = size;\n  size_t i = 1, j = 0;\n  while (i < size) {\n    while\
    \ (i + j < size && str[i + j] == str[j]) {\n      ++j;\n    }\n    result[i] =\
    \ j;\n    if (j == 0) { \n      ++i; \n      continue; \n    }\n    size_t k =\
    \ 1;\n    while (i + k < size && k + result[k] < j) { \n      result[i + k] =\
    \ result[k];\n      ++k; \n    }\n    i += k;\n    j -= k;\n  }\n  return result;\n\
    }\n\n/**\n * @title Z-Algorithm\n */"
  dependsOn: []
  isVerificationFile: false
  path: string/z_algorithm.cpp
  requiredBy: []
  timestamp: '2020-08-14 11:56:16+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/z_algorithm.test.cpp
documentation_of: string/z_algorithm.cpp
layout: document
redirect_from:
- /library/string/z_algorithm.cpp
- /library/string/z_algorithm.cpp.html
title: Z-Algorithm
---
