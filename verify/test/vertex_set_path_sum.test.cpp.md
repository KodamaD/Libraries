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


# :x: test/vertex_set_path_sum.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/vertex_set_path_sum.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-09 18:08:09+09:00


* see: <a href="https://judge.yosupo.jp/problem/vertex_add_path_sum">https://judge.yosupo.jp/problem/vertex_add_path_sum</a>


## Depends on

* :x: <a href="../../library/container/fenwick_tree.cpp.html">Fenwick Tree</a>
* :question: <a href="../../library/graph/heavy_light_decomposition.cpp.html">Heavy-Light Decomposition</a>
* :x: <a href="../../library/other/bit_operation.cpp.html">Bit Operations</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp

#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"

#include "../graph/heavy_light_decomposition.cpp"
#include "../container/fenwick_tree.cpp"

#include <cstddef>
#include <cstdint>
#include <vector>
#include <iostream>

int main() {
  size_t N, Q;
  std::cin >> N >> Q;
  std::vector<uint64_t> A(N);
  for (auto &x: A) {
    std::cin >> x;
  }
  heavy_light_decomposition hld(N);
  for (size_t i = 1; i < N; ++i) {
    size_t x, y;
    std::cin >> x >> y;
    hld.add_edge(x, y);
  }
  hld.construct();
  fenwick_tree<uint64_t> fen(N);
  for (size_t i = 0; i < N; ++i) {
    fen.add(hld.label[i], A[i]);
  }
  uint64_t answer;
  const auto query = [&](const size_t x, const size_t y) {
    answer += fen.fold(x, y + 1);
  };
  while (Q--) {
    size_t t;
    std::cin >> t;
    if (t == 0) {
      size_t p;
      uint64_t x;
      std::cin >> p >> x;
      fen.add(hld.label[p], x);
    }
    else {
      size_t x, y;
      std::cin >> x >> y;
      answer = 0;
      hld.each_vertex(x, y, query);
      std::cout << answer << '\n';
    }
  }
  return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/vertex_set_path_sum.test.cpp"

#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"

#line 2 "graph/heavy_light_decomposition.cpp"

#include <cstddef>
#include <vector>
#include <utility>

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
    M_calc_subtree(root, -1);
    M_decompose(root, -1, root);
  }
  void add_edge(size_type u, size_type v) {
    M_graph[u].push_back(v);
    M_graph[v].push_back(u);
  }

  template <class Func> 
  void each_edge(size_type u, size_type v, const Func &func) const {
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
#line 2 "container/fenwick_tree.cpp"

#line 2 "other/bit_operation.cpp"

#line 4 "other/bit_operation.cpp"
#include <cstdint>

constexpr size_t bit_ppc(const uint64_t x) { return __builtin_popcountll(x); }
constexpr size_t bit_ctzr(const uint64_t x) { return x == 0 ? 64 : __builtin_ctzll(x); }
constexpr size_t bit_ctzl(const uint64_t x) { return x == 0 ? 64 : __builtin_clzll(x); }
constexpr size_t bit_width(const uint64_t x) { return 64 - bit_ctzl(x); }
constexpr uint64_t bit_msb(const uint64_t x) { return x == 0 ? 0 : uint64_t(1) << (bit_width(x) - 1); }
constexpr uint64_t bit_lsb(const uint64_t x) { return x & (-x); }
constexpr uint64_t bit_cover(const uint64_t x) { return x == 0 ? 0 : bit_msb(2 * x - 1); }

constexpr uint64_t bit_rev(uint64_t x) {
  x = ((x >> 1) & 0x5555555555555555) | ((x & 0x5555555555555555) << 1);
  x = ((x >> 2) & 0x3333333333333333) | ((x & 0x3333333333333333) << 2);
  x = ((x >> 4) & 0x0F0F0F0F0F0F0F0F) | ((x & 0x0F0F0F0F0F0F0F0F) << 4);
  x = ((x >> 8) & 0x00FF00FF00FF00FF) | ((x & 0x00FF00FF00FF00FF) << 8);
  x = ((x >> 16) & 0x0000FFFF0000FFFF) | ((x & 0x0000FFFF0000FFFF) << 16);
  x = (x >> 32) | (x << 32);
  return x;
}

/**
 * @title Bit Operations
 */
#line 4 "container/fenwick_tree.cpp"

#line 7 "container/fenwick_tree.cpp"
#include <cassert>

template <class T>
class fenwick_tree {
public:
  using value_type = T;
  using size_type = size_t;

private:
  std::vector<value_type> M_tree;

public:
  fenwick_tree() = default;
  explicit fenwick_tree(size_type size) { initialize(size); }

  void initialize(size_type size) {
    M_tree.assign(size + 1, value_type{});
  }

  void add(size_type index, const value_type& x) {
    assert(index < size());
    ++index;
    while (index <= size()) {
      M_tree[index] += x;
      index += bit_lsb(index);
    }
  }

  value_type get(size_type index) const {
    assert(index < size());
    ++index;
    value_type res{};
    while (index > 0) {
      res += M_tree[index];
      index -= bit_lsb(index);
    }
    return res;
  }
  value_type fold(size_type first, size_type last) const {
    assert(first <= last);
    assert(last <= size());
    value_type res{};
    while (first < last) {
      res += data[last];
      last -= bit_lsb(last);
    }
    while (last < first) {
      res -= data[first];
      first -= bit_lsb(first);
    }
    return res;
  }

  void clear() {
    M_tree.clear();
    M_tree.shrink_to_fit();
  }
  size_type size() const {
    return M_tree.size() - 1;
  }
};

/**
 * @title Fenwick Tree
 */
#line 6 "test/vertex_set_path_sum.test.cpp"

#line 10 "test/vertex_set_path_sum.test.cpp"
#include <iostream>

int main() {
  size_t N, Q;
  std::cin >> N >> Q;
  std::vector<uint64_t> A(N);
  for (auto &x: A) {
    std::cin >> x;
  }
  heavy_light_decomposition hld(N);
  for (size_t i = 1; i < N; ++i) {
    size_t x, y;
    std::cin >> x >> y;
    hld.add_edge(x, y);
  }
  hld.construct();
  fenwick_tree<uint64_t> fen(N);
  for (size_t i = 0; i < N; ++i) {
    fen.add(hld.label[i], A[i]);
  }
  uint64_t answer;
  const auto query = [&](const size_t x, const size_t y) {
    answer += fen.fold(x, y + 1);
  };
  while (Q--) {
    size_t t;
    std::cin >> t;
    if (t == 0) {
      size_t p;
      uint64_t x;
      std::cin >> p >> x;
      fen.add(hld.label[p], x);
    }
    else {
      size_t x, y;
      std::cin >> x >> y;
      answer = 0;
      hld.each_vertex(x, y, query);
      std::cout << answer << '\n';
    }
  }
  return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

