#pragma once

#include "../other/fix_point.cpp"

#include <vector>
#include <stack>

template <class Network>
class strongly_connected_components {
public:
  using network_type = Network;
  using vertex_type  = typename Network::vertex_type;
  using edge_type    = typename Network::edge_type;
  using size_type    = typename Network::size_type;

private:
  std::vector<std::vector<vertex_type>> graph;
  std::vector<std::vector<vertex_type>> revgraph;

public:
  explicit strongly_connected_components(const network_type &net) {
    graph.resize(net.size());
    revgraph.resize(net.size());
    for (size_type src = 0; src < net.size(); ++src) {
      for (const auto &edge: net[src]) {
        graph[src].push_back(edge.dest);
        revgraph[edge.dest].push_back(src);
      }
    }
  }

  std::vector<std::vector<vertex_type>> decompose() const {
    std::vector<bool> visited(graph.size());
    std::stack<vertex_type> topological;
    const auto sort = fix_point([&](auto dfs, const vertex_type u) -> void {
      if (visited[u]) return;
      visited[u] = true;
      for (const auto v: graph[u]) {
        dfs(v);
      }
      topological.push(u);
    });
    for (vertex_type src = 0; src < graph.size(); ++src) {
      sort(src);
    }
    std::vector<std::vector<vertex_type>> group;
    const auto decompose = fix_point([&](const auto dfs, const vertex_type u) -> void {
      if (visited[u]) return;
      visited[u] = true;
      group.back().push_back(u);
      for (const auto v: revgraph[u]) {
        dfs(v);
      }
    });
    std::fill(visited.begin(), visited.end(), false);
    while (!topological.empty()) {
      const auto u = topological.top();
      topological.pop();
      if (!visited[u]) {
        group.push_back({ });
        decompose(u);
      }
    }
    return group;
  }
};

/**
 * @title Strongly Connected Components
 */