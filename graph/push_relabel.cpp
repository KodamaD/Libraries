#pragma once

#include <cstddef>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>
#include <utility>
#include <type_traits>

namespace push_relabel_detail {

  class stack_helper {
  private:
    const size_t M_size;
    std::vector<size_t> M_stack;
  public:
    explicit stack_helper(const size_t size):
      M_size(size), M_stack(size * 2)
    { clear(); }
    size_t top(const size_t height) const {
      return M_stack[M_size + height];
    }
    bool empty(const size_t height) const { 
      return M_stack[M_size + height] == M_size + height; 
    }
    void pop(const size_t height) {
      M_stack[M_size + height] = M_stack[M_stack[M_size + height]];
    }
    void push(const size_t height, const size_t node) {
      M_stack[node] = M_stack[M_size + height];
      M_stack[M_size + height] = node;
    }
    void clear() {
      std::iota(M_stack.begin() + M_size, M_stack.end(), M_size);
    }
  };

  class list_helper {
  private:
    const size_t M_size;
    std::vector<std::pair<size_t, size_t>> M_list;
  public:
    explicit list_helper(const size_t size):
      M_size(size), M_list(size * 2)
    { clear(); }
    bool empty(const size_t height) {
      return M_list[M_size + height].second == M_size + height;
    }
    bool more_than_one(const size_t height) {
      return M_list[M_size + height].first != M_list[M_size + height].second;
    }
    void insert(const size_t height, const size_t node) {
      M_list[node].first = M_list[M_size + height].first;
      M_list[node].second = M_size + height;
      M_list[M_list[M_size + height].first].second = node;
      M_list[M_size + height].first = node;
    }
    void erase(const size_t node) {
      M_list[M_list[node].first].second = M_list[node].second;
      M_list[M_list[node].second].first = M_list[node].first;
    }
    void clear() {
      for (size_t index = M_size; index < M_size * 2; ++index) {
        M_list[index].first = M_list[index].second = index;
      }
    }
    void clear(const size_t height) {
      const size_t index = M_size + height;
      M_list[index].first = M_list[index].second = index;
    }
    template <class Func>
    void apply_all(const size_t height, Func &&func) {
      size_t index = M_list[M_size + height].second;
      while (index < M_size) {
        func(index);
        index = M_list[index].second;
      }
    }
  };

};

template <class Network>
class push_relabel {
public:
  using network_type = Network;
  using vertex_type  = typename Network::vertex_type;
  using edge_type    = typename Network::edge_type;
  using size_type    = typename Network::size_type;
  using flow_type    = typename Network::edge_type::flow_type;
  using height_type  = size_t;

  static_assert(std::is_integral<flow_type>::value, "invalid flow type :: non-integral");

private:
  class residual_edge {
  public:
    const vertex_type dest;
    flow_type remain;
    const size_type rev;
    const bool is_rev;
    explicit residual_edge(const vertex_type dest, const flow_type remain, 
      const size_type rev, const bool is_rev):
      dest(dest), remain(remain), rev(rev), is_rev(is_rev)
    { }
  };

  class node_type {
  public:
    std::vector<residual_edge> edges;
    flow_type excess;
    height_type height;
    size_type iter;
    node_type() = default;
  };

  residual_edge &M_cur_edge(node_type &node) {
    return node.edges[node.iter];
  }
  residual_edge &M_rev_edge(const residual_edge &edge) {
    return M_graph[edge.dest].edges[edge.rev];
  }
  void M_push(node_type &node, residual_edge &edge) {
    const auto flow = std::min(node.excess, edge.remain);
    edge.remain -= flow;
    node.excess -= flow;
    M_rev_edge(edge).remain += flow;
    M_graph[edge.dest].excess += flow;
  }
  void M_relabel(node_type &node) {
    height_type min = M_graph.size() + 1;
    for (const auto &edge: node.edges) {
      if (edge.remain > 0 && min > M_graph[edge.dest].height + 1) {
        min = M_graph[edge.dest].height + 1;
      }
    }
    node.height = min;
  }

