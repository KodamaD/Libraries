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


# :heavy_check_mark: test/dinic.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/dinic.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-09 18:08:09+09:00


* see: <a href="https://judge.yosupo.jp/problem/bipartitematching">https://judge.yosupo.jp/problem/bipartitematching</a>


## Depends on

* :heavy_check_mark: <a href="../../library/graph/dinic.cpp.html">Dinic</a>
* :heavy_check_mark: <a href="../../library/graph/network.cpp.html">Network</a>
* :heavy_check_mark: <a href="../../library/other/fix_point.cpp.html">Lambda Recursion</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp

#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include "../graph/network.cpp"
#include "../graph/dinic.cpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

int main() {
  size_t L, R, M;
  std::cin >> L >> R >> M;
  network<flow_edge<int32_t>> graph;
  const auto S = graph.add_vertex();
  const auto T = graph.add_vertex();
  const auto left = graph.add_vertices(L);
  const auto right = graph.add_vertices(R);
  while (M--) {
    size_t u, v;
    std::cin >> u >> v;
    graph.emplace_edge(left[u], right[v], 1);
  }
  for (size_t i = 0; i < L; ++i) {
    graph.emplace_edge(S, left[i], 1);
  }
  for (size_t i = 0; i < R; ++i) {
    graph.emplace_edge(right[i], T, 1);
  }
  const auto [flow, built] = dinic(graph).max_flow<false>(S, T);
  std::cout << flow << '\n';
  for (size_t i = 0; i < L; ++i) {
    for (const auto &edge: built[left[i]]) {
      if (edge.flow > 0) {
        std::cout << i << ' ' << right.to_index(edge.dest) << '\n';
        break;
      }
    }
  }
  return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/dinic.test.cpp"

#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#line 2 "graph/network.cpp"

#include <cstddef>
#include <cstdint>
#include <vector>
#include <numeric>
#include <utility>
#include <type_traits>
#include <cassert>

template <class Edge>
class network {
public:
  using vertex_type = typename Edge::vertex_type;
  using edge_type   = Edge;
  using size_type   = size_t;

  class index_helper {
  private:
    const size_type M_stuff, M_size;
  public:
    explicit index_helper(const size_type stuff, const size_type size): 
      M_stuff(stuff), M_size(size) 
    { }
    vertex_type operator [] (const size_type index) const {
      return to_vertex(index);
    }
    vertex_type to_vertex(const size_type index) const {
      assert(index < M_size);
      return index + M_stuff;
    }
    size_type to_index(const vertex_type vert) const {
      assert(vert >= M_stuff);
      assert(vert < M_size + M_stuff);
      return vert - M_stuff;
    }
    size_type size() const {
      return M_size;
    }
  };

protected:
  std::vector<std::vector<edge_type>> M_graph;

public:
  network() = default;

  template <bool ReturnsIndex = true>
  typename std::enable_if<ReturnsIndex, vertex_type>::type add_vertex() {
    vertex_type res = M_graph.size();
    M_graph.push_back({ });
    return res;
  }
  template <bool ReturnsIndex = true>
  typename std::enable_if<!ReturnsIndex, void>::type add_vertex() {
    M_graph.push_back({ });
  }

  template <bool ReturnsIndices = true>
  typename std::enable_if<ReturnsIndices, index_helper>::type 
  add_vertices(const size_type size) {
    size_type cur = M_graph.size();
    M_graph.resize(cur + size);
    return index_helper(cur, size);
  }
  template <bool ReturnsIndices = true>
  typename std::enable_if<!ReturnsIndices, void>::type 
  add_vertices(const size_type size) {
    size_type cur = M_graph.size();
    M_graph.resize(cur + size);
  }
  
  void add_edge(const edge_type &edge) {
    M_graph[edge.source].push_back(edge);
  }
  template <class... Args>
  void emplace_edge(const vertex_type src, Args&&... args) {
    M_graph[src].emplace_back(src, std::forward<Args>(args)...);
  }

  std::vector<edge_type> &operator [] (const vertex_type vert) {
    assert(vert < size());
    return M_graph[vert];
  }
  const std::vector<edge_type> &operator [] (const vertex_type vert) const {
    assert(vert < size());
    return M_graph[vert];
  }

  size_type size() const {
    return M_graph.size();
  }
  bool empty() const {
    return M_graph.empty();
  }
  void clear() {
    M_graph.clear();
    M_graph.shrink_to_fit();
  }
};

class base_edge {
public:
  using vertex_type = uint32_t;
  const vertex_type source, dest;
  explicit base_edge(const vertex_type source, const vertex_type dest): 
    source(source), dest(dest) 
  { }
  base_edge reverse() {
    return base_edge(dest, source);
  }
};

template <class Flow>
class flow_edge: public base_edge {
public:
  using vertex_type = typename base_edge::vertex_type;
  using flow_type   = Flow;
  flow_type flow;
  const flow_type capacity;
  explicit flow_edge(const base_edge &edge, const flow_type capacity):
    base_edge(edge), flow(0), capacity(capacity)
  { }
  explicit flow_edge(const base_edge &edge, const flow_type flow, const flow_type capacity):
    base_edge(edge), flow(flow), capacity(capacity)
  { }
  explicit flow_edge(const vertex_type source, const vertex_type dest, const flow_type capacity):
    base_edge(source, dest), flow(0), capacity(capacity)
  { }
  explicit flow_edge(const vertex_type source, const vertex_type dest, const flow_type flow, const flow_type capacity):
    base_edge(source, dest), flow(flow), capacity(capacity)
  { }
  flow_edge reverse() const {
    return flow_edge(static_cast<base_edge>(*this).reverse(), capacity - flow, capacity);
  }
};

template <class Flow, class Cost>
class flow_cost_edge: public flow_edge<Flow> {
public:
  using vertex_type = typename flow_edge<Flow>::vertex_type;
  using flow_type   = typename flow_edge<Flow>::flow_type;
  using cost_type   = Cost;
  const cost_type cost;
  explicit flow_cost_edge(const flow_edge<Flow> &edge, const cost_type cost):
    flow_edge<Flow>(edge), cost(cost)
  { }
  explicit flow_cost_edge(const vertex_type source, const vertex_type dest, const flow_type capacity, const cost_type cost):
    flow_edge<Flow>(source, dest, capacity), cost(cost)
  { }
  explicit flow_cost_edge(const vertex_type source, const vertex_type dest, const flow_type flow, const flow_type capacity, const cost_type cost):
    flow_edge<Flow>(source, dest, flow, capacity), cost(cost)
  { }
  flow_cost_edge reverse() const {
    return flow_cost_edge(static_cast<flow_edge<Flow>>(*this).reverse(), -cost);
  }
};

/**
 * @title Network
 */
#line 2 "graph/dinic.cpp"

#line 2 "other/fix_point.cpp"

#line 4 "other/fix_point.cpp"

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
#line 5 "graph/dinic.cpp"

#include <queue>
#include <algorithm>
#line 9 "graph/dinic.cpp"

template <class Network>
class dinic {
public:
  using network_type = Network;
  using vertex_type  = typename Network::vertex_type;
  using edge_type    = typename Network::edge_type;
  using size_type    = typename Network::size_type;
  using flow_type    = typename Network::edge_type::flow_type;
  using height_type  = uint32_t;

  static_assert(std::is_integral<flow_type>::value, "invalid flow type :: non-integral");

private:
  class residual_edge: public edge_type {
  public:
    const size_type rev;
    const bool is_rev;
    explicit residual_edge(const edge_type &edge, const size_type rev, const bool is_rev):
      edge_type(edge), rev(rev), is_rev(is_rev)
    { }
  };

  class node_type {
  public:
    std::vector<residual_edge> edges;
    height_type level;
    size_type iter;
    node_type() = default;
  };

  flow_type M_remain(const residual_edge &edge) {
    return edge.capacity - edge.flow;
  }
  residual_edge &M_cur_edge(node_type &node) {
    return node.edges[node.iter];
  }
  residual_edge &M_rev_edge(const residual_edge &edge) {
    return M_graph[edge.dest].edges[edge.rev];
  }

  void M_bfs(const vertex_type source) {
    for (auto &node: M_graph) {
      node.level = M_graph.size() + 1;
    }
    M_graph[source].level = 0;
    std::queue<vertex_type> queue;
    queue.push(source);
    while (!queue.empty()) {
      const auto vert = queue.front();
      queue.pop();
      for (const auto &edge: M_graph[vert].edges) {
        if (M_remain(edge) > 0) {
          if (M_graph[edge.dest].level == M_graph.size() + 1) {
            M_graph[edge.dest].level = M_graph[vert].level + 1;
            queue.push(edge.dest);
          }
        }
      }
    }
  }

  std::vector<node_type> M_graph;

public:
  dinic() = default;
  explicit dinic(const network_type &net) {
    M_graph.resize(net.size());
    for (size_type src = 0; src < net.size(); ++src) {
      for (const auto &edge: net[src]) {
        M_graph[src].edges.emplace_back(edge, M_graph[edge.dest].edges.size(), false);
        M_graph[edge.dest].edges.emplace_back(edge.reverse(), M_graph[src].edges.size() - 1, true);
      }
    }
  }

  template <bool ValueOnly = true>
  typename std::enable_if<ValueOnly, flow_type>::type
  max_flow(const vertex_type source, const vertex_type sink, const bool initialize_edges = false) {
    assert(source < M_graph.size());
    assert(sink < M_graph.size());
    assert(source != sink);
    const auto dfs = fix_point([&](const auto dfs, 
      const vertex_type vert, const flow_type flow) -> flow_type {
      if (vert == sink) return flow;
      auto &node = M_graph[vert];
      for (; node.iter < node.edges.size(); ++node.iter) {
        auto &edge = M_cur_edge(node);
        if (M_remain(edge) > 0 && node.level < M_graph[edge.dest].level) {
          const auto push = dfs(edge.dest, std::min(flow, M_remain(edge)));
          if (push > 0) {
            edge.flow += push;
            M_rev_edge(edge).flow -= push;
            return push;
          }
        }
      }
      return 0;
    });
    flow_type max_capacity = 0;
    for (auto &node: M_graph) {
      for (auto &edge: node.edges) {
        if (initialize_edges) {
          if (!edge.is_rev) edge.flow = 0;
          else edge.flow = edge.capacity;
        }
        max_capacity = std::max(max_capacity, edge.capacity);
      }
    }
    flow_type flow = 0;
    while (true) {
      M_bfs(source);
      if (M_graph[sink].level == M_graph.size() + 1) {
        return flow;
      }
      for (auto &node: M_graph) {
        node.iter = 0;
      }
      flow_type push;
      while ((push = dfs(source, max_capacity)) > 0) {
        flow += push;
      }
    }
    return flow;
  }

  template <bool ValueOnly = true>
  typename std::enable_if<!ValueOnly, std::pair<flow_type, network_type>>::type
  max_flow(const vertex_type source, const vertex_type sink, const bool initialize_edges = false) {
    const auto flow = max_flow<true>(source, sink, initialize_edges);
    network_type graph;
    graph.template add_vertices <false>(M_graph.size());
    for (size_type index = 0; index < M_graph.size(); ++index) {
      for (const auto &edge: M_graph[index].edges) {
        if (!edge.is_rev) {
          graph.add_edge(static_cast<edge_type>(edge));
        }
      }
    }
    return std::make_pair(flow, std::move(graph));
  }
};

/**
 * @title Dinic
 */
#line 6 "test/dinic.test.cpp"

#line 9 "test/dinic.test.cpp"
#include <iostream>

int main() {
  size_t L, R, M;
  std::cin >> L >> R >> M;
  network<flow_edge<int32_t>> graph;
  const auto S = graph.add_vertex();
  const auto T = graph.add_vertex();
  const auto left = graph.add_vertices(L);
  const auto right = graph.add_vertices(R);
  while (M--) {
    size_t u, v;
    std::cin >> u >> v;
    graph.emplace_edge(left[u], right[v], 1);
  }
  for (size_t i = 0; i < L; ++i) {
    graph.emplace_edge(S, left[i], 1);
  }
  for (size_t i = 0; i < R; ++i) {
    graph.emplace_edge(right[i], T, 1);
  }
  const auto [flow, built] = dinic(graph).max_flow<false>(S, T);
  std::cout << flow << '\n';
  for (size_t i = 0; i < L; ++i) {
    for (const auto &edge: built[left[i]]) {
      if (edge.flow > 0) {
        std::cout << i << ' ' << right.to_index(edge.dest) << '\n';
        break;
      }
    }
  }
  return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

