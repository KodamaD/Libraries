---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    document_title: Chmin/Chmax
    links: []
  bundledCode: "#line 2 \"other/chmin_chmax.cpp\"\n\ntemplate <class T, class U>\n\
    constexpr bool chmin(T &lhs, const U &rhs) {\n  if (lhs > rhs) { lhs = rhs; return\
    \ true; }\n  return false;\n}\n\ntemplate <class T, class U>\nconstexpr bool chmax(T\
    \ &lhs, const U &rhs) {\n  if (lhs < rhs) { lhs = rhs; return true; }\n  return\
    \ false;\n}\n\n/**\n * @title Chmin/Chmax\n */\n"
  code: "#pragma once\n\ntemplate <class T, class U>\nconstexpr bool chmin(T &lhs,\
    \ const U &rhs) {\n  if (lhs > rhs) { lhs = rhs; return true; }\n  return false;\n\
    }\n\ntemplate <class T, class U>\nconstexpr bool chmax(T &lhs, const U &rhs) {\n\
    \  if (lhs < rhs) { lhs = rhs; return true; }\n  return false;\n}\n\n/**\n * @title\
    \ Chmin/Chmax\n */"
  dependsOn: []
  isVerificationFile: false
  path: other/chmin_chmax.cpp
  requiredBy: []
  timestamp: '2020-08-11 15:45:19+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other/chmin_chmax.cpp
layout: document
redirect_from:
- /library/other/chmin_chmax.cpp
- /library/other/chmin_chmax.cpp.html
title: Chmin/Chmax
---
