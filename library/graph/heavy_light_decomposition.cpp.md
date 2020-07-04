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


# :warning: graph/heavy_light_decomposition.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/heavy_light_decomposition.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-02 22:24:52+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp

class heavy_light_decomposition {
public:
  using size_type = int32_t;

private:
  std::vector<std::vector<size_type>> graph;
  std::vector<size_type> size, parent, head;
  size_type index;

  void calc_size(size_type u, size_type p) {
    size[u] = 1;
    for (size_type v: graph[u]) {
      if (v != p) {
        calc_size(v, u);
        size[u] += size[v];
      }
    }
  }

  void decompose(size_type u, size_type p, size_type h) {
    label[u] = index;
    head[u] = h;
    parent[u] = p;
    ++index;
    size_type max = -1, heavy = -1;
    for (size_type v : graph[u]) {
      if (v != p) {
        if (max < size[v]) {
          max = size[v];
          heavy = v;
        }
      }
    }
    if (heavy == -1) {
      return;
    }
    decompose(heavy, u, h);
    for (size_type v : graph[u]) {
      if (v != p && v != heavy) {
        decompose(v, u, v);
      }
    }
  }

public:
  std::vector<size_type> label;

  heavy_light_decomposition() { }
  heavy_light_decomposition(size_type size_) { init(size_); }

  void init(size_type size_) {
    graph.assign(size_, { });
    size.assign(size_, 0);
    parent.assign(size_, 0);
    head.assign(size_, 0);
    label.assign(size_, 0);
  }

  void add_edge(size_type u, size_type v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  void build() {
    index = 0;
    calc_size(0, -1);
    decompose(0, -1, 0);
  }

  template <class T> 
  void each_edge(size_type u, size_type v, const T &func) const {
    while (true) {
      if (label[u] > label[v]) {
        std::swap(u, v);
      }
      if (head[u] == head[v]) {
        if (label[u] + 1 <= label[v]) {
          func(label[u] + 1, label[v]);
        }
        return;
      }
      func(label[head[v]], label[v]);
      v = parent[head[v]];
    }
  }

  template <class T> 
  void each_vertex(size_type u, size_type v, const T &func) const {
    while (true) {
      if (label[u] > label[v]) {
        std::swap(u, v);
      }
      if (head[u] == head[v]) {
        func(label[u], label[v]);
        return;
      }
      func(label[head[v]], label[v]);
      v = parent[head[v]];
    }
  }

  size_type lca(size_type u, size_type v) const {
    if (label[u] > label[v]) {
      std::swap(u, v);
    }
    while (label[u] <= label[v]) {
      if (head[u] == head[v]) {
        return u;
      }
      v = parent[head[v]];
    }
    return v;
  }

};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/heavy_light_decomposition.cpp"

class heavy_light_decomposition {
public:
  using size_type = int32_t;

private:
  std::vector<std::vector<size_type>> graph;
  std::vector<size_type> size, parent, head;
  size_type index;

  void calc_size(size_type u, size_type p) {
    size[u] = 1;
    for (size_type v: graph[u]) {
      if (v != p) {
        calc_size(v, u);
        size[u] += size[v];
      }
    }
  }

  void decompose(size_type u, size_type p, size_type h) {
    label[u] = index;
    head[u] = h;
    parent[u] = p;
    ++index;
    size_type max = -1, heavy = -1;
    for (size_type v : graph[u]) {
      if (v != p) {
        if (max < size[v]) {
          max = size[v];
          heavy = v;
        }
      }
    }
    if (heavy == -1) {
      return;
    }
    decompose(heavy, u, h);
    for (size_type v : graph[u]) {
      if (v != p && v != heavy) {
        decompose(v, u, v);
      }
    }
  }

public:
  std::vector<size_type> label;

  heavy_light_decomposition() { }
  heavy_light_decomposition(size_type size_) { init(size_); }

  void init(size_type size_) {
    graph.assign(size_, { });
    size.assign(size_, 0);
    parent.assign(size_, 0);
    head.assign(size_, 0);
    label.assign(size_, 0);
  }

  void add_edge(size_type u, size_type v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  void build() {
    index = 0;
    calc_size(0, -1);
    decompose(0, -1, 0);
  }

  template <class T> 
  void each_edge(size_type u, size_type v, const T &func) const {
    while (true) {
      if (label[u] > label[v]) {
        std::swap(u, v);
      }
      if (head[u] == head[v]) {
        if (label[u] + 1 <= label[v]) {
          func(label[u] + 1, label[v]);
        }
        return;
      }
      func(label[head[v]], label[v]);
      v = parent[head[v]];
    }
  }

  template <class T> 
  void each_vertex(size_type u, size_type v, const T &func) const {
    while (true) {
      if (label[u] > label[v]) {
        std::swap(u, v);
      }
      if (head[u] == head[v]) {
        func(label[u], label[v]);
        return;
      }
      func(label[head[v]], label[v]);
      v = parent[head[v]];
    }
  }

  size_type lca(size_type u, size_type v) const {
    if (label[u] > label[v]) {
      std::swap(u, v);
    }
    while (label[u] <= label[v]) {
      if (head[u] == head[v]) {
        return u;
      }
      v = parent[head[v]];
    }
    return v;
  }

};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

