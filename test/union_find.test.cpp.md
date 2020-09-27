---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/union_find.cpp
    title: Disjoint Set Union
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/unionfind
    links:
    - https://judge.yosupo.jp/problem/unionfind
  bundledCode: "#line 1 \"test/union_find.test.cpp\"\n\n#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\
    \n\n#line 2 \"graph/union_find.cpp\"\n\n#include <cstddef>\n#include <vector>\n\
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
    \  }\n};\n\n/**\n * @title Disjoint Set Union\n */\n#line 5 \"test/union_find.test.cpp\"\
    \n\n#line 7 \"test/union_find.test.cpp\"\n#include <iostream>\n\nint main() {\n\
    \  size_t N, Q;\n  std::cin >> N >> Q;\n  union_find dsu(N);\n  while (Q--) {\n\
    \    size_t t, u, v;\n    std::cin >> t >> u >> v;\n    if (t == 0) {\n      dsu.unite(u,\
    \ v);\n    }\n    else {\n      std::cout << dsu.same_component(u, v) << '\\n';\n\
    \    }\n  }\n}\n"
  code: "\n#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\n\n#include\
    \ \"../graph/union_find.cpp\"\n\n#include <cstddef>\n#include <iostream>\n\nint\
    \ main() {\n  size_t N, Q;\n  std::cin >> N >> Q;\n  union_find dsu(N);\n  while\
    \ (Q--) {\n    size_t t, u, v;\n    std::cin >> t >> u >> v;\n    if (t == 0)\
    \ {\n      dsu.unite(u, v);\n    }\n    else {\n      std::cout << dsu.same_component(u,\
    \ v) << '\\n';\n    }\n  }\n}\n"
  dependsOn:
  - graph/union_find.cpp
  isVerificationFile: true
  path: test/union_find.test.cpp
  requiredBy: []
  timestamp: '2020-09-27 11:10:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/union_find.test.cpp
layout: document
redirect_from:
- /verify/test/union_find.test.cpp
- /verify/test/union_find.test.cpp.html
title: test/union_find.test.cpp
---
