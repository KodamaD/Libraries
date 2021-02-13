#pragma once

#include <cstddef>
#include <vector>
#include <utility>
#include <cassert>

class heavy_light_decomposition {
public:
  using size_type = size_t;

private:
  std::vector<std::vector<size_type>> M_graph;
  std::vector<size_type> M_size, M_parent, M_head;
  size_type M_index;

  void M_calc_subtree(size_type u, size_type p) {
    M_size[u] = 1;
    for (auto v: M_graph[u]) {
      if (v != p) {
        M_calc_subtree(v, u);
        M_size[u] += M_size[v];
      }
    }
  }

  void M_decompose(size_type u, size_type p, size_type h) {
    label[u] = M_index;
    M_head[u] = h;
    M_parent[u] = p;
    ++M_index;
    size_type max = 0, heavy = -1;
    for (auto v: M_graph[u]) {
      if (v != p) {
        if (max < M_size[v]) {
          max = M_size[v];
          heavy = v;
        }
      }
    }
    if (heavy == size_type(-1)) return;
    M_decompose(heavy, u, h);
    for (auto v: M_graph[u]) {
      if (v != p && v != heavy) {
        M_decompose(v, u, v);
      }
    }
  }

public:
  std::vector<size_type> label;

  heavy_light_decomposition() { }
  explicit heavy_light_decomposition(size_type size) { initialize(size); }

  void initialize(size_type size) {
    clear();
    M_index = 0;
    M_graph.assign(size, { });
    M_size.assign(size, 0);
    M_parent.assign(size, 0);
    M_head.assign(size, 0);
    label.assign(size, 0);
  }
  void construct(size_type root = 0) {
    assert(root < M_graph.size());
    M_calc_subtree(root, -1);
    M_decompose(root, -1, root);
  }
  void construct(const std::vector<size_type> &roots) {
    for (const auto x: roots) {
      construct(x);
    }
  }
  void add_edge(size_type u, size_type v) {
    assert(u < M_graph.size());
    assert(v < M_graph.size());
    assert(u != v);
    M_graph[u].push_back(v);
    M_graph[v].push_back(u);
  }

  template <class Func> 
  void each_edge(size_type u, size_type v, const Func &func) const {
    assert(u < M_graph.size());
    assert(v < M_graph.size());
    while (true) {
      if (label[u] > label[v]) {
        std::swap(u, v);
      }
      if (M_head[u] == M_head[v]) {
        if (label[u] + 1 <= label[v]) {
          func(label[u] + 1, label[v]);
        }
        return;
      }
      func(label[M_head[v]], label[v]);
      v = M_parent[M_head[v]];
    }
  }

  template <class Func> 
  void each_vertex(size_type u, size_type v, const Func &func) const {
    assert(u < M_graph.size());
    assert(v < M_graph.size());
    while (true) {
      if (label[u] > label[v]) {
        std::swap(u, v);
      }
      if (M_head[u] == M_head[v]) {
        func(label[u], label[v]);
        return;
      }
      func(label[M_head[v]], label[v]);
      v = M_parent[M_head[v]];
    }
  }

  size_type lca(size_type u, size_type v) const {
    assert(u < M_graph.size());
    assert(v < M_graph.size());
    if (label[u] > label[v]) {
      std::swap(u, v);
    }
    while (label[u] <= label[v]) {
      if (M_head[u] == M_head[v]) {
        return u;
      }
      v = M_parent[M_head[v]];
    }
    return v;
  }

  size_type size() const {
    return M_graph.size();
  }
  bool empty() const {
    return M_graph.empty();
  }
  void clear() {
    M_index = 0;
    M_graph.clear();
    M_graph.shrink_to_fit();
    M_size.clear();
    M_size.shrink_to_fit();
    M_parent.clear();
    M_parent.shrink_to_fit();
    M_head.clear();
    M_head.shrink_to_fit();
    label.clear();
    label.shrink_to_fit();
  }
};

/**
 * @title Heavy-Light Decomposition
 */