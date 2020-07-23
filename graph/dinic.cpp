#pragma once

#include <queue>
#include <algorithm>

#include "../graph/network.cpp"
#include "../other/fix_point.cpp"

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
    const auto &graph = net.get();
    M_graph.resize(graph.size());
    for (size_type src = 0; src < graph.size(); ++src) {
      for (const auto &edge: graph[src]) {
        M_graph[src].edges.emplace_back(edge, M_graph[edge.dest].edges.size(), false);
        M_graph[edge.dest].edges.emplace_back(edge.reverse(), M_graph[src].edges.size() - 1, true);
      }
    }
  }

  template <bool ValueOnly = true>
  typename std::enable_if<ValueOnly, flow_type>::type
  max_flow(const vertex_type source, const vertex_type sink, const bool initialize_edges = false) {
    const auto dfs = make_fix_point([&](const auto dfs, 
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