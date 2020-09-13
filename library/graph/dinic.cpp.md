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


# :heavy_check_mark: Dinic

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/dinic.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-13 16:51:07+09:00




## Depends on

* :heavy_check_mark: <a href="../other/fix_point.cpp.html">Lambda Recursion</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/dinic.test.cpp.html">test/dinic.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "../other/fix_point.cpp"

#include <queue>
#include <algorithm>
#include <cassert>

template <class Network>
class dinic {
public:
  using network_type = Network;
  using vertex_type  = typename Network::vertex_type;
  using edge_type    = typename Network::edge_type;
  using size_type    = typename Network::size_type;
  using flow_type    = typename Network::edge_type::flow_type;
  using height_type  = uint32_t;

  static_assert(std::is_integral<flow_type>::value, "invalid flow type :: non-integral");

private:
  class residual_edge: public edge_type {
  public:
    const size_type rev;
    const bool is_rev;
    explicit residual_edge(const edge_type &edge, const size_type rev, const bool is_rev):
      edge_type(edge), rev(rev), is_rev(is_rev)
    { }
  };

  class node_type {
  public:
    std::vector<residual_edge> edges;
    height_type level;
    size_type iter;
    node_type() = default;
  };

  flow_type M_remain(const residual_edge &edge) {
    return edge.capacity - edge.flow;
  }
  residual_edge &M_cur_edge(node_type &node) {
    return node.edges[node.iter];
  }
  residual_edge &M_rev_edge(const residual_edge &edge) {
    return M_graph[edge.dest].edges[edge.rev];
  }

  void M_bfs(const vertex_type source) {
    for (auto &node: M_graph) {
      node.level = M_graph.size() + 1;
    }
    M_graph[source].level = 0;
    std::queue<vertex_type> queue;
    queue.push(source);
    while (!queue.empty()) {
      const auto vert = queue.front();
      queue.pop();
      for (const auto &edge: M_graph[vert].edges) {
        if (M_remain(edge) > 0) {
          if (M_graph[edge.dest].level == M_graph.size() + 1) {
            M_graph[edge.dest].level = M_graph[vert].level + 1;
            queue.push(edge.dest);
          }
        }
      }
    }
  }

  std::vector<node_type> M_graph;

public:
  dinic() = default;
  explicit dinic(const network_type &net) {
    M_graph.resize(net.size());
    for (size_type src = 0; src < net.size(); ++src) {
      for (const auto &edge: net[src]) {
        M_graph[src].edges.emplace_back(edge, M_graph[edge.dest].edges.size(), false);
        M_graph[edge.dest].edges.emplace_back(edge.reverse(), M_graph[src].edges.size() - 1, true);
      }
    }
  }

  template <bool ValueOnly = true>
  typename std::enable_if<ValueOnly, flow_type>::type
  max_flow(const vertex_type source, const vertex_type sink, const bool initialize_edges = false) {
    assert(source < M_graph.size());
    assert(sink < M_graph.size());
    assert(source != sink);
    const auto dfs = fix_point([&](const auto dfs, 
      const vertex_type vert, const flow_type flow) -> flow_type {
      if (vert == sink) return flow;
      auto &node = M_graph[vert];
      for (; node.iter < node.edges.size(); ++node.iter) {
        auto &edge = M_cur_edge(node);
        if (M_remain(edge) > 0 && node.level < M_graph[edge.dest].level) {
          const auto push = dfs(edge.dest, std::min(flow, M_remain(edge)));
          if (push > 0) {
            edge.flow += push;
            M_rev_edge(edge).flow -= push;
            return push;
          }
        }
      }
      return 0;
    });
    flow_type max_capacity = 0;
    for (auto &node: M_graph) {
      for (auto &edge: node.edges) {
        if (initialize_edges) {
          if (!edge.is_rev) edge.flow = 0;
          else edge.flow = edge.capacity;
        }
        max_capacity = std::max(max_capacity, edge.capacity);
      }
    }
    flow_type flow = 0;
    while (true) {
      M_bfs(source);
      if (M_graph[sink].level == M_graph.size() + 1) {
        return flow;
      }
      for (auto &node: M_graph) {
        node.iter = 0;
      }
      flow_type push;
      while ((push = dfs(source, max_capacity)) > 0) {
        flow += push;
      }
    }
    return flow;
  }

  template <bool ValueOnly = true>
  typename std::enable_if<!ValueOnly, std::pair<flow_type, network_type>>::type
  max_flow(const vertex_type source, const vertex_type sink, const bool initialize_edges = false) {
    const auto flow = max_flow<true>(source, sink, initialize_edges);
    network_type graph;
    graph.template add_vertices <false>(M_graph.size());
    for (size_type index = 0; index < M_graph.size(); ++index) {
      for (const auto &edge: M_graph[index].edges) {
        if (!edge.is_rev) {
          graph.add_edge(static_cast<edge_type>(edge));
        }
      }
    }
    return std::make_pair(flow, std::move(graph));
  }
};

