---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/network.cpp
    title: Network
  - icon: ':heavy_check_mark:'
    path: graph/network_simplex.cpp
    title: Network Simplex
  - icon: ':warning:'
    path: graph/two_sat.cpp
    title: Two Sat
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/dinic.test.cpp
    title: test/dinic.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/network_simplex.test.cpp
    title: test/network_simplex.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/push_relabel.test.cpp
    title: test/push_relabel.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/scc.test.cpp
    title: test/scc.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Index Adjustment
    links: []
  bundledCode: "#line 2 \"other/adjust_index.cpp\"\n\n#include <cstddef>\n#include\
    \ <cassert>\n\nclass adjust_index {\nprivate:\n  const size_t M_stuff, M_size;\n\
    \npublic:\n  explicit adjust_index(const size_t stuff, const size_t size): \n\
    \    M_stuff(stuff), M_size(size) \n  { }\n\n  size_t operator [] (const size_t\
    \ index) const {\n    assert(index < M_size);\n    return M_stuff + index;\n \
    \ }\n  size_t to_index(const size_t fixed) const {\n    assert(fixed >= M_stuff);\n\
    \    assert(fixed < M_size + M_stuff);\n    return fixed - M_stuff;\n  }\n  size_t\
    \ size() const {\n    return M_size;\n  }\n};\n\n/**\n * @title Index Adjustment\n\
    \ */\n"
  code: "#pragma once\n\n#include <cstddef>\n#include <cassert>\n\nclass adjust_index\
    \ {\nprivate:\n  const size_t M_stuff, M_size;\n\npublic:\n  explicit adjust_index(const\
    \ size_t stuff, const size_t size): \n    M_stuff(stuff), M_size(size) \n  { }\n\
    \n  size_t operator [] (const size_t index) const {\n    assert(index < M_size);\n\
    \    return M_stuff + index;\n  }\n  size_t to_index(const size_t fixed) const\
    \ {\n    assert(fixed >= M_stuff);\n    assert(fixed < M_size + M_stuff);\n  \
    \  return fixed - M_stuff;\n  }\n  size_t size() const {\n    return M_size;\n\
    \  }\n};\n\n/**\n * @title Index Adjustment\n */"
  dependsOn: []
  isVerificationFile: false
  path: other/adjust_index.cpp
  requiredBy:
  - graph/network_simplex.cpp
  - graph/network.cpp
  - graph/two_sat.cpp
  timestamp: '2020-09-19 13:07:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/push_relabel.test.cpp
  - test/dinic.test.cpp
  - test/scc.test.cpp
  - test/network_simplex.test.cpp
documentation_of: other/adjust_index.cpp
layout: document
redirect_from:
- /library/other/adjust_index.cpp
- /library/other/adjust_index.cpp.html
title: Index Adjustment
---
