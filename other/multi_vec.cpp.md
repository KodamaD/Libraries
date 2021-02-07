---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Multi-Dimensional Vector
    links: []
  bundledCode: "#line 2 \"other/multi_vec.cpp\"\n\n#include <cstddef>\n#include <vector>\n\
    #include <type_traits>\n\ntemplate <class T, size_t N, size_t I = 0>\ndecltype(auto)\
    \ multi_vec(const size_t (&)[N], typename std::enable_if<(I == N), const T&>::type\
    \ value = T{}) { \n  return value; \n}\n\ntemplate <class T, size_t N, size_t\
    \ I = 0>\ndecltype(auto) multi_vec(const size_t (&list)[N], typename std::enable_if<(I\
    \ != N), const T&>::type value = T{}) { \n  return std::vector(list[I], multi_vec<T,\
    \ N, I + 1>(list, value)); \n}\n\n/**\n * @title Multi-Dimensional Vector\n */\n"
  code: "#pragma once\n\n#include <cstddef>\n#include <vector>\n#include <type_traits>\n\
    \ntemplate <class T, size_t N, size_t I = 0>\ndecltype(auto) multi_vec(const size_t\
    \ (&)[N], typename std::enable_if<(I == N), const T&>::type value = T{}) { \n\
    \  return value; \n}\n\ntemplate <class T, size_t N, size_t I = 0>\ndecltype(auto)\
    \ multi_vec(const size_t (&list)[N], typename std::enable_if<(I != N), const T&>::type\
    \ value = T{}) { \n  return std::vector(list[I], multi_vec<T, N, I + 1>(list,\
    \ value)); \n}\n\n/**\n * @title Multi-Dimensional Vector\n */"
  dependsOn: []
  isVerificationFile: false
  path: other/multi_vec.cpp
  requiredBy: []
  timestamp: '2020-07-12 13:43:20+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other/multi_vec.cpp
layout: document
redirect_from:
- /library/other/multi_vec.cpp
- /library/other/multi_vec.cpp.html
title: Multi-Dimensional Vector
---
