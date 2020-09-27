---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/union_find.test.cpp
    title: test/union_find.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    document_title: Disjoint Set Union
    links: []
  bundledCode: "#line 2 \"graph/union_find.cpp\"\n\n#include <cstddef>\n#include <vector>\n\
    #include <utility>\n#include <cassert>\n\nclass union_find {\npublic:\n  using\
    \ size_type = size_t;\n\nprivate:\n  class node_type {\n  public:\n    size_type\
    \ parent, size;\n    node_type(size_type parent): \n      parent(parent), size(1)\
    \ \n    { }\n  };\n\n  size_type M_components;\n  std::vector<node_type> M_forest;\n\
    \npublic:\n  union_find() = default;\n  explicit union_find(const size_type size)\
    \ { initialize(size); }\n\n  void initialize(const size_type size) {\n    clear();\n\
    \    M_components = size;\n    M_forest.reserve(size);\n    for (size_type index\
    \ = 0; index < size; ++index) {\n      M_forest.emplace_back(index);\n    }\n\
    \  }\n\n  size_type find_parent(const size_type node) {\n    assert(node < size());\n\
    \    size_type &parent = M_forest[node].parent;\n    if (node == parent) return\
    \ node;\n    return parent = find_parent(parent);\n  }\n  size_type count_components()\
    \ const { \n    return M_components; \n  }\n  size_type component_size(const size_type\
    \ node) { \n    assert(node < size());\n    return M_forest[find_parent(node)].size;\n\
    \  }\n\n  bool unite(size_type node1, size_type node2) {\n    assert(node1 < size());\n\
    \    assert(node2 < size());\n    node1 = find_parent(node1);\n    node2 = find_parent(node2);\n\
    \    if (node1 == node2) return false;\n    if (M_forest[node1].size < M_forest[node2].size)\
    \ {\n      std::swap(node1, node2);\n    }\n    M_forest[node1].size += M_forest[node2].size;\n\
    \    M_forest[node2].parent = node1;\n    --M_components;\n    return true;\n\
    \  }\n  bool same_component(const size_type node1, const size_type node2) { \n\
    \    assert(node1 < size());\n    assert(node2 < size());\n    return find_parent(node1)\
    \ == find_parent(node2); \n  }\n\n  size_type size() const {\n    return M_forest.size();\n\
    \  }\n  bool empty() const {\n    return M_forest.empty();\n  }\n  void clear()\
    \ {\n    M_components = 0;\n    M_forest.clear();\n    M_forest.shrink_to_fit();\n\
    \  }\n};\n\n/**\n * @title Disjoint Set Union\n */\n"
  code: "#pragma once\n\n#include <cstddef>\n#include <vector>\n#include <utility>\n\
    #include <cassert>\n\nclass union_find {\npublic:\n  using size_type = size_t;\n\
    \nprivate:\n  class node_type {\n  public:\n    size_type parent, size;\n    node_type(size_type\
    \ parent): \n      parent(parent), size(1) \n    { }\n  };\n\n  size_type M_components;\n\
    \  std::vector<node_type> M_forest;\n\npublic:\n  union_find() = default;\n  explicit\
    \ union_find(const size_type size) { initialize(size); }\n\n  void initialize(const\
    \ size_type size) {\n    clear();\n    M_components = size;\n    M_forest.reserve(size);\n\
    \    for (size_type index = 0; index < size; ++index) {\n      M_forest.emplace_back(index);\n\
    \    }\n  }\n\n  size_type find_parent(const size_type node) {\n    assert(node\
    \ < size());\n    size_type &parent = M_forest[node].parent;\n    if (node ==\
    \ parent) return node;\n    return parent = find_parent(parent);\n  }\n  size_type\
    \ count_components() const { \n    return M_components; \n  }\n  size_type component_size(const\
    \ size_type node) { \n    assert(node < size());\n    return M_forest[find_parent(node)].size;\n\
    \  }\n\n  bool unite(size_type node1, size_type node2) {\n    assert(node1 < size());\n\
    \    assert(node2 < size());\n    node1 = find_parent(node1);\n    node2 = find_parent(node2);\n\
    \    if (node1 == node2) return false;\n    if (M_forest[node1].size < M_forest[node2].size)\
    \ {\n      std::swap(node1, node2);\n    }\n    M_forest[node1].size += M_forest[node2].size;\n\
    \    M_forest[node2].parent = node1;\n    --M_components;\n    return true;\n\
    \  }\n  bool same_component(const size_type node1, const size_type node2) { \n\
    \    assert(node1 < size());\n    assert(node2 < size());\n    return find_parent(node1)\
    \ == find_parent(node2); \n  }\n\n  size_type size() const {\n    return M_forest.size();\n\
    \  }\n  bool empty() const {\n    return M_forest.empty();\n  }\n  void clear()\
    \ {\n    M_components = 0;\n    M_forest.clear();\n    M_forest.shrink_to_fit();\n\
    \  }\n};\n\n/**\n * @title Disjoint Set Union\n */"
  dependsOn: []
  isVerificationFile: false
  path: graph/union_find.cpp
  requiredBy: []
  timestamp: '2020-09-27 11:10:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/union_find.test.cpp
documentation_of: graph/union_find.cpp
layout: document
redirect_from:
- /library/graph/union_find.cpp
- /library/graph/union_find.cpp.html
title: Disjoint Set Union
---
