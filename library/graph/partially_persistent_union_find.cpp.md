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


# :warning: Partially Persistent Union Find

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/partially_persistent_union_find.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-09 18:08:09+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cstddef>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

class partially_persistent_union_find {
public:
  using size_type = size_t;
  using time_type = size_t;

  static time_type far_future() {
    return static_cast<time_type>(-1);
  }

private:
  class node_type {
  public:
    size_type parent;
    time_type updated;
    std::vector<time_type> history;
    std::vector<size_type> size;
    node_type(size_type parent):
      parent(parent), updated(far_future()),
      history(1, 0), size(1, 1)
    { }
  };

  std::vector<node_type> M_forest;
  std::vector<size_type> M_components;

public:
  partially_persistent_union_find() = default;
  explicit partially_persistent_union_find(const size_type size) { initialize(size); }

  void initialize(const size_type size) {
    clear();
    M_forest.reserve(size);
    for (size_type index = 0; index < size; ++index) {
      M_forest.emplace_back(index);
    }
    M_components.push_back(size);
  }

  size_type find_parent(const size_type node, const time_type time) const {
    assert(node < size());
    if (M_forest[node].updated > time) return node;
    return find_parent(M_forest[node].parent, time);
  }
  size_type count_components(const time_type time) const {
    return M_components[std::min(now(), time)];
  }
  size_type component_size(size_type node, time_type time) const {
    assert(node < size());
    time = std::min(time, now());
    node = find_parent(node, time);
    const auto &history = M_forest[node].history;
    auto index = std::lower_bound(history.cbegin(), history.cend(), time + 1) - history.cbegin() - 1;
    return M_forest[node].size[index];
  }

  time_type when(const size_type node1, const size_type node2) const {
    assert(node1 < size());
    assert(node2 < size());
    if (!same_component(node1, node2, now())) return far_future();
    time_type ok = now(), ng = 0, md;
    while (ok - ng > 1) {
      md = (ok + ng) / 2;
      (same_component(node1, node2, md) ? ok : ng) = md;
    }
    return ok;
  }

  bool same_component(const size_type node1, const size_type node2, const time_type time) const {
    assert(node1 < size());
    assert(node2 < size());
    return find_parent(node1, time) == find_parent(node2, time);
  }
  bool unite(size_type node1, size_type node2) {
    assert(node1 < size());
    assert(node2 < size());
    node1 = find_parent(node1, now());
    node2 = find_parent(node2, now());
    size_type current = M_components.back();
    if (node1 == node2) {
      M_components.push_back(current);
      return false;
    }
    M_components.push_back(current - 1);
    const size_type size1 = M_forest[node1].size.back();
    const size_type size2 = M_forest[node2].size.back();
    if (size1 < size2) std::swap(node1, node2);
    M_forest[node1].history.push_back(now());
    M_forest[node1].size.push_back(size1 + size2);
    M_forest[node2].parent = node1;
    M_forest[node2].updated = now();
    return true;
  }

  time_type now() const {
    return M_components.size() - 1;
  }
  size_type size() const {
    return M_forest.size();
  }
  bool empty() const {
    return M_forest.empty();
  }
  void clear() {
    M_forest.clear();
    M_forest.shrink_to_fit();
    M_components.clear();
    M_components.shrink_to_fit();
  }
};

/**
 * @title Partially Persistent Union Find
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "graph/partially_persistent_union_find.cpp"

#include <cstddef>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

class partially_persistent_union_find {
public:
  using size_type = size_t;
  using time_type = size_t;

  static time_type far_future() {
    return static_cast<time_type>(-1);
  }

private:
  class node_type {
  public:
    size_type parent;
    time_type updated;
    std::vector<time_type> history;
    std::vector<size_type> size;
    node_type(size_type parent):
      parent(parent), updated(far_future()),
      history(1, 0), size(1, 1)
    { }
  };

  std::vector<node_type> M_forest;
  std::vector<size_type> M_components;

public:
  partially_persistent_union_find() = default;
  explicit partially_persistent_union_find(const size_type size) { initialize(size); }

  void initialize(const size_type size) {
    clear();
    M_forest.reserve(size);
    for (size_type index = 0; index < size; ++index) {
      M_forest.emplace_back(index);
    }
    M_components.push_back(size);
  }

  size_type find_parent(const size_type node, const time_type time) const {
    assert(node < size());
    if (M_forest[node].updated > time) return node;
    return find_parent(M_forest[node].parent, time);
  }
  size_type count_components(const time_type time) const {
    return M_components[std::min(now(), time)];
  }
  size_type component_size(size_type node, time_type time) const {
    assert(node < size());
    time = std::min(time, now());
    node = find_parent(node, time);
    const auto &history = M_forest[node].history;
    auto index = std::lower_bound(history.cbegin(), history.cend(), time + 1) - history.cbegin() - 1;
    return M_forest[node].size[index];
  }

  time_type when(const size_type node1, const size_type node2) const {
    assert(node1 < size());
    assert(node2 < size());
    if (!same_component(node1, node2, now())) return far_future();
    time_type ok = now(), ng = 0, md;
    while (ok - ng > 1) {
      md = (ok + ng) / 2;
      (same_component(node1, node2, md) ? ok : ng) = md;
    }
    return ok;
  }

  bool same_component(const size_type node1, const size_type node2, const time_type time) const {
    assert(node1 < size());
    assert(node2 < size());
    return find_parent(node1, time) == find_parent(node2, time);
  }
  bool unite(size_type node1, size_type node2) {
    assert(node1 < size());
    assert(node2 < size());
    node1 = find_parent(node1, now());
    node2 = find_parent(node2, now());
    size_type current = M_components.back();
    if (node1 == node2) {
      M_components.push_back(current);
      return false;
    }
    M_components.push_back(current - 1);
    const size_type size1 = M_forest[node1].size.back();
    const size_type size2 = M_forest[node2].size.back();
    if (size1 < size2) std::swap(node1, node2);
    M_forest[node1].history.push_back(now());
    M_forest[node1].size.push_back(size1 + size2);
    M_forest[node2].parent = node1;
    M_forest[node2].updated = now();
    return true;
  }

  time_type now() const {
    return M_components.size() - 1;
  }
  size_type size() const {
    return M_forest.size();
  }
  bool empty() const {
    return M_forest.empty();
  }
  void clear() {
    M_forest.clear();
    M_forest.shrink_to_fit();
    M_components.clear();
    M_components.shrink_to_fit();
  }
};

/**
 * @title Partially Persistent Union Find
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

