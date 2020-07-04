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


# :warning: graph/dinic.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/dinic.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-06 23:01:53+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp

template <class T>
class dinic {
public:
  using value_type = T;
  using size_type = int;

  static constexpr value_type inf = std::numeric_limits<value_type>::max();

  struct edge_type {
    size_type to, rev;
    value_type cap;
  };

private:
  size_type size;
  std::vector<std::vector<edge_type>> graph;
  std::vector<size_type> level, iter;

  void bfs(size_type start) {
    std::fill(level.begin(), level.end(), -1);
    std::queue<size_type> que;
    level[start] = 0;
    que.push(start);
    while (!que.empty()) {
      size_type u = que.front();
      que.pop();
      for (edge_type e: graph[u]) {
        if (e.cap > 0 && level[e.to] == -1) {
          level[e.to] = level[u] + 1;
          que.push(e.to);
        }
      }
    }
  }

  value_type dfs(size_type cur, size_type goal, const value_type &flow) {
    if (cur == goal) return flow;
    for (size_type &i = iter[cur]; i < graph[cur].size(); ++i) {
      edge_type &e = graph[cur][i];
      if (e.cap > 0 && level[cur] < level[e.to]) {
        value_type tmp = dfs(e.to, goal, std::min(flow, e.cap));
        if (tmp > 0) {
          e.cap -= tmp;
          graph[e.to][e.rev].cap += tmp;
          return tmp;
        }
      }
    }
    return 0;
  }


public:
  dinic() { }
  dinic(size_type size_) { init(size_); }

  void init(size_type size_) {
    size = size_;
    graph.assign(size_, { });
    level.assign(size_, -1);
    iter.assign(size_, 0);
  }

  void add_edge(size_type from, size_type to, const value_type &cap) {
    graph[from].push_back(edge_type{ to, (size_type) graph[to].size(), cap });
    graph[to].push_back(edge_type{ from, (size_type) graph[from].size() - 1, 0 });
  }

  value_type max_flow(size_type start, size_type goal) {
    value_type res = 0;
    while (true) {
      bfs(start);
      if (level[goal] == -1) return res;
      std::fill(iter.begin(), iter.end(), 0);
      value_type tmp;
      while ((tmp = dfs(start, goal, inf)) > 0) {
        res += tmp;
      }
    }
  }

};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/dinic.cpp"

template <class T>
class dinic {
public:
  using value_type = T;
  using size_type = int;

  static constexpr value_type inf = std::numeric_limits<value_type>::max();

  struct edge_type {
    size_type to, rev;
    value_type cap;
  };

private:
  size_type size;
  std::vector<std::vector<edge_type>> graph;
  std::vector<size_type> level, iter;

  void bfs(size_type start) {
    std::fill(level.begin(), level.end(), -1);
    std::queue<size_type> que;
    level[start] = 0;
    que.push(start);
    while (!que.empty()) {
      size_type u = que.front();
      que.pop();
      for (edge_type e: graph[u]) {
        if (e.cap > 0 && level[e.to] == -1) {
          level[e.to] = level[u] + 1;
          que.push(e.to);
        }
      }
    }
  }

  value_type dfs(size_type cur, size_type goal, const value_type &flow) {
    if (cur == goal) return flow;
    for (size_type &i = iter[cur]; i < graph[cur].size(); ++i) {
      edge_type &e = graph[cur][i];
      if (e.cap > 0 && level[cur] < level[e.to]) {
        value_type tmp = dfs(e.to, goal, std::min(flow, e.cap));
        if (tmp > 0) {
          e.cap -= tmp;
          graph[e.to][e.rev].cap += tmp;
          return tmp;
        }
      }
    }
    return 0;
  }


public:
  dinic() { }
  dinic(size_type size_) { init(size_); }

  void init(size_type size_) {
    size = size_;
    graph.assign(size_, { });
    level.assign(size_, -1);
    iter.assign(size_, 0);
  }

  void add_edge(size_type from, size_type to, const value_type &cap) {
    graph[from].push_back(edge_type{ to, (size_type) graph[to].size(), cap });
    graph[to].push_back(edge_type{ from, (size_type) graph[from].size() - 1, 0 });
  }

  value_type max_flow(size_type start, size_type goal) {
    value_type res = 0;
    while (true) {
      bfs(start);
      if (level[goal] == -1) return res;
      std::fill(iter.begin(), iter.end(), 0);
      value_type tmp;
      while ((tmp = dfs(start, goal, inf)) > 0) {
        res += tmp;
      }
    }
  }

};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

