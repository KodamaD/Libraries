---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/adjust_index.cpp
    title: Index Adjustment
  _extendedRequiredBy:
  - icon: ':warning:'
    path: graph/two_sat.cpp
    title: Two Sat
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/dinic.test.cpp
    title: test/dinic.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/push_relabel.test.cpp
    title: test/push_relabel.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/scc.test.cpp
    title: test/scc.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Network
    links: []
  bundledCode: "#line 2 \"graph/network.cpp\"\n\n#line 2 \"other/adjust_index.cpp\"\
    \n\n#include <cstddef>\n#include <cassert>\n\nclass adjust_index {\nprivate:\n\
    \  const size_t M_stuff, M_size;\n\npublic:\n  explicit adjust_index(const size_t\
    \ stuff, const size_t size): \n    M_stuff(stuff), M_size(size) \n  { }\n\n  size_t\
    \ operator [] (const size_t index) const {\n    assert(index < M_size);\n    return\
    \ M_stuff + index;\n  }\n  size_t to_index(const size_t fixed) const {\n    assert(fixed\
    \ >= M_stuff);\n    assert(fixed < M_size + M_stuff);\n    return fixed - M_stuff;\n\
    \  }\n  size_t size() const {\n    return M_size;\n  }\n};\n\n/**\n * @title Index\
    \ Adjustment\n */\n#line 4 \"graph/network.cpp\"\n\n#line 6 \"graph/network.cpp\"\
    \n#include <cstdint>\n#include <vector>\n#include <numeric>\n#include <utility>\n\
    #include <type_traits>\n#line 12 \"graph/network.cpp\"\n\ntemplate <class Edge>\n\
    class network {\npublic:\n  using vertex_type = typename Edge::vertex_type;\n\
    \  using edge_type   = Edge;\n  using size_type   = size_t;\n\nprotected:\n  std::vector<std::vector<edge_type>>\
    \ M_graph;\n\npublic:\n  explicit network() = default;\n  explicit network(const\
    \ size_type size) { add_vertices<false>(size); }\n\n  template <bool ReturnsIndex\
    \ = true>\n  typename std::enable_if<ReturnsIndex, vertex_type>::type add_vertex()\
    \ {\n    vertex_type res = M_graph.size();\n    M_graph.push_back({ });\n    return\
    \ res;\n  }\n  template <bool ReturnsIndex = true>\n  typename std::enable_if<!ReturnsIndex,\
    \ void>::type add_vertex() {\n    M_graph.push_back({ });\n  }\n\n  template <bool\
    \ ReturnsIndices = true>\n  typename std::enable_if<ReturnsIndices, adjust_index>::type\
    \ \n  add_vertices(const size_type size) {\n    size_type cur = M_graph.size();\n\
    \    M_graph.resize(cur + size);\n    return adjust_index(cur, size);\n  }\n \
    \ template <bool ReturnsIndices = true>\n  typename std::enable_if<!ReturnsIndices,\
    \ void>::type \n  add_vertices(const size_type size) {\n    size_type cur = M_graph.size();\n\
    \    M_graph.resize(cur + size);\n  }\n  \n  void add_edge(const edge_type &edge)\
    \ {\n    M_graph[edge.source].push_back(edge);\n  }\n  template <class... Args>\n\
    \  void emplace_edge(const vertex_type src, Args&&... args) {\n    M_graph[src].emplace_back(src,\
    \ std::forward<Args>(args)...);\n  }\n\n  std::vector<edge_type> &operator []\
    \ (const vertex_type vert) {\n    assert(vert < size());\n    return M_graph[vert];\n\
    \  }\n  const std::vector<edge_type> &operator [] (const vertex_type vert) const\
    \ {\n    assert(vert < size());\n    return M_graph[vert];\n  }\n\n  size_type\
    \ size() const {\n    return M_graph.size();\n  }\n  bool empty() const {\n  \
    \  return M_graph.empty();\n  }\n  void clear() {\n    M_graph.clear();\n    M_graph.shrink_to_fit();\n\
    \  }\n};\n\nclass base_edge {\npublic:\n  using vertex_type = uint32_t;\n\n  const\
    \ vertex_type source, dest;\n  explicit base_edge(const vertex_type source, const\
    \ vertex_type dest): \n    source(source), dest(dest) \n  { }\n\n  base_edge reverse()\
    \ const {\n    return base_edge(dest, source);\n  }\n};\n\ntemplate <class Flow>\n\
    class flow_edge: public base_edge {\npublic:\n  using vertex_type = typename base_edge::vertex_type;\n\
    \  using flow_type   = Flow;\n\n  flow_type flow;\n  const flow_type capacity;\n\
    \  explicit flow_edge(const base_edge &edge, const flow_type capacity):\n    base_edge(edge),\
    \ flow(0), capacity(capacity)\n  { }\n\n  explicit flow_edge(const base_edge &edge,\
    \ const flow_type flow, const flow_type capacity):\n    base_edge(edge), flow(flow),\
    \ capacity(capacity)\n  { }\n  explicit flow_edge(const vertex_type source, const\
    \ vertex_type dest, const flow_type capacity):\n    base_edge(source, dest), flow(0),\
    \ capacity(capacity)\n  { }\n  explicit flow_edge(const vertex_type source, const\
    \ vertex_type dest, const flow_type flow, const flow_type capacity):\n    base_edge(source,\
    \ dest), flow(flow), capacity(capacity)\n  { }\n  flow_edge reverse() const {\n\
    \    return flow_edge(static_cast<base_edge>(*this).reverse(), capacity - flow,\
    \ capacity);\n  }\n};\n\n/**\n * @title Network\n */\n"
  code: "#pragma once\n\n#include \"../other/adjust_index.cpp\"\n\n#include <cstddef>\n\
    #include <cstdint>\n#include <vector>\n#include <numeric>\n#include <utility>\n\
    #include <type_traits>\n#include <cassert>\n\ntemplate <class Edge>\nclass network\
    \ {\npublic:\n  using vertex_type = typename Edge::vertex_type;\n  using edge_type\
    \   = Edge;\n  using size_type   = size_t;\n\nprotected:\n  std::vector<std::vector<edge_type>>\
    \ M_graph;\n\npublic:\n  explicit network() = default;\n  explicit network(const\
    \ size_type size) { add_vertices<false>(size); }\n\n  template <bool ReturnsIndex\
    \ = true>\n  typename std::enable_if<ReturnsIndex, vertex_type>::type add_vertex()\
    \ {\n    vertex_type res = M_graph.size();\n    M_graph.push_back({ });\n    return\
    \ res;\n  }\n  template <bool ReturnsIndex = true>\n  typename std::enable_if<!ReturnsIndex,\
    \ void>::type add_vertex() {\n    M_graph.push_back({ });\n  }\n\n  template <bool\
    \ ReturnsIndices = true>\n  typename std::enable_if<ReturnsIndices, adjust_index>::type\
    \ \n  add_vertices(const size_type size) {\n    size_type cur = M_graph.size();\n\
    \    M_graph.resize(cur + size);\n    return adjust_index(cur, size);\n  }\n \
    \ template <bool ReturnsIndices = true>\n  typename std::enable_if<!ReturnsIndices,\
    \ void>::type \n  add_vertices(const size_type size) {\n    size_type cur = M_graph.size();\n\
    \    M_graph.resize(cur + size);\n  }\n  \n  void add_edge(const edge_type &edge)\
    \ {\n    M_graph[edge.source].push_back(edge);\n  }\n  template <class... Args>\n\
    \  void emplace_edge(const vertex_type src, Args&&... args) {\n    M_graph[src].emplace_back(src,\
    \ std::forward<Args>(args)...);\n  }\n\n  std::vector<edge_type> &operator []\
    \ (const vertex_type vert) {\n    assert(vert < size());\n    return M_graph[vert];\n\
    \  }\n  const std::vector<edge_type> &operator [] (const vertex_type vert) const\
    \ {\n    assert(vert < size());\n    return M_graph[vert];\n  }\n\n  size_type\
    \ size() const {\n    return M_graph.size();\n  }\n  bool empty() const {\n  \
    \  return M_graph.empty();\n  }\n  void clear() {\n    M_graph.clear();\n    M_graph.shrink_to_fit();\n\
    \  }\n};\n\nclass base_edge {\npublic:\n  using vertex_type = uint32_t;\n\n  const\
    \ vertex_type source, dest;\n  explicit base_edge(const vertex_type source, const\
    \ vertex_type dest): \n    source(source), dest(dest) \n  { }\n\n  base_edge reverse()\
    \ const {\n    return base_edge(dest, source);\n  }\n};\n\ntemplate <class Flow>\n\
    class flow_edge: public base_edge {\npublic:\n  using vertex_type = typename base_edge::vertex_type;\n\
    \  using flow_type   = Flow;\n\n  flow_type flow;\n  const flow_type capacity;\n\
    \  explicit flow_edge(const base_edge &edge, const flow_type capacity):\n    base_edge(edge),\
    \ flow(0), capacity(capacity)\n  { }\n\n  explicit flow_edge(const base_edge &edge,\
    \ const flow_type flow, const flow_type capacity):\n    base_edge(edge), flow(flow),\
    \ capacity(capacity)\n  { }\n  explicit flow_edge(const vertex_type source, const\
    \ vertex_type dest, const flow_type capacity):\n    base_edge(source, dest), flow(0),\
    \ capacity(capacity)\n  { }\n  explicit flow_edge(const vertex_type source, const\
    \ vertex_type dest, const flow_type flow, const flow_type capacity):\n    base_edge(source,\
    \ dest), flow(flow), capacity(capacity)\n  { }\n  flow_edge reverse() const {\n\
    \    return flow_edge(static_cast<base_edge>(*this).reverse(), capacity - flow,\
    \ capacity);\n  }\n};\n\n/**\n * @title Network\n */"
  dependsOn:
  - other/adjust_index.cpp
  isVerificationFile: false
  path: graph/network.cpp
  requiredBy:
  - graph/two_sat.cpp
  timestamp: '2020-09-27 11:10:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/dinic.test.cpp
  - test/push_relabel.test.cpp
  - test/scc.test.cpp
documentation_of: graph/network.cpp
layout: document
redirect_from:
- /library/graph/network.cpp
- /library/graph/network.cpp.html
title: Network
---
