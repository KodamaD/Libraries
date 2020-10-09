---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/dinic.cpp
    title: Dinic
  - icon: ':heavy_check_mark:'
    path: graph/network.cpp
    title: Network
  - icon: ':heavy_check_mark:'
    path: other/adjust_index.cpp
    title: Index Adjustment
  - icon: ':heavy_check_mark:'
    path: other/fix_point.cpp
    title: Lambda Recursion
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/bipartitematching
    links:
    - https://judge.yosupo.jp/problem/bipartitematching
  bundledCode: "#line 1 \"test/dinic.test.cpp\"\n\n#define PROBLEM \"https://judge.yosupo.jp/problem/bipartitematching\"\
    \n\n#line 2 \"graph/network.cpp\"\n\n#line 2 \"other/adjust_index.cpp\"\n\n#include\
    \ <cstddef>\n#include <cassert>\n\nclass adjust_index {\nprivate:\n  const size_t\
    \ M_stuff, M_size;\n\npublic:\n  explicit adjust_index(const size_t stuff, const\
    \ size_t size): \n    M_stuff(stuff), M_size(size) \n  { }\n\n  size_t operator\
    \ [] (const size_t index) const {\n    assert(index < M_size);\n    return M_stuff\
    \ + index;\n  }\n  size_t to_index(const size_t fixed) const {\n    assert(fixed\
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
    \ capacity);\n  }\n};\n\n/**\n * @title Network\n */\n#line 2 \"graph/dinic.cpp\"\
    \n\n#line 2 \"other/fix_point.cpp\"\n\n#line 4 \"other/fix_point.cpp\"\n\ntemplate\
    \ <class Func>\nstruct fix_point_impl: private Func {\n  explicit constexpr fix_point_impl(Func\
    \ &&func): Func(std::forward<Func>(func)) { }\n  template <class... Args>\n  constexpr\
    \ decltype(auto) operator () (Args &&... args) const {\n    return Func::operator()(*this,\
    \ std::forward<Args>(args)...);\n  }\n};\n\ntemplate <class Func>\nconstexpr decltype(auto)\
    \ fix_point(Func &&func) {\n  return fix_point_impl<Func>(std::forward<Func>(func));\n\
    }\n\n/**\n * @title Lambda Recursion\n */\n#line 4 \"graph/dinic.cpp\"\n\n#include\
    \ <queue>\n#include <algorithm>\n#line 8 \"graph/dinic.cpp\"\n\ntemplate <class\
    \ Network>\nclass dinic {\npublic:\n  using network_type = Network;\n  using vertex_type\
    \  = typename Network::vertex_type;\n  using edge_type    = typename Network::edge_type;\n\
    \  using size_type    = typename Network::size_type;\n  using flow_type    = typename\
    \ Network::edge_type::flow_type;\n  using height_type  = uint32_t;\n\n  static_assert(std::is_integral<flow_type>::value,\
    \ \"invalid flow type :: non-integral\");\n\nprivate:\n  class residual_edge:\
    \ public edge_type {\n  public:\n    const size_type rev;\n    const bool is_rev;\n\
    \    explicit residual_edge(const edge_type &edge, const size_type rev, const\
    \ bool is_rev):\n      edge_type(edge), rev(rev), is_rev(is_rev)\n    { }\n  };\n\
    \n  class node_type {\n  public:\n    std::vector<residual_edge> edges;\n    height_type\
    \ level;\n    size_type iter;\n    node_type() = default;\n  };\n\n  flow_type\
    \ M_remain(const residual_edge &edge) {\n    return edge.capacity - edge.flow;\n\
    \  }\n  residual_edge &M_cur_edge(node_type &node) {\n    return node.edges[node.iter];\n\
    \  }\n  residual_edge &M_rev_edge(const residual_edge &edge) {\n    return M_graph[edge.dest].edges[edge.rev];\n\
    \  }\n\n  void M_bfs(const vertex_type source) {\n    for (auto &node: M_graph)\
    \ {\n      node.level = M_graph.size() + 1;\n    }\n    M_graph[source].level\
    \ = 0;\n    std::queue<vertex_type> queue;\n    queue.push(source);\n    while\
    \ (!queue.empty()) {\n      const auto vert = queue.front();\n      queue.pop();\n\
    \      for (const auto &edge: M_graph[vert].edges) {\n        if (M_remain(edge)\
    \ > 0) {\n          if (M_graph[edge.dest].level == M_graph.size() + 1) {\n  \
    \          M_graph[edge.dest].level = M_graph[vert].level + 1;\n            queue.push(edge.dest);\n\
    \          }\n        }\n      }\n    }\n  }\n\n  std::vector<node_type> M_graph;\n\
    \npublic:\n  dinic() = default;\n  explicit dinic(const network_type &net) {\n\
    \    M_graph.resize(net.size());\n    for (size_type src = 0; src < net.size();\
    \ ++src) {\n      for (const auto &edge: net[src]) {\n        M_graph[src].edges.emplace_back(edge,\
    \ M_graph[edge.dest].edges.size(), false);\n        M_graph[edge.dest].edges.emplace_back(edge.reverse(),\
    \ M_graph[src].edges.size() - 1, true);\n      }\n    }\n  }\n\n  template <bool\
    \ ValueOnly = true>\n  typename std::enable_if<ValueOnly, flow_type>::type\n \
    \ max_flow(const vertex_type source, const vertex_type sink, const bool initialize_edges\
    \ = false) {\n    assert(source < M_graph.size());\n    assert(sink < M_graph.size());\n\
    \    assert(source != sink);\n    const auto dfs = fix_point([&](const auto dfs,\
    \ \n      const vertex_type vert, const flow_type flow) -> flow_type {\n     \
    \ if (vert == sink) return flow;\n      auto &node = M_graph[vert];\n      for\
    \ (; node.iter < node.edges.size(); ++node.iter) {\n        auto &edge = M_cur_edge(node);\n\
    \        if (M_remain(edge) > 0 && node.level < M_graph[edge.dest].level) {\n\
    \          const auto push = dfs(edge.dest, std::min(flow, M_remain(edge)));\n\
    \          if (push > 0) {\n            edge.flow += push;\n            M_rev_edge(edge).flow\
    \ -= push;\n            return push;\n          }\n        }\n      }\n      return\
    \ 0;\n    });\n    flow_type max_capacity = 0;\n    for (auto &node: M_graph)\
    \ {\n      for (auto &edge: node.edges) {\n        if (initialize_edges) {\n \
    \         if (!edge.is_rev) edge.flow = 0;\n          else edge.flow = edge.capacity;\n\
    \        }\n        max_capacity = std::max(max_capacity, edge.capacity);\n  \
    \    }\n    }\n    flow_type flow = 0;\n    while (true) {\n      M_bfs(source);\n\
    \      if (M_graph[sink].level == M_graph.size() + 1) {\n        return flow;\n\
    \      }\n      for (auto &node: M_graph) {\n        node.iter = 0;\n      }\n\
    \      flow_type push;\n      while ((push = dfs(source, max_capacity)) > 0) {\n\
    \        flow += push;\n      }\n    }\n    return flow;\n  }\n\n  template <bool\
    \ ValueOnly = true>\n  typename std::enable_if<!ValueOnly, std::pair<flow_type,\
    \ network_type>>::type\n  max_flow(const vertex_type source, const vertex_type\
    \ sink, const bool initialize_edges = false) {\n    const auto flow = max_flow<true>(source,\
    \ sink, initialize_edges);\n    network_type graph;\n    graph.template add_vertices\
    \ <false>(M_graph.size());\n    for (size_type index = 0; index < M_graph.size();\
    \ ++index) {\n      for (const auto &edge: M_graph[index].edges) {\n        if\
    \ (!edge.is_rev) {\n          graph.add_edge(static_cast<edge_type>(edge));\n\
    \        }\n      }\n    }\n    return std::make_pair(flow, std::move(graph));\n\
    \  }\n};\n\n/**\n * @title Dinic\n */\n#line 6 \"test/dinic.test.cpp\"\n\n#line\
    \ 9 \"test/dinic.test.cpp\"\n#include <iostream>\n\nint main() {\n  size_t L,\
    \ R, M;\n  std::cin >> L >> R >> M;\n  network<flow_edge<int32_t>> graph;\n  const\
    \ auto S = graph.add_vertex();\n  const auto T = graph.add_vertex();\n  const\
    \ auto left = graph.add_vertices(L);\n  const auto right = graph.add_vertices(R);\n\
    \  while (M--) {\n    size_t u, v;\n    std::cin >> u >> v;\n    graph.emplace_edge(left[u],\
    \ right[v], 1);\n  }\n  for (size_t i = 0; i < L; ++i) {\n    graph.emplace_edge(S,\
    \ left[i], 1);\n  }\n  for (size_t i = 0; i < R; ++i) {\n    graph.emplace_edge(right[i],\
    \ T, 1);\n  }\n  const auto [flow, built] = dinic(graph).max_flow<false>(S, T);\n\
    \  std::cout << flow << '\\n';\n  for (size_t i = 0; i < L; ++i) {\n    for (const\
    \ auto &edge: built[left[i]]) {\n      if (edge.flow > 0) {\n        std::cout\
    \ << i << ' ' << right.to_index(edge.dest) << '\\n';\n        break;\n      }\n\
    \    }\n  }\n  return 0;\n}\n"
  code: "\n#define PROBLEM \"https://judge.yosupo.jp/problem/bipartitematching\"\n\
    \n#include \"../graph/network.cpp\"\n#include \"../graph/dinic.cpp\"\n\n#include\
    \ <cstddef>\n#include <cstdint>\n#include <iostream>\n\nint main() {\n  size_t\
    \ L, R, M;\n  std::cin >> L >> R >> M;\n  network<flow_edge<int32_t>> graph;\n\
    \  const auto S = graph.add_vertex();\n  const auto T = graph.add_vertex();\n\
    \  const auto left = graph.add_vertices(L);\n  const auto right = graph.add_vertices(R);\n\
    \  while (M--) {\n    size_t u, v;\n    std::cin >> u >> v;\n    graph.emplace_edge(left[u],\
    \ right[v], 1);\n  }\n  for (size_t i = 0; i < L; ++i) {\n    graph.emplace_edge(S,\
    \ left[i], 1);\n  }\n  for (size_t i = 0; i < R; ++i) {\n    graph.emplace_edge(right[i],\
    \ T, 1);\n  }\n  const auto [flow, built] = dinic(graph).max_flow<false>(S, T);\n\
    \  std::cout << flow << '\\n';\n  for (size_t i = 0; i < L; ++i) {\n    for (const\
    \ auto &edge: built[left[i]]) {\n      if (edge.flow > 0) {\n        std::cout\
    \ << i << ' ' << right.to_index(edge.dest) << '\\n';\n        break;\n      }\n\
    \    }\n  }\n  return 0;\n}\n"
  dependsOn:
  - graph/network.cpp
  - other/adjust_index.cpp
  - graph/dinic.cpp
  - other/fix_point.cpp
  isVerificationFile: true
  path: test/dinic.test.cpp
  requiredBy: []
  timestamp: '2020-09-27 11:10:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/dinic.test.cpp
layout: document
redirect_from:
- /verify/test/dinic.test.cpp
- /verify/test/dinic.test.cpp.html
title: test/dinic.test.cpp
---
