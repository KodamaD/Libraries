---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/push_relabel.test.cpp
    title: test/push_relabel.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    document_title: Push Relabel
    links: []
  bundledCode: "#line 2 \"graph/push_relabel.cpp\"\n\n#include <queue>\n#include <algorithm>\n\
    \nnamespace push_relabel_detail {\n\nclass stack {\nprivate:\n  const size_t M_size;\n\
    \  std::vector<size_t> M_stack;\n\npublic:\n  explicit stack(const size_t size):\n\
    \    M_size(size), M_stack(size * 2)\n  { clear(); }\n\n  size_t top(const size_t\
    \ height) const {\n    return M_stack[M_size + height];\n  }\n  bool empty(const\
    \ size_t height) const { \n    return M_stack[M_size + height] == M_size + height;\
    \ \n  }\n  void pop(const size_t height) {\n    M_stack[M_size + height] = M_stack[M_stack[M_size\
    \ + height]];\n  }\n  void push(const size_t height, const size_t node) {\n  \
    \  M_stack[node] = M_stack[M_size + height];\n    M_stack[M_size + height] = node;\n\
    \  }\n  void clear() {\n    std::iota(M_stack.begin() + M_size, M_stack.end(),\
    \ M_size);\n  }\n};\n\nclass list {\nprivate:\n  const size_t M_size;\n  std::vector<std::pair<size_t,\
    \ size_t>> M_list;\n\npublic:\n  explicit list(const size_t size):\n    M_size(size),\
    \ M_list(size * 2)\n  { clear(); }\n\n  bool empty(const size_t height) {\n  \
    \  return M_list[M_size + height].second == M_size + height;\n  }\n  bool more_than_one(const\
    \ size_t height) {\n    return M_list[M_size + height].first != M_list[M_size\
    \ + height].second;\n  }\n\n  void insert(const size_t height, const size_t node)\
    \ {\n    M_list[node].first = M_list[M_size + height].first;\n    M_list[node].second\
    \ = M_size + height;\n    M_list[M_list[M_size + height].first].second = node;\n\
    \    M_list[M_size + height].first = node;\n  }\n  void erase(const size_t node)\
    \ {\n    M_list[M_list[node].first].second = M_list[node].second;\n    M_list[M_list[node].second].first\
    \ = M_list[node].first;\n  }\n  \n  void clear() {\n    for (size_t index = M_size;\
    \ index < M_size * 2; ++index) {\n      M_list[index].first = M_list[index].second\
    \ = index;\n    }\n  }\n  void clear(const size_t height) {\n    const size_t\
    \ index = M_size + height;\n    M_list[index].first = M_list[index].second = index;\n\
    \  }\n  template <class Func>\n  void apply_all(const size_t height, Func &&func)\
    \ {\n    size_t index = M_list[M_size + height].second;\n    while (index < M_size)\
    \ {\n      func(index);\n      index = M_list[index].second;\n    }\n  }\n};\n\
    \n}\n\ntemplate <class Network>\nclass push_relabel {\npublic:\n  using network_type\
    \ = Network;\n  using vertex_type  = typename Network::vertex_type;\n  using edge_type\
    \    = typename Network::edge_type;\n  using size_type    = typename Network::size_type;\n\
    \  using flow_type    = typename Network::edge_type::flow_type;\n  using height_type\
    \  = uint32_t;\n\n  static_assert(std::is_integral<flow_type>::value, \"invalid\
    \ flow type :: non-integral\");\n\nprivate:\n  class residual_edge: public edge_type\
    \ {\n  public:\n    const size_type rev;\n    const bool is_rev;\n    explicit\
    \ residual_edge(const edge_type &edge, const size_type rev, const bool is_rev):\n\
    \      edge_type(edge), rev(rev), is_rev(is_rev)\n    { }\n  };\n\n  class node_type\
    \ {\n  public:\n    std::vector<residual_edge> edges;\n    flow_type excess;\n\
    \    height_type height;\n    size_type iter;\n    node_type() = default;\n  };\n\
    \n  flow_type M_remain(const residual_edge &edge) {\n    return edge.capacity\
    \ - edge.flow;\n  }\n  residual_edge &M_cur_edge(node_type &node) {\n    return\
    \ node.edges[node.iter];\n  }\n  residual_edge &M_rev_edge(const residual_edge\
    \ &edge) {\n    return M_graph[edge.dest].edges[edge.rev];\n  }\n\n  void M_push(node_type\
    \ &node, residual_edge &edge) {\n    const auto flow = std::min(node.excess, M_remain(edge));\n\
    \    edge.flow += flow;\n    node.excess -= flow;\n    M_rev_edge(edge).flow -=\
    \ flow;\n    M_graph[edge.dest].excess += flow;\n  }\n  void M_relabel(node_type\
    \ &node) {\n    height_type min = M_graph.size() + 1;\n    for (const auto &edge:\
    \ node.edges) {\n      if (M_remain(edge) > 0 && min > M_graph[edge.dest].height\
    \ + 1) {\n        min = M_graph[edge.dest].height + 1;\n      }\n    }\n    node.height\
    \ = min;\n  }\n\n  void M_reverse_bfs(const vertex_type source) {\n    for (auto\
    \ &node: M_graph) {\n      node.height = M_graph.size() + 1;\n    }\n    M_graph[source].height\
    \ = 0;\n    std::queue<vertex_type> queue;\n    queue.push(source);\n    while\
    \ (!queue.empty()) {\n      const auto vert = queue.front();\n      queue.pop();\n\
    \      for (const auto &edge: M_graph[vert].edges) {\n        if (M_remain(M_rev_edge(edge))\
    \ > 0) {\n          if (M_graph[edge.dest].height == M_graph.size() + 1) {\n \
    \           M_graph[edge.dest].height = M_graph[vert].height + 1;\n          \
    \  queue.push(edge.dest);\n          }\n        }\n      }\n    }\n  }\n\n  std::vector<node_type>\
    \ M_graph;\n\npublic:\n  push_relabel() = default;\n  explicit push_relabel(const\
    \ network_type &net) {\n    M_graph.resize(net.size());\n    for (size_type src\
    \ = 0; src < net.size(); ++src) {\n      for (const auto &edge: net[src]) {\n\
    \        M_graph[src].edges.emplace_back(edge, M_graph[edge.dest].edges.size(),\
    \ false);\n        M_graph[edge.dest].edges.emplace_back(edge.reverse(), M_graph[src].edges.size()\
    \ - 1, true);\n      }\n    }\n  }\n\n  template <bool ValueOnly = true>\n  typename\
    \ std::enable_if<ValueOnly, flow_type>::type\n  max_flow(const vertex_type source,\
    \ const vertex_type sink, const bool initialize_edges = false) {\n    assert(source\
    \ < M_graph.size());\n    assert(sink < M_graph.size());\n    assert(source !=\
    \ sink);\n    push_relabel_detail::stack active(M_graph.size());\n    push_relabel_detail::list\
    \ level(M_graph.size());\n    height_type min_gap, max_active;\n    for (auto\
    \ &node: M_graph) {\n      node.excess = 0;\n      node.iter = 0;\n      for (auto\
    \ &edge: node.edges) {\n        if (initialize_edges) {\n          if (!edge.is_rev)\
    \ edge.flow = 0;\n          else edge.flow = edge.capacity;\n        }\n     \
    \ }\n    }\n    M_reverse_bfs(sink);\n    if (M_graph[source].height == M_graph.size()\
    \ + 1) {\n      return 0;\n    }\n    for (auto &edge: M_graph[source].edges)\
    \ {\n      M_graph[source].excess += M_remain(edge);\n      M_push(M_graph[source],\
    \ edge);\n    }\n    M_graph[source].height = M_graph.size();\n    min_gap = M_graph.size();\n\
    \    max_active = 0;\n    for (size_type index = 0; index < M_graph.size(); ++index)\
    \ {\n      const auto &node = M_graph[index];\n      if (node.height < M_graph.size())\
    \ {\n        if (node.excess > 0 && index != sink) {\n          active.push(node.height,\
    \ index);\n          max_active = std::max(max_active, node.height);\n       \
    \ }\n        level.insert(node.height, index);\n      }\n    }\n    for (size_type\
    \ index = 0; index < M_graph.size(); ++index) {\n      if (level.empty(index))\
    \ {\n        min_gap = index;\n        break;\n      }\n    }\n    while (max_active\
    \ > 0) {\n      if (active.empty(max_active)) {\n        --max_active;\n     \
    \   continue;\n      }\n      const auto vert = active.top(max_active);\n    \
    \  auto &node = M_graph[vert];\n      active.pop(max_active);\n      while (true)\
    \ {\n        auto &edge = M_cur_edge(node);\n        const auto &dest = M_graph[edge.dest];\n\
    \        if (M_remain(edge) > 0 && node.height == dest.height + 1) {\n       \
    \   if (dest.excess == 0 && edge.dest != sink) {\n            active.push(dest.height,\
    \ edge.dest);\n            max_active = std::max(max_active, dest.height);\n \
    \         }\n          M_push(node, edge);\n          if (node.excess == 0) {\n\
    \            break;\n          }\n        }\n        node.iter++;\n        if\
    \ (node.iter == node.edges.size()) {\n          node.iter = 0;\n          if (level.more_than_one(node.height))\
    \ {\n            level.erase(vert);\n            M_relabel(node);\n          \
    \  if (node.height > min_gap) {\n              node.height = M_graph.size() +\
    \ 1;\n              break;\n            }\n            if (node.height == min_gap)\
    \ {\n              min_gap++;\n            }\n            level.insert(node.height,\
    \ vert);\n          }\n          else {\n            const height_type old_gap\
    \ = min_gap;\n            min_gap = node.height;\n            for (height_type\
    \ index = node.height; index < old_gap; ++index) {\n              level.apply_all(index,\
    \ [&](const vertex_type vert) {\n                M_graph[vert].height = M_graph.size()\
    \ + 1;\n              });\n              level.clear(index);\n            }\n\
    \            break;\n          }\n        }\n      }\n      max_active = std::min(max_active,\
    \ min_gap - 1);\n    }\n    return M_graph[sink].excess;\n  }\n\n  template <bool\
    \ ValueOnly = true>\n  typename std::enable_if<!ValueOnly, std::pair<flow_type,\
    \ network_type>>::type\n  max_flow(const vertex_type source, const vertex_type\
    \ sink, const bool initialize_edges = false) {\n    const auto flow = max_flow<true>(source,\
    \ sink, initialize_edges);\n    std::queue<vertex_type> active;\n    M_reverse_bfs(source);\n\
    \    for (vertex_type index = 0; index < M_graph.size(); ++index) {\n      const\
    \ auto &node = M_graph[index];\n      if (node.excess > 0 && node.height < M_graph.size()\
    \ && index != sink) {\n        active.push(index);\n      }\n    }\n    while\
    \ (!active.empty()) {\n      auto &node = M_graph[active.front()];\n      active.pop();\n\
    \      while (node.excess > 0) {\n        auto &edge = M_cur_edge(node);\n   \
    \     const auto &dest = M_graph[edge.dest];\n        if (M_remain(edge) > 0 &&\
    \ node.height == dest.height + 1) {\n          if (dest.excess == 0 && edge.dest\
    \ != source) {\n            active.push(edge.dest);\n          }\n          M_push(node,\
    \ edge);\n          if (node.excess == 0) {\n            break;\n          }\n\
    \        }\n        node.iter++;\n        if (node.iter == node.edges.size())\
    \ {\n          node.iter = 0;\n          M_relabel(node);\n        }\n      }\n\
    \    }\n    network_type graph;\n    graph.template add_vertices <false>(M_graph.size());\n\
    \    for (size_type index = 0; index < M_graph.size(); ++index) {\n      for (const\
    \ auto &edge: M_graph[index].edges) {\n        if (!edge.is_rev) {\n         \
    \ graph.add_edge(static_cast<edge_type>(edge));\n        }\n      }\n    }\n \
    \   return std::make_pair(flow, std::move(graph));\n  } \n};\n\n/**\n * @title\
    \ Push Relabel\n */\n"
  code: "#pragma once\n\n#include <queue>\n#include <algorithm>\n\nnamespace push_relabel_detail\
    \ {\n\nclass stack {\nprivate:\n  const size_t M_size;\n  std::vector<size_t>\
    \ M_stack;\n\npublic:\n  explicit stack(const size_t size):\n    M_size(size),\
    \ M_stack(size * 2)\n  { clear(); }\n\n  size_t top(const size_t height) const\
    \ {\n    return M_stack[M_size + height];\n  }\n  bool empty(const size_t height)\
    \ const { \n    return M_stack[M_size + height] == M_size + height; \n  }\n  void\
    \ pop(const size_t height) {\n    M_stack[M_size + height] = M_stack[M_stack[M_size\
    \ + height]];\n  }\n  void push(const size_t height, const size_t node) {\n  \
    \  M_stack[node] = M_stack[M_size + height];\n    M_stack[M_size + height] = node;\n\
    \  }\n  void clear() {\n    std::iota(M_stack.begin() + M_size, M_stack.end(),\
    \ M_size);\n  }\n};\n\nclass list {\nprivate:\n  const size_t M_size;\n  std::vector<std::pair<size_t,\
    \ size_t>> M_list;\n\npublic:\n  explicit list(const size_t size):\n    M_size(size),\
    \ M_list(size * 2)\n  { clear(); }\n\n  bool empty(const size_t height) {\n  \
    \  return M_list[M_size + height].second == M_size + height;\n  }\n  bool more_than_one(const\
    \ size_t height) {\n    return M_list[M_size + height].first != M_list[M_size\
    \ + height].second;\n  }\n\n  void insert(const size_t height, const size_t node)\
    \ {\n    M_list[node].first = M_list[M_size + height].first;\n    M_list[node].second\
    \ = M_size + height;\n    M_list[M_list[M_size + height].first].second = node;\n\
    \    M_list[M_size + height].first = node;\n  }\n  void erase(const size_t node)\
    \ {\n    M_list[M_list[node].first].second = M_list[node].second;\n    M_list[M_list[node].second].first\
    \ = M_list[node].first;\n  }\n  \n  void clear() {\n    for (size_t index = M_size;\
    \ index < M_size * 2; ++index) {\n      M_list[index].first = M_list[index].second\
    \ = index;\n    }\n  }\n  void clear(const size_t height) {\n    const size_t\
    \ index = M_size + height;\n    M_list[index].first = M_list[index].second = index;\n\
    \  }\n  template <class Func>\n  void apply_all(const size_t height, Func &&func)\
    \ {\n    size_t index = M_list[M_size + height].second;\n    while (index < M_size)\
    \ {\n      func(index);\n      index = M_list[index].second;\n    }\n  }\n};\n\
    \n}\n\ntemplate <class Network>\nclass push_relabel {\npublic:\n  using network_type\
    \ = Network;\n  using vertex_type  = typename Network::vertex_type;\n  using edge_type\
    \    = typename Network::edge_type;\n  using size_type    = typename Network::size_type;\n\
    \  using flow_type    = typename Network::edge_type::flow_type;\n  using height_type\
    \  = uint32_t;\n\n  static_assert(std::is_integral<flow_type>::value, \"invalid\
    \ flow type :: non-integral\");\n\nprivate:\n  class residual_edge: public edge_type\
    \ {\n  public:\n    const size_type rev;\n    const bool is_rev;\n    explicit\
    \ residual_edge(const edge_type &edge, const size_type rev, const bool is_rev):\n\
    \      edge_type(edge), rev(rev), is_rev(is_rev)\n    { }\n  };\n\n  class node_type\
    \ {\n  public:\n    std::vector<residual_edge> edges;\n    flow_type excess;\n\
    \    height_type height;\n    size_type iter;\n    node_type() = default;\n  };\n\
    \n  flow_type M_remain(const residual_edge &edge) {\n    return edge.capacity\
    \ - edge.flow;\n  }\n  residual_edge &M_cur_edge(node_type &node) {\n    return\
    \ node.edges[node.iter];\n  }\n  residual_edge &M_rev_edge(const residual_edge\
    \ &edge) {\n    return M_graph[edge.dest].edges[edge.rev];\n  }\n\n  void M_push(node_type\
    \ &node, residual_edge &edge) {\n    const auto flow = std::min(node.excess, M_remain(edge));\n\
    \    edge.flow += flow;\n    node.excess -= flow;\n    M_rev_edge(edge).flow -=\
    \ flow;\n    M_graph[edge.dest].excess += flow;\n  }\n  void M_relabel(node_type\
    \ &node) {\n    height_type min = M_graph.size() + 1;\n    for (const auto &edge:\
    \ node.edges) {\n      if (M_remain(edge) > 0 && min > M_graph[edge.dest].height\
    \ + 1) {\n        min = M_graph[edge.dest].height + 1;\n      }\n    }\n    node.height\
    \ = min;\n  }\n\n  void M_reverse_bfs(const vertex_type source) {\n    for (auto\
    \ &node: M_graph) {\n      node.height = M_graph.size() + 1;\n    }\n    M_graph[source].height\
    \ = 0;\n    std::queue<vertex_type> queue;\n    queue.push(source);\n    while\
    \ (!queue.empty()) {\n      const auto vert = queue.front();\n      queue.pop();\n\
    \      for (const auto &edge: M_graph[vert].edges) {\n        if (M_remain(M_rev_edge(edge))\
    \ > 0) {\n          if (M_graph[edge.dest].height == M_graph.size() + 1) {\n \
    \           M_graph[edge.dest].height = M_graph[vert].height + 1;\n          \
    \  queue.push(edge.dest);\n          }\n        }\n      }\n    }\n  }\n\n  std::vector<node_type>\
    \ M_graph;\n\npublic:\n  push_relabel() = default;\n  explicit push_relabel(const\
    \ network_type &net) {\n    M_graph.resize(net.size());\n    for (size_type src\
    \ = 0; src < net.size(); ++src) {\n      for (const auto &edge: net[src]) {\n\
    \        M_graph[src].edges.emplace_back(edge, M_graph[edge.dest].edges.size(),\
    \ false);\n        M_graph[edge.dest].edges.emplace_back(edge.reverse(), M_graph[src].edges.size()\
    \ - 1, true);\n      }\n    }\n  }\n\n  template <bool ValueOnly = true>\n  typename\
    \ std::enable_if<ValueOnly, flow_type>::type\n  max_flow(const vertex_type source,\
    \ const vertex_type sink, const bool initialize_edges = false) {\n    assert(source\
    \ < M_graph.size());\n    assert(sink < M_graph.size());\n    assert(source !=\
    \ sink);\n    push_relabel_detail::stack active(M_graph.size());\n    push_relabel_detail::list\
    \ level(M_graph.size());\n    height_type min_gap, max_active;\n    for (auto\
    \ &node: M_graph) {\n      node.excess = 0;\n      node.iter = 0;\n      for (auto\
    \ &edge: node.edges) {\n        if (initialize_edges) {\n          if (!edge.is_rev)\
    \ edge.flow = 0;\n          else edge.flow = edge.capacity;\n        }\n     \
    \ }\n    }\n    M_reverse_bfs(sink);\n    if (M_graph[source].height == M_graph.size()\
    \ + 1) {\n      return 0;\n    }\n    for (auto &edge: M_graph[source].edges)\
    \ {\n      M_graph[source].excess += M_remain(edge);\n      M_push(M_graph[source],\
    \ edge);\n    }\n    M_graph[source].height = M_graph.size();\n    min_gap = M_graph.size();\n\
    \    max_active = 0;\n    for (size_type index = 0; index < M_graph.size(); ++index)\
    \ {\n      const auto &node = M_graph[index];\n      if (node.height < M_graph.size())\
    \ {\n        if (node.excess > 0 && index != sink) {\n          active.push(node.height,\
    \ index);\n          max_active = std::max(max_active, node.height);\n       \
    \ }\n        level.insert(node.height, index);\n      }\n    }\n    for (size_type\
    \ index = 0; index < M_graph.size(); ++index) {\n      if (level.empty(index))\
    \ {\n        min_gap = index;\n        break;\n      }\n    }\n    while (max_active\
    \ > 0) {\n      if (active.empty(max_active)) {\n        --max_active;\n     \
    \   continue;\n      }\n      const auto vert = active.top(max_active);\n    \
    \  auto &node = M_graph[vert];\n      active.pop(max_active);\n      while (true)\
    \ {\n        auto &edge = M_cur_edge(node);\n        const auto &dest = M_graph[edge.dest];\n\
    \        if (M_remain(edge) > 0 && node.height == dest.height + 1) {\n       \
    \   if (dest.excess == 0 && edge.dest != sink) {\n            active.push(dest.height,\
    \ edge.dest);\n            max_active = std::max(max_active, dest.height);\n \
    \         }\n          M_push(node, edge);\n          if (node.excess == 0) {\n\
    \            break;\n          }\n        }\n        node.iter++;\n        if\
    \ (node.iter == node.edges.size()) {\n          node.iter = 0;\n          if (level.more_than_one(node.height))\
    \ {\n            level.erase(vert);\n            M_relabel(node);\n          \
    \  if (node.height > min_gap) {\n              node.height = M_graph.size() +\
    \ 1;\n              break;\n            }\n            if (node.height == min_gap)\
    \ {\n              min_gap++;\n            }\n            level.insert(node.height,\
    \ vert);\n          }\n          else {\n            const height_type old_gap\
    \ = min_gap;\n            min_gap = node.height;\n            for (height_type\
    \ index = node.height; index < old_gap; ++index) {\n              level.apply_all(index,\
    \ [&](const vertex_type vert) {\n                M_graph[vert].height = M_graph.size()\
    \ + 1;\n              });\n              level.clear(index);\n            }\n\
    \            break;\n          }\n        }\n      }\n      max_active = std::min(max_active,\
    \ min_gap - 1);\n    }\n    return M_graph[sink].excess;\n  }\n\n  template <bool\
    \ ValueOnly = true>\n  typename std::enable_if<!ValueOnly, std::pair<flow_type,\
    \ network_type>>::type\n  max_flow(const vertex_type source, const vertex_type\
    \ sink, const bool initialize_edges = false) {\n    const auto flow = max_flow<true>(source,\
    \ sink, initialize_edges);\n    std::queue<vertex_type> active;\n    M_reverse_bfs(source);\n\
    \    for (vertex_type index = 0; index < M_graph.size(); ++index) {\n      const\
    \ auto &node = M_graph[index];\n      if (node.excess > 0 && node.height < M_graph.size()\
    \ && index != sink) {\n        active.push(index);\n      }\n    }\n    while\
    \ (!active.empty()) {\n      auto &node = M_graph[active.front()];\n      active.pop();\n\
    \      while (node.excess > 0) {\n        auto &edge = M_cur_edge(node);\n   \
    \     const auto &dest = M_graph[edge.dest];\n        if (M_remain(edge) > 0 &&\
    \ node.height == dest.height + 1) {\n          if (dest.excess == 0 && edge.dest\
    \ != source) {\n            active.push(edge.dest);\n          }\n          M_push(node,\
    \ edge);\n          if (node.excess == 0) {\n            break;\n          }\n\
    \        }\n        node.iter++;\n        if (node.iter == node.edges.size())\
    \ {\n          node.iter = 0;\n          M_relabel(node);\n        }\n      }\n\
    \    }\n    network_type graph;\n    graph.template add_vertices <false>(M_graph.size());\n\
    \    for (size_type index = 0; index < M_graph.size(); ++index) {\n      for (const\
    \ auto &edge: M_graph[index].edges) {\n        if (!edge.is_rev) {\n         \
    \ graph.add_edge(static_cast<edge_type>(edge));\n        }\n      }\n    }\n \
    \   return std::make_pair(flow, std::move(graph));\n  } \n};\n\n/**\n * @title\
    \ Push Relabel\n */"
  dependsOn: []
  isVerificationFile: false
  path: graph/push_relabel.cpp
  requiredBy: []
  timestamp: '2020-09-13 16:51:07+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/push_relabel.test.cpp
documentation_of: graph/push_relabel.cpp
layout: document
redirect_from:
- /library/graph/push_relabel.cpp
- /library/graph/push_relabel.cpp.html
title: Push Relabel
---