/**
 * @title Dinic
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "graph/dinic.cpp"

#line 2 "other/fix_point.cpp"

#include <utility>

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
#line 4 "graph/dinic.cpp"

#include <queue>
#include <algorithm>
#include <cassert>

template <class Network>
class dinic {
public:
  using network_type = Network;
  using vertex_type  = typename Network::vertex_type;
  using edge_type    = typename Network::edge_type;
  using size_type    = typename Network::size_type;
  using flow_type    = typename Network::edge_type::flow_type;
  using height_type  = uint32_t;

  static_assert(std::is_integral<flow_type>::value, "invalid flow type :: non-integral");

private:
  class residual_edge: public edge_type {
  public:
    const size_type rev;
    const bool is_rev;
    explicit residual_edge(const edge_type &edge, const size_type rev, const bool is_rev):
      edge_type(edge), rev(rev), is_rev(is_rev)
    { }
  };

  class node_type {
  public:
    std::vector<residual_edge> edges;
    height_type level;
    size_type iter;
    node_type() = default;
  };

  flow_type M_remain(const residual_edge &edge) {
    return edge.capacity - edge.flow;
  }
  residual_edge &M_cur_edge(node_type &node) {
    return node.edges[node.iter];
  }
  residual_edge &M_rev_edge(const residual_edge &edge) {
    return M_graph[edge.dest].edges[edge.rev];
  }

  void M_bfs(const vertex_type source) {
    for (auto &node: M_graph) {
      node.level = M_graph.size() + 1;
    }
    M_graph[source].level = 0;
    std::queue<vertex_type> queue;
    queue.push(source);
    while (!queue.empty()) {
      const auto vert = queue.front();
      queue.pop();
      for (const auto &edge: M_graph[vert].edges) {
        if (M_remain(edge) > 0) {
          if (M_graph[edge.dest].level == M_graph.size() + 1) {
            M_graph[edge.dest].level = M_graph[vert].level + 1;
            queue.push(edge.dest);
          }
        }
      }
    }
  }

  std::vector<node_type> M_graph;

public:
  dinic() = default;
  explicit dinic(const network_type &net) {
    M_graph.resize(net.size());
    for (size_type src = 0; src < net.size(); ++src) {
      for (const auto &edge: net[src]) {
        M_graph[src].edges.emplace_back(edge, M_graph[edge.dest].edges.size(), false);
        M_graph[edge.dest].edges.emplace_back(edge.reverse(), M_graph[src].edges.size() - 1, true);
      }
    }
  }

  template <bool ValueOnly = true>
  typename std::enable_if<ValueOnly, flow_type>::type
  max_flow(const vertex_type source, const vertex_type sink, const bool initialize_edges = false) {
    assert(source < M_graph.size());
    assert(sink < M_graph.size());
    assert(source != sink);
    const auto dfs = fix_point([&](const auto dfs, 
      const vertex_type vert, const flow_type flow) -> flow_type {
      if (vert == sink) return flow;
      auto &node = M_graph[vert];
      for (; node.iter < node.edges.size(); ++node.iter) {
        auto &edge = M_cur_edge(node);
        if (M_remain(edge) > 0 && node.level < M_graph[edge.dest].level) {
          const auto push = dfs(edge.dest, std::min(flow, M_remain(edge)));
          if (push > 0) {
            edge.flow += push;
            M_rev_edge(edge).flow -= push;
            return push;
          }
        }
      }
      return 0;
    });
    flow_type max_capacity = 0;
    for (auto &node: M_graph) {
      for (auto &edge: node.edges) {
        if (initialize_edges) {
          if (!edge.is_rev) edge.flow = 0;
          else edge.flow = edge.capacity;
        }
        max_capacity = std::max(max_capacity, edge.capacity);
      }
    }
    flow_type flow = 0;
    while (true) {
      M_bfs(source);
      if (M_graph[sink].level == M_graph.size() + 1) {
        return flow;
      }
      for (auto &node: M_graph) {
        node.iter = 0;
      }
      flow_type push;
      while ((push = dfs(source, max_capacity)) > 0) {
        flow += push;
      }
    }
    return flow;
  }

  template <bool ValueOnly = true>
  typename std::enable_if<!ValueOnly, std::pair<flow_type, network_type>>::type
  max_flow(const vertex_type source, const vertex_type sink, const bool initialize_edges = false) {
    const auto flow = max_flow<true>(source, sink, initialize_edges);
    network_type graph;
    graph.template add_vertices <false>(M_graph.size());
    for (size_type index = 0; index < M_graph.size(); ++index) {
      for (const auto &edge: M_graph[index].edges) {
        if (!edge.is_rev) {
          graph.add_edge(static_cast<edge_type>(edge));
        }
      }
    }
    return std::make_pair(flow, std::move(graph));
  }
};

/**
 * @title Dinic
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

