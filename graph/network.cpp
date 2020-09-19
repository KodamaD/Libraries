#pragma once

#include "../other/adjust_index.cpp"

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
  typename std::enable_if<ReturnsIndices, adjust_index>::type 
  add_vertices(const size_type size) {
    size_type cur = M_graph.size();
    M_graph.resize(cur + size);
    return adjust_index(cur, size);
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

/**
 * @title Network
 */