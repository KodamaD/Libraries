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


# :heavy_check_mark: test/scc.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/scc.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-13 16:51:07+09:00


* see: <a href="https://judge.yosupo.jp/problem/scc">https://judge.yosupo.jp/problem/scc</a>


## Depends on

* :heavy_check_mark: <a href="../../library/graph/network.cpp.html">Network</a>
* :heavy_check_mark: <a href="../../library/graph/scc.cpp.html">Strongly Connected Components</a>
* :heavy_check_mark: <a href="../../library/other/fix_point.cpp.html">Lambda Recursion</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include "../graph/network.cpp"
#include "../graph/scc.cpp"

#include <cstddef>
#include <iostream>

int main() {
  size_t N, M;
  std::cin >> N >> M;
  network<base_edge> net;
  net.add_vertices<false>(N);
  for (size_t i = 0; i < M; ++i) {
    size_t a, b;
    std::cin >> a >> b;
    net.emplace_edge(a, b);
  }
  const auto group = strongly_connected_components(net).decompose();
  std::cout << group.size() << '\n';
  for (const auto &vec: group) {
    std::cout << vec.size();
    for (const auto u: vec) {
      std::cout << ' ' << u;
    }
    std::cout << '\n';
  }
  return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/scc.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/scc"

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

  base_edge reverse() const {
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
#line 2 "graph/scc.cpp"

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
#line 4 "graph/scc.cpp"

#line 6 "graph/scc.cpp"
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
#line 5 "test/scc.test.cpp"

#line 7 "test/scc.test.cpp"
#include <iostream>

int main() {
  size_t N, M;
  std::cin >> N >> M;
  network<base_edge> net;
  net.add_vertices<false>(N);
  for (size_t i = 0; i < M; ++i) {
    size_t a, b;
    std::cin >> a >> b;
    net.emplace_edge(a, b);
  }
  const auto group = strongly_connected_components(net).decompose();
  std::cout << group.size() << '\n';
  for (const auto &vec: group) {
    std::cout << vec.size();
    for (const auto u: vec) {
      std::cout << ' ' << u;
    }
    std::cout << '\n';
  }
  return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

