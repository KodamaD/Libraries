---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/lca.test.cpp
    title: test/lca.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/vertex_set_path_sum.test.cpp
    title: test/vertex_set_path_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Heavy-Light Decomposition
    links: []
  bundledCode: "#line 2 \"graph/heavy_light_decomposition.cpp\"\n\n#include <cstddef>\n\
    #include <vector>\n#include <utility>\n#include <cassert>\n\nclass heavy_light_decomposition\
    \ {\npublic:\n  using size_type = size_t;\n\nprivate:\n  std::vector<std::vector<size_type>>\
    \ M_graph;\n  std::vector<size_type> M_size, M_parent, M_head;\n  size_type M_index;\n\
    \n  void M_calc_subtree(size_type u, size_type p) {\n    M_size[u] = 1;\n    for\
    \ (auto v: M_graph[u]) {\n      if (v != p) {\n        M_calc_subtree(v, u);\n\
    \        M_size[u] += M_size[v];\n      }\n    }\n  }\n\n  void M_decompose(size_type\
    \ u, size_type p, size_type h) {\n    label[u] = M_index;\n    M_head[u] = h;\n\
    \    M_parent[u] = p;\n    ++M_index;\n    size_type max = 0, heavy = -1;\n  \
    \  for (auto v: M_graph[u]) {\n      if (v != p) {\n        if (max < M_size[v])\
    \ {\n          max = M_size[v];\n          heavy = v;\n        }\n      }\n  \
    \  }\n    if (heavy == size_type(-1)) return;\n    M_decompose(heavy, u, h);\n\
    \    for (auto v: M_graph[u]) {\n      if (v != p && v != heavy) {\n        M_decompose(v,\
    \ u, v);\n      }\n    }\n  }\n\npublic:\n  std::vector<size_type> label;\n\n\
    \  heavy_light_decomposition() { }\n  explicit heavy_light_decomposition(size_type\
    \ size) { initialize(size); }\n\n  void initialize(size_type size) {\n    clear();\n\
    \    M_index = 0;\n    M_graph.assign(size, { });\n    M_size.assign(size, 0);\n\
    \    M_parent.assign(size, 0);\n    M_head.assign(size, 0);\n    label.assign(size,\
    \ 0);\n  }\n  void construct(size_type root = 0) {\n    assert(root < M_graph.size());\n\
    \    M_calc_subtree(root, -1);\n    M_decompose(root, -1, root);\n  }\n  void\
    \ add_edge(size_type u, size_type v) {\n    assert(u < M_graph.size());\n    assert(v\
    \ < M_graph.size());\n    assert(u != v);\n    M_graph[u].push_back(v);\n    M_graph[v].push_back(u);\n\
    \  }\n\n  template <class Func> \n  void each_edge(size_type u, size_type v, const\
    \ Func &func) const {\n    assert(u < M_graph.size());\n    assert(v < M_graph.size());\n\
    \    while (true) {\n      if (label[u] > label[v]) {\n        std::swap(u, v);\n\
    \      }\n      if (M_head[u] == M_head[v]) {\n        if (label[u] + 1 <= label[v])\
    \ {\n          func(label[u] + 1, label[v]);\n        }\n        return;\n   \
    \   }\n      func(label[M_head[v]], label[v]);\n      v = M_parent[M_head[v]];\n\
    \    }\n  }\n\n  template <class Func> \n  void each_vertex(size_type u, size_type\
    \ v, const Func &func) const {\n    assert(u < M_graph.size());\n    assert(v\
    \ < M_graph.size());\n    while (true) {\n      if (label[u] > label[v]) {\n \
    \       std::swap(u, v);\n      }\n      if (M_head[u] == M_head[v]) {\n     \
    \   func(label[u], label[v]);\n        return;\n      }\n      func(label[M_head[v]],\
    \ label[v]);\n      v = M_parent[M_head[v]];\n    }\n  }\n\n  size_type lca(size_type\
    \ u, size_type v) const {\n    assert(u < M_graph.size());\n    assert(v < M_graph.size());\n\
    \    if (label[u] > label[v]) {\n      std::swap(u, v);\n    }\n    while (label[u]\
    \ <= label[v]) {\n      if (M_head[u] == M_head[v]) {\n        return u;\n   \
    \   }\n      v = M_parent[M_head[v]];\n    }\n    return v;\n  }\n\n  size_type\
    \ size() const {\n    return M_graph.size();\n  }\n  bool empty() const {\n  \
    \  return M_graph.empty();\n  }\n  void clear() {\n    M_index = 0;\n    M_graph.clear();\n\
    \    M_graph.shrink_to_fit();\n    M_size.clear();\n    M_size.shrink_to_fit();\n\
    \    M_parent.clear();\n    M_parent.shrink_to_fit();\n    M_head.clear();\n \
    \   M_head.shrink_to_fit();\n    label.clear();\n    label.shrink_to_fit();\n\
    \  }\n};\n\n/**\n * @title Heavy-Light Decomposition\n */\n"
  code: "#pragma once\n\n#include <cstddef>\n#include <vector>\n#include <utility>\n\
    #include <cassert>\n\nclass heavy_light_decomposition {\npublic:\n  using size_type\
    \ = size_t;\n\nprivate:\n  std::vector<std::vector<size_type>> M_graph;\n  std::vector<size_type>\
    \ M_size, M_parent, M_head;\n  size_type M_index;\n\n  void M_calc_subtree(size_type\
    \ u, size_type p) {\n    M_size[u] = 1;\n    for (auto v: M_graph[u]) {\n    \
    \  if (v != p) {\n        M_calc_subtree(v, u);\n        M_size[u] += M_size[v];\n\
    \      }\n    }\n  }\n\n  void M_decompose(size_type u, size_type p, size_type\
    \ h) {\n    label[u] = M_index;\n    M_head[u] = h;\n    M_parent[u] = p;\n  \
    \  ++M_index;\n    size_type max = 0, heavy = -1;\n    for (auto v: M_graph[u])\
    \ {\n      if (v != p) {\n        if (max < M_size[v]) {\n          max = M_size[v];\n\
    \          heavy = v;\n        }\n      }\n    }\n    if (heavy == size_type(-1))\
    \ return;\n    M_decompose(heavy, u, h);\n    for (auto v: M_graph[u]) {\n   \
    \   if (v != p && v != heavy) {\n        M_decompose(v, u, v);\n      }\n    }\n\
    \  }\n\npublic:\n  std::vector<size_type> label;\n\n  heavy_light_decomposition()\
    \ { }\n  explicit heavy_light_decomposition(size_type size) { initialize(size);\
    \ }\n\n  void initialize(size_type size) {\n    clear();\n    M_index = 0;\n \
    \   M_graph.assign(size, { });\n    M_size.assign(size, 0);\n    M_parent.assign(size,\
    \ 0);\n    M_head.assign(size, 0);\n    label.assign(size, 0);\n  }\n  void construct(size_type\
    \ root = 0) {\n    assert(root < M_graph.size());\n    M_calc_subtree(root, -1);\n\
    \    M_decompose(root, -1, root);\n  }\n  void add_edge(size_type u, size_type\
    \ v) {\n    assert(u < M_graph.size());\n    assert(v < M_graph.size());\n   \
    \ assert(u != v);\n    M_graph[u].push_back(v);\n    M_graph[v].push_back(u);\n\
    \  }\n\n  template <class Func> \n  void each_edge(size_type u, size_type v, const\
    \ Func &func) const {\n    assert(u < M_graph.size());\n    assert(v < M_graph.size());\n\
    \    while (true) {\n      if (label[u] > label[v]) {\n        std::swap(u, v);\n\
    \      }\n      if (M_head[u] == M_head[v]) {\n        if (label[u] + 1 <= label[v])\
    \ {\n          func(label[u] + 1, label[v]);\n        }\n        return;\n   \
    \   }\n      func(label[M_head[v]], label[v]);\n      v = M_parent[M_head[v]];\n\
    \    }\n  }\n\n  template <class Func> \n  void each_vertex(size_type u, size_type\
    \ v, const Func &func) const {\n    assert(u < M_graph.size());\n    assert(v\
    \ < M_graph.size());\n    while (true) {\n      if (label[u] > label[v]) {\n \
    \       std::swap(u, v);\n      }\n      if (M_head[u] == M_head[v]) {\n     \
    \   func(label[u], label[v]);\n        return;\n      }\n      func(label[M_head[v]],\
    \ label[v]);\n      v = M_parent[M_head[v]];\n    }\n  }\n\n  size_type lca(size_type\
    \ u, size_type v) const {\n    assert(u < M_graph.size());\n    assert(v < M_graph.size());\n\
    \    if (label[u] > label[v]) {\n      std::swap(u, v);\n    }\n    while (label[u]\
    \ <= label[v]) {\n      if (M_head[u] == M_head[v]) {\n        return u;\n   \
    \   }\n      v = M_parent[M_head[v]];\n    }\n    return v;\n  }\n\n  size_type\
    \ size() const {\n    return M_graph.size();\n  }\n  bool empty() const {\n  \
    \  return M_graph.empty();\n  }\n  void clear() {\n    M_index = 0;\n    M_graph.clear();\n\
    \    M_graph.shrink_to_fit();\n    M_size.clear();\n    M_size.shrink_to_fit();\n\
    \    M_parent.clear();\n    M_parent.shrink_to_fit();\n    M_head.clear();\n \
    \   M_head.shrink_to_fit();\n    label.clear();\n    label.shrink_to_fit();\n\
    \  }\n};\n\n/**\n * @title Heavy-Light Decomposition\n */"
  dependsOn: []
  isVerificationFile: false
  path: graph/heavy_light_decomposition.cpp
  requiredBy: []
  timestamp: '2020-09-09 18:26:02+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/vertex_set_path_sum.test.cpp
  - test/lca.test.cpp
documentation_of: graph/heavy_light_decomposition.cpp
layout: document
redirect_from:
- /library/graph/heavy_light_decomposition.cpp
- /library/graph/heavy_light_decomposition.cpp.html
title: Heavy-Light Decomposition
---