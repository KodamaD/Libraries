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


# :warning: graph/union_find.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/union_find.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-04 16:35:04+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <utility>

class union_find {
private:
  size_t component;
  std::vector<int32_t> parent;

public:
  union_find() = default;
  union_find(size_t size_) { init(size_); }

  void init(size_t size_) {
    component = size_;
    parent.assign(size_, -1);
  }

  size_t count_components() const { 
    return component; 
  }
  size_t component_size(size_t i) { 
    return -parent[find_parent(i)]; 
  }
  bool same_component(size_t i, size_t j) { 
    return find_parent(i) == find_parent(j); 
  }

  size_t find_parent(size_t i) {
    if (parent[i] < 0) {
      return i;
    }
    else {
      return parent[i] = find_parent(parent[i]);
    }
  }

  bool unite(size_t i, size_t j) {
    i = find_parent(i);
    j = find_parent(j);
    if (i == j) {
      return false;
    }
    if (parent[i] > parent[j]) {
      std::swap(i, j);
    }
    parent[i] += parent[j];
    parent[j] = i;
    --component;
    return true;
  }

};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "graph/union_find.cpp"

#include <cstddef>
#include <cstdint>
#include <vector>
#include <utility>

class union_find {
private:
  size_t component;
  std::vector<int32_t> parent;

public:
  union_find() = default;
  union_find(size_t size_) { init(size_); }

  void init(size_t size_) {
    component = size_;
    parent.assign(size_, -1);
  }

  size_t count_components() const { 
    return component; 
  }
  size_t component_size(size_t i) { 
    return -parent[find_parent(i)]; 
  }
  bool same_component(size_t i, size_t j) { 
    return find_parent(i) == find_parent(j); 
  }

  size_t find_parent(size_t i) {
    if (parent[i] < 0) {
      return i;
    }
    else {
      return parent[i] = find_parent(parent[i]);
    }
  }

  bool unite(size_t i, size_t j) {
    i = find_parent(i);
    j = find_parent(j);
    if (i == j) {
      return false;
    }
    if (parent[i] > parent[j]) {
      std::swap(i, j);
    }
    parent[i] += parent[j];
    parent[j] = i;
    --component;
    return true;
  }

};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
