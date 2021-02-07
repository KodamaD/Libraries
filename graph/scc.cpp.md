---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/fix_point.cpp
    title: Lambda Recursion
  _extendedRequiredBy:
  - icon: ':warning:'
    path: graph/two_sat.cpp
    title: Two Sat
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/scc.test.cpp
    title: test/scc.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Strongly Connected Components
    links: []
  bundledCode: "#line 2 \"graph/scc.cpp\"\n\n#line 2 \"other/fix_point.cpp\"\n\n#include\
    \ <utility>\n\ntemplate <class Func>\nstruct fix_point_impl: private Func {\n\
    \  explicit constexpr fix_point_impl(Func &&func): Func(std::forward<Func>(func))\
    \ { }\n  template <class... Args>\n  constexpr decltype(auto) operator () (Args\
    \ &&... args) const {\n    return Func::operator()(*this, std::forward<Args>(args)...);\n\
    \  }\n};\n\ntemplate <class Func>\nconstexpr decltype(auto) fix_point(Func &&func)\
    \ {\n  return fix_point_impl<Func>(std::forward<Func>(func));\n}\n\n/**\n * @title\
    \ Lambda Recursion\n */\n#line 4 \"graph/scc.cpp\"\n\n#include <vector>\n#include\
    \ <stack>\n\ntemplate <class Network>\nclass strongly_connected_components {\n\
    public:\n  using network_type = Network;\n  using vertex_type  = typename Network::vertex_type;\n\
    \  using edge_type    = typename Network::edge_type;\n  using size_type    = typename\
    \ Network::size_type;\n\nprivate:\n  std::vector<std::vector<vertex_type>> graph;\n\
    \  std::vector<std::vector<vertex_type>> revgraph;\n\npublic:\n  explicit strongly_connected_components(const\
    \ network_type &net) {\n    graph.resize(net.size());\n    revgraph.resize(net.size());\n\
    \    for (size_type src = 0; src < net.size(); ++src) {\n      for (const auto\
    \ &edge: net[src]) {\n        graph[src].push_back(edge.dest);\n        revgraph[edge.dest].push_back(src);\n\
    \      }\n    }\n  }\n\n  std::vector<std::vector<vertex_type>> decompose() const\
    \ {\n    std::vector<bool> visited(graph.size());\n    std::stack<vertex_type>\
    \ topological;\n    const auto sort = fix_point([&](auto dfs, const vertex_type\
    \ u) -> void {\n      if (visited[u]) return;\n      visited[u] = true;\n    \
    \  for (const auto v: graph[u]) {\n        dfs(v);\n      }\n      topological.push(u);\n\
    \    });\n    for (vertex_type src = 0; src < graph.size(); ++src) {\n      sort(src);\n\
    \    }\n    std::vector<std::vector<vertex_type>> group;\n    const auto decompose\
    \ = fix_point([&](const auto dfs, const vertex_type u) -> void {\n      if (visited[u])\
    \ return;\n      visited[u] = true;\n      group.back().push_back(u);\n      for\
    \ (const auto v: revgraph[u]) {\n        dfs(v);\n      }\n    });\n    std::fill(visited.begin(),\
    \ visited.end(), false);\n    while (!topological.empty()) {\n      const auto\
    \ u = topological.top();\n      topological.pop();\n      if (!visited[u]) {\n\
    \        group.push_back({ });\n        decompose(u);\n      }\n    }\n    return\
    \ group;\n  }\n};\n\n/**\n * @title Strongly Connected Components\n */\n"
  code: "#pragma once\n\n#include \"../other/fix_point.cpp\"\n\n#include <vector>\n\
    #include <stack>\n\ntemplate <class Network>\nclass strongly_connected_components\
    \ {\npublic:\n  using network_type = Network;\n  using vertex_type  = typename\
    \ Network::vertex_type;\n  using edge_type    = typename Network::edge_type;\n\
    \  using size_type    = typename Network::size_type;\n\nprivate:\n  std::vector<std::vector<vertex_type>>\
    \ graph;\n  std::vector<std::vector<vertex_type>> revgraph;\n\npublic:\n  explicit\
    \ strongly_connected_components(const network_type &net) {\n    graph.resize(net.size());\n\
    \    revgraph.resize(net.size());\n    for (size_type src = 0; src < net.size();\
    \ ++src) {\n      for (const auto &edge: net[src]) {\n        graph[src].push_back(edge.dest);\n\
    \        revgraph[edge.dest].push_back(src);\n      }\n    }\n  }\n\n  std::vector<std::vector<vertex_type>>\
    \ decompose() const {\n    std::vector<bool> visited(graph.size());\n    std::stack<vertex_type>\
    \ topological;\n    const auto sort = fix_point([&](auto dfs, const vertex_type\
    \ u) -> void {\n      if (visited[u]) return;\n      visited[u] = true;\n    \
    \  for (const auto v: graph[u]) {\n        dfs(v);\n      }\n      topological.push(u);\n\
    \    });\n    for (vertex_type src = 0; src < graph.size(); ++src) {\n      sort(src);\n\
    \    }\n    std::vector<std::vector<vertex_type>> group;\n    const auto decompose\
    \ = fix_point([&](const auto dfs, const vertex_type u) -> void {\n      if (visited[u])\
    \ return;\n      visited[u] = true;\n      group.back().push_back(u);\n      for\
    \ (const auto v: revgraph[u]) {\n        dfs(v);\n      }\n    });\n    std::fill(visited.begin(),\
    \ visited.end(), false);\n    while (!topological.empty()) {\n      const auto\
    \ u = topological.top();\n      topological.pop();\n      if (!visited[u]) {\n\
    \        group.push_back({ });\n        decompose(u);\n      }\n    }\n    return\
    \ group;\n  }\n};\n\n/**\n * @title Strongly Connected Components\n */"
  dependsOn:
  - other/fix_point.cpp
  isVerificationFile: false
  path: graph/scc.cpp
  requiredBy:
  - graph/two_sat.cpp
  timestamp: '2020-09-13 16:51:07+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/scc.test.cpp
documentation_of: graph/scc.cpp
layout: document
redirect_from:
- /library/graph/scc.cpp
- /library/graph/scc.cpp.html
title: Strongly Connected Components
---
