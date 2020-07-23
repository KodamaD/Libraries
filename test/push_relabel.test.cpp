
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_A"

#include "../graph/network.cpp"
#include "../graph/push_relabel.cpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

int main() {
  size_t V, E;
  std::cin >> V >> E;
  network<flow_edge<int32_t>> graph;
  graph.add_vertices<false>(V);
  while (E--) {
    size_t u, v;
    std::cin >> u >> v;
    int32_t c;
    std::cin >> c;
    graph.emplace_edge(u, v, c);
  }
  std::cout << push_relabel<decltype(graph)>(graph).max_flow(0, V - 1) << '\n';
  return 0;
}
