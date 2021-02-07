---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Integer Operations
    links: []
  bundledCode: "#line 2 \"other/int_operation.cpp\"\n\n#include <cstdint>\n#include\
    \ <type_traits>\n#include <limits>\n\ntemplate <class T, std::enable_if_t<std::is_integral<T>::value>*\
    \ = nullptr>\nconstexpr T isqrt(const T x) {\n  T ok = 0, ng = std::numeric_limits<T>::max();\n\
    \  while (ng - ok > 1) {\n    const T md = ok + ((ng - ok) >> 1);\n    (md > x\
    \ / md ? ng : ok) = md;\n  }\n  return ok;\n}\n\ntemplate <class T, std::enable_if_t<std::is_integral<T>::value>*\
    \ = nullptr>\nconstexpr T ipower(T x, uint64_t e) {\n  T res = 1;\n  while (e\
    \ > 0) {\n    if (e & 1) res *= x;\n    e >>= 1;\n    if (e > 0) x *= x;\n  }\n\
    \  return res;\n}\n\n/**\n * @title Integer Operations\n */\n"
  code: "#pragma once\n\n#include <cstdint>\n#include <type_traits>\n#include <limits>\n\
    \ntemplate <class T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>\n\
    constexpr T isqrt(const T x) {\n  T ok = 0, ng = std::numeric_limits<T>::max();\n\
    \  while (ng - ok > 1) {\n    const T md = ok + ((ng - ok) >> 1);\n    (md > x\
    \ / md ? ng : ok) = md;\n  }\n  return ok;\n}\n\ntemplate <class T, std::enable_if_t<std::is_integral<T>::value>*\
    \ = nullptr>\nconstexpr T ipower(T x, uint64_t e) {\n  T res = 1;\n  while (e\
    \ > 0) {\n    if (e & 1) res *= x;\n    e >>= 1;\n    if (e > 0) x *= x;\n  }\n\
    \  return res;\n}\n\n/**\n * @title Integer Operations\n */"
  dependsOn: []
  isVerificationFile: false
  path: other/int_operation.cpp
  requiredBy: []
  timestamp: '2020-09-13 16:51:07+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other/int_operation.cpp
layout: document
redirect_from:
- /library/other/int_operation.cpp
- /library/other/int_operation.cpp.html
title: Integer Operations
---
