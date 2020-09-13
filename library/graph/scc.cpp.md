---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: Strongly Connected Components

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/scc.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-13 16:51:07+09:00




## Depends on

* :heavy_check_mark: <a href="../other/fix_point.cpp.html">Lambda Recursion</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/scc.test.cpp.html">test/scc.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "../other/fix_point.cpp"

#include <vector>
#include <stack>

template <class Network>
class strongly_connected_components {
public:
  using network_type = Network;
  using vertex_type  = typename Network::vertex_type;
  using edge_type    = typename Network::edge_type;
  using size_type    = typename Network::size_type;

private:
  std::vector<std::vector<vertex_type>> graph;
  std::vector<std::vector<vertex_type>> revgraph;

public:
  explicit strongly_connected_components(const network_type &net) {
    graph.resize(net.size());
    revgraph.resize(net.size());
    for (size_type src = 0; src < net.size(); ++src) {
      for (const auto &edge: net[src]) {
        graph[src].push_back(edge.dest);
        revgraph[edge.dest].push_back(src);
      }
    }
  }

  std::vector<std::vector<vertex_type>> decompose() const {
    std::vector<bool> visited(graph.size());
    std::stack<vertex_type> topological;
    const auto sort = fix_point([&](auto dfs, const vertex_type u) -> void {
      if (visited[u]) return;
      visited[u] = true;
      for (const auto v: graph[u]) {
        dfs(v);
      }
      topological.push(u);
    });
    for (vertex_type src = 0; src < graph.size(); ++src) {
      sort(src);
    }
    std::vector<std::vector<vertex_type>> group;
    const auto decompose = fix_point([&](const auto dfs, const vertex_type u) -> void {
      if (visited[u]) return;
      visited[u] = true;
      group.back().push_back(u);
      for (const auto v: revgraph[u]) {
        dfs(v);
      }
    });
    std::fill(visited.begin(), visited.end(), false);
    while (!topological.empty()) {
      const auto u = topological.top();
      topological.pop();
      if (!visited[u]) {
        group.push_back({ });
        decompose(u);
      }
    }
    return group;
  }
};

/**
 * @title Strongly Connected Components
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "graph/scc.cpp"

#line 2 "other/fix_point.cpp"

#include <utility>

template <class Func>
struct fix_point_impl: private Func {
  explicit constexpr fix_point_impl(Func &&func): Func(std::forward<Func>(func)) { }
  template <class... Args>
  constexpr decltype(auto) operator () (Args &&... args) const {
    return Func::operator()(*this, std::forward<Args>(args)...);
  }
};

template <class Func>
constexpr decltype(auto) fix_point(Func &&func) {
  return fix_point_impl<Func>(std::forward<Func>(func));
}

/**
 * @title Lambda Recursion
 */
#line 4 "graph/scc.cpp"

#include <vector>
#include <stack>

template <class Network>
class strongly_connected_components {
public:
  using network_type = Network;
  using vertex_type  = typename Network::vertex_type;
  using edge_type    = typename Network::edge_type;
  using size_type    = typename Network::size_type;

private:
  std::vector<std::vector<vertex_type>> graph;
  std::vector<std::vector<vertex_type>> revgraph;

public:
  explicit strongly_connected_components(const network_type &net) {
    graph.resize(net.size());
    revgraph.resize(net.size());
    for (size_type src = 0; src < net.size(); ++src) {
      for (const auto &edge: net[src]) {
        graph[src].push_back(edge.dest);
        revgraph[edge.dest].push_back(src);
      }
    }
  }

  std::vector<std::vector<vertex_type>> decompose() const {
    std::vector<bool> visited(graph.size());
    std::stack<vertex_type> topological;
    const auto sort = fix_point([&](auto dfs, const vertex_type u) -> void {
      if (visited[u]) return;
      visited[u] = true;
      for (const auto v: graph[u]) {
        dfs(v);
      }
      topological.push(u);
    });
    for (vertex_type src = 0; src < graph.size(); ++src) {
      sort(src);
    }
    std::vector<std::vector<vertex_type>> group;
    const auto decompose = fix_point([&](const auto dfs, const vertex_type u) -> void {
      if (visited[u]) return;
      visited[u] = true;
      group.back().push_back(u);
      for (const auto v: revgraph[u]) {
        dfs(v);
      }
    });
    std::fill(visited.begin(), visited.end(), false);
    while (!topological.empty()) {
      const auto u = topological.top();
      topological.pop();
      if (!visited[u]) {
        group.push_back({ });
        decompose(u);
      }
    }
    return group;
  }
};

/**
 * @title Strongly Connected Components
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

