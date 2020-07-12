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


# :heavy_check_mark: test/union_find.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/union_find.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-12 13:43:20+09:00


* see: <a href="https://judge.yosupo.jp/problem/unionfind">https://judge.yosupo.jp/problem/unionfind</a>


## Depends on

* :heavy_check_mark: <a href="../../library/graph/union_find.cpp.html">Union Find</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp

#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include "../graph/union_find.cpp"

#include <cstddef>
#include <iostream>

int main() {
  size_t N, Q;
  std::cin >> N >> Q;
  union_find dsu(N);
  while (Q--) {
    size_t t, u, v;
    std::cin >> t >> u >> v;
    if (t == 0) {
      dsu.unite(u, v);
    }
    else {
      std::cout << dsu.same_component(u, v) << '\n';
    }
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/union_find.test.cpp"

#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#line 2 "graph/union_find.cpp"

#include <cstddef>
#include <vector>
#include <utility>

class union_find {
public:
  using size_type = size_t;

private:
  class node_type {
  public:
    size_type parent, size;
    node_type(size_type parent): 
      parent(parent), size(1) 
    { }
  };

  size_type M_components;
  std::vector<node_type> M_forest;

public:
  union_find() = default;
  explicit union_find(const size_type size) { initialize(size); }

  void initialize(const size_type size) {
    clear();
    M_components = size;
    M_forest.reserve(size);
    for (size_type index = 0; index < size; ++index) {
      M_forest.emplace_back(index);
    }
  }

  size_type find_parent(const size_type node) {
    size_type &parent = M_forest[node].parent;
    if (node == parent) return node;
    return parent = find_parent(parent);
  }
  size_type count_components() const { 
    return M_components; 
  }
  size_type component_size(const size_type node) { 
    return M_forest[find_parent(node)].size;
  }

  bool unite(size_type node1, size_type node2) {
    node1 = find_parent(node1);
    node2 = find_parent(node2);
    if (node1 == node2) return false;
    if (M_forest[node1].size < M_forest[node2].size) {
      std::swap(node1, node2);
    }
    M_forest[node1].size += M_forest[node2].size;
    M_forest[node2].parent = node1;
    --M_components;
    return true;
  }
  bool same_component(const size_type node1, const size_type node2) { 
    return find_parent(node1) == find_parent(node2); 
  }

  size_type size() const {
    return M_forest.size();
  }
  bool empty() const {
    return M_forest.empty();
  }
  void clear() {
    M_components = 0;
    M_forest.clear();
    M_forest.shrink_to_fit();
  }

};

/**
 * @title Union Find
 */
#line 5 "test/union_find.test.cpp"

#line 7 "test/union_find.test.cpp"
#include <iostream>

int main() {
  size_t N, Q;
  std::cin >> N >> Q;
  union_find dsu(N);
  while (Q--) {
    size_t t, u, v;
    std::cin >> t >> u >> v;
    if (t == 0) {
      dsu.unite(u, v);
    }
    else {
      std::cout << dsu.same_component(u, v) << '\n';
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