  std::vector<node_type> M_graph;

public:
  push_relabel() = default;
  explicit push_relabel(const network_type &net) {
    const auto &graph = net.get();
    M_graph.resize(graph.size());
    for (size_type src = 0; src < graph.size(); ++src) {
      for (const auto &edge: graph[src]) {
        M_graph[src].edges.emplace_back(edge.dest, edge.capacity, M_graph[edge.dest].edges.size(), false);
        M_graph[edge.dest].edges.emplace_back(src, 0, M_graph[src].edges.size() - 1, true);
      }
    }
  }

  flow_type max_flow(const vertex_type source, const vertex_type sink) {
    push_relabel_detail::stack_helper active(M_graph.size());
    push_relabel_detail::list_helper level(M_graph.size());
    height_type min_gap, max_active;
    {
      for (auto &node: M_graph) {
        node.excess = 0;
        node.height = M_graph.size() + 1;
        node.iter = 0;
        for (auto &edge: node.edges) {
          if (edge.is_rev) edge.remain = 0;
          else edge.remain = edge.remain + M_rev_edge(edge).remain;
        }
      }
      M_graph[sink].height = 0;
      std::queue<vertex_type> queue;
      queue.push(sink);
      while (!queue.empty()) {
        const auto vert = queue.front();
        queue.pop();
        for (const auto &edge: M_graph[vert].edges) {
          if (M_rev_edge(edge).remain > 0) {
            if (M_graph[edge.dest].height == M_graph.size() + 1) {
              M_graph[edge.dest].height = M_graph[vert].height + 1;
              queue.push(edge.dest);
            }
          }
        }
      }
      if (M_graph[source].height == M_graph.size() + 1) {
        return 0;
      }
      for (auto &edge: M_graph[source].edges) {
        M_graph[source].excess += edge.remain;
        M_push(M_graph[source], edge);
      }
      M_graph[source].height = M_graph.size();
      min_gap = M_graph.size();
      max_active = 0;
      for (size_type index = 0; index < M_graph.size(); ++index) {
        const auto &node = M_graph[index];
        if (node.height < M_graph.size()) {
          if (node.excess > 0 && index != sink) {
            active.push(node.height, index);
            max_active = std::max(max_active, node.height);
          }
          level.insert(node.height, index);
        }
      }
      for (size_type index = 0; index < M_graph.size(); ++index) {
        if (level.empty(index)) {
          min_gap = index;
          break;
        }
      }
    }
    while (max_active > 0) {
      if (active.empty(max_active)) {
        --max_active;
        continue;
      }
      const auto vert = active.top(max_active);
      auto &node = M_graph[vert];
      active.pop(max_active);
      while (true) {
        auto &edge = M_cur_edge(node);
        const auto &dest = M_graph[edge.dest];
        if (edge.remain > 0 && node.height == dest.height + 1) {
          if (dest.excess == 0 && edge.dest != sink) {
            active.push(dest.height, edge.dest);
            max_active = std::max(max_active, dest.height);
          }
          M_push(node, edge);
          if (node.excess == 0) {
            break;
          }
        }
        node.iter++;
        if (node.iter == node.edges.size()) {
          node.iter = 0;
          if (level.more_than_one(node.height)) {
            level.erase(vert);
            M_relabel(node);
            if (node.height > min_gap) {
              node.height = M_graph.size() + 1;
              break;
            }
            if (node.height == min_gap) {
              ++min_gap;
            }
            level.insert(node.height, vert);
          }
          else {
            for (height_type index = node.height; index < min_gap; ++index) {
              level.apply_all(index, [&](const vertex_type vert) {
                M_graph[vert].height = M_graph.size() + 1;
              });
              level.clear(index);
            }
            break;
          }
        }
      }
      max_active = std::min(max_active, min_gap - 1);
    }
    return M_graph[sink].excess;
  }

};

/**
 * @title Push Relabel
 */