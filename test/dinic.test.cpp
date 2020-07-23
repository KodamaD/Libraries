
#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include "../graph/network.cpp"
#include "../graph/dinic.cpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

int main() {
  size_t L, R, M;
  std::cin >> L >> R >> M;
  network<flow_edge<int32_t>> graph;
  const auto S = graph.add_vertex();
  const auto T = graph.add_vertex();
  const auto left = graph.add_vertices(L);
  const auto right = graph.add_vertices(R);
  while (M--) {
    size_t u, v;
    std::cin >> u >> v;
    graph.emplace_edge(left[u], right[v], 1);
  }
  for (size_t i = 0; i < L; ++i) {
    graph.emplace_edge(S, left[i], 1);
  }
  for (size_t i = 0; i < R; ++i) {
    graph.emplace_edge(right[i], T, 1);
  }
  const auto [flow, built] = dinic(graph).max_flow<false>(S, T);
  std::cout << flow << '\n';
  for (size_t i = 0; i < L; ++i) {
    for (const auto &edge: built[left[i]]) {
      if (edge.flow > 0) {
        std::cout << i << ' ' << right.to_index(edge.dest) << '\n';
        break;
      }
    }
  }
  return 0;
}
