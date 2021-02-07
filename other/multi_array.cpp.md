---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Multi-Dimensional Array
    links: []
  bundledCode: "#line 2 \"other/multi_array.cpp\"\n\n#include <cstddef>\n#include\
    \ <array>\n\ntemplate <class T, size_t N, size_t... Seq>\nstruct multi_array_impl\
    \ {\n  using type = std::array<typename multi_array_impl<T, Seq...>::type, N>;\n\
    };\n\ntemplate <class T, size_t N>\nstruct multi_array_impl<T, N> {\n  using type\
    \ = std::array<T, N>;\n};\n\ntemplate <class T, size_t N, size_t... Seq>\nusing\
    \ multi_array = typename multi_array_impl<T, N, Seq...>::type; \n\n/**\n * @title\
    \ Multi-Dimensional Array\n */\n"
  code: "#pragma once\n\n#include <cstddef>\n#include <array>\n\ntemplate <class T,\
    \ size_t N, size_t... Seq>\nstruct multi_array_impl {\n  using type = std::array<typename\
    \ multi_array_impl<T, Seq...>::type, N>;\n};\n\ntemplate <class T, size_t N>\n\
    struct multi_array_impl<T, N> {\n  using type = std::array<T, N>;\n};\n\ntemplate\
    \ <class T, size_t N, size_t... Seq>\nusing multi_array = typename multi_array_impl<T,\
    \ N, Seq...>::type; \n\n/**\n * @title Multi-Dimensional Array\n */"
  dependsOn: []
  isVerificationFile: false
  path: other/multi_array.cpp
  requiredBy: []
  timestamp: '2020-07-11 19:42:18+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other/multi_array.cpp
layout: document
redirect_from:
- /library/other/multi_array.cpp
- /library/other/multi_array.cpp.html
title: Multi-Dimensional Array
---
