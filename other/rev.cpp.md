---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    document_title: Reverser
    links: []
  bundledCode: "#line 2 \"other/rev.cpp\"\n\n#include <type_traits>\n#include <iterator>\n\
    #include <utility>\n\ntemplate <class T>\nclass rev_impl {\npublic:\n  using iterator\
    \ = decltype(std::rbegin(std::declval<T>()));\n\nprivate:\n  const iterator M_begin;\n\
    \  const iterator M_end;\n\npublic:\n  constexpr rev_impl(T &&cont) noexcept:\
    \ M_begin(std::rbegin(cont)), M_end(std::rend(cont)) { }\n  constexpr iterator\
    \ begin() const noexcept { return M_begin; }\n  constexpr iterator end() const\
    \ noexcept { return M_end; }\n};\n\ntemplate <class T>\nconstexpr decltype(auto)\
    \ rev(T &&cont) {\n  return rev_impl<T>(std::forward<T>(cont));\n}\n\n/**\n *\
    \ @title Reverser\n */\n"
  code: "#pragma once\n\n#include <type_traits>\n#include <iterator>\n#include <utility>\n\
    \ntemplate <class T>\nclass rev_impl {\npublic:\n  using iterator = decltype(std::rbegin(std::declval<T>()));\n\
    \nprivate:\n  const iterator M_begin;\n  const iterator M_end;\n\npublic:\n  constexpr\
    \ rev_impl(T &&cont) noexcept: M_begin(std::rbegin(cont)), M_end(std::rend(cont))\
    \ { }\n  constexpr iterator begin() const noexcept { return M_begin; }\n  constexpr\
    \ iterator end() const noexcept { return M_end; }\n};\n\ntemplate <class T>\n\
    constexpr decltype(auto) rev(T &&cont) {\n  return rev_impl<T>(std::forward<T>(cont));\n\
    }\n\n/**\n * @title Reverser\n */"
  dependsOn: []
  isVerificationFile: false
  path: other/rev.cpp
  requiredBy: []
  timestamp: '2020-09-13 16:51:07+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other/rev.cpp
layout: document
redirect_from:
- /library/other/rev.cpp
- /library/other/rev.cpp.html
title: Reverser
---
