---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: other/fix_point.cpp
    title: Lambda Recursion
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/dinic.test.cpp
    title: test/dinic.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    document_title: Dinic
    links: []
  bundledCode: "#line 2 \"graph/dinic.cpp\"\n\n#line 2 \"other/fix_point.cpp\"\n\n\
    #include <utility>\n\ntemplate <class Func>\nstruct fix_point_impl: private Func\
    \ {\n  explicit constexpr fix_point_impl(Func &&func): Func(std::forward<Func>(func))\
    \ { }\n  template <class... Args>\n  constexpr decltype(auto) operator () (Args\
    \ &&... args) const {\n    return Func::operator()(*this, std::forward<Args>(args)...);\n\
    \  }\n};\n\ntemplate <class Func>\nconstexpr decltype(auto) fix_point(Func &&func)\
    \ {\n  return fix_point_impl<Func>(std::forward<Func>(func));\n}\n\n/**\n * @title\
    \ Lambda Recursion\n */\n#line 4 \"graph/dinic.cpp\"\n\n#include <queue>\n#include\
    \ <algorithm>\n#include <cassert>\n\ntemplate <class Network>\nclass dinic {\n\
    public:\n  using network_type = Network;\n  using vertex_type  = typename Network::vertex_type;\n\
    \  using edge_type    = typename Network::edge_type;\n  using size_type    = typename\
    \ Network::size_type;\n  using flow_type    = typename Network::edge_type::flow_type;\n\
    \  using height_type  = uint32_t;\n\n  static_assert(std::is_integral<flow_type>::value,\
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
    \  }\n};\n\n/**\n * @title Dinic\n */\n"
  code: "#pragma once\n\n#include \"../other/fix_point.cpp\"\n\n#include <queue>\n\
    #include <algorithm>\n#include <cassert>\n\ntemplate <class Network>\nclass dinic\
    \ {\npublic:\n  using network_type = Network;\n  using vertex_type  = typename\
    \ Network::vertex_type;\n  using edge_type    = typename Network::edge_type;\n\
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
    \  }\n};\n\n/**\n * @title Dinic\n */"
  dependsOn:
  - other/fix_point.cpp
  isVerificationFile: false
  path: graph/dinic.cpp
  requiredBy: []
  timestamp: '2020-09-13 16:51:07+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/dinic.test.cpp
documentation_of: graph/dinic.cpp
layout: document
redirect_from:
- /library/graph/dinic.cpp
- /library/graph/dinic.cpp.html
title: Dinic
---
