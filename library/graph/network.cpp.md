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


# :heavy_check_mark: Network

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/network.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-20 22:07:26+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/push_relabel.test.cpp.html">test/push_relabel.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cstddef>
#include <vector>
#include <numeric>
#include <utility>
#include <type_traits>

template <class Edge>
class network {
public:
  using vertex_type = typename Edge::vertex_type;
  using edge_type   = Edge;
  using size_type   = size_t;

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
  typename std::enable_if<ReturnsIndices, std::vector<vertex_type>>::type 
  add_vertices(const size_type size) {
    size_type cur = M_graph.size();
    std::vector<vertex_type> res(size);
    std::iota(res.begin(), res.end(), cur);
    M_graph.resize(cur + size);
    return res;
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
    return M_graph[vert];
  }
  std::vector<edge_type> &at(const vertex_type vert) {
    return M_graph.at(vert);
  }
  const std::vector<edge_type> &operator [] (const vertex_type vert) const {
    return M_graph[vert];
  }
  const std::vector<edge_type> &at(const vertex_type vert) const {
    return M_graph.at(vert);
  }
  const std::vector<std::vector<edge_type>> &get() const {
    return M_graph;
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
  using vertex_type = size_t;
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
    return flow_edge(static_cast<base_edge>(*this).reverse(), capacity);
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
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "graph/network.cpp"

#include <cstddef>
#include <vector>
#include <numeric>
#include <utility>
#include <type_traits>

template <class Edge>
class network {
public:
  using vertex_type = typename Edge::vertex_type;
  using edge_type   = Edge;
  using size_type   = size_t;

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
  typename std::enable_if<ReturnsIndices, std::vector<vertex_type>>::type 
  add_vertices(const size_type size) {
    size_type cur = M_graph.size();
    std::vector<vertex_type> res(size);
    std::iota(res.begin(), res.end(), cur);
    M_graph.resize(cur + size);
    return res;
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
    return M_graph[vert];
  }
  std::vector<edge_type> &at(const vertex_type vert) {
    return M_graph.at(vert);
  }
  const std::vector<edge_type> &operator [] (const vertex_type vert) const {
    return M_graph[vert];
  }
  const std::vector<edge_type> &at(const vertex_type vert) const {
    return M_graph.at(vert);
  }
  const std::vector<std::vector<edge_type>> &get() const {
    return M_graph;
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
  using vertex_type = size_t;
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
    return flow_edge(static_cast<base_edge>(*this).reverse(), capacity);
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

