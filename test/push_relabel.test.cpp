
#define PROBLEM "https://yukicoder.me/problems/no/957"

#include "../graph/network.cpp"
#include "../graph/push_relabel.cpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

int main() {
  size_t H, W;
  std::cin >> H >> W;
  network<flow_edge<int64_t>> graph;
  const auto source = graph.add_vertex();
  const auto sink = graph.add_vertex();
  const auto row = graph.add_vertices(H);
  const auto column = graph.add_vertices(W);
  std::vector<int64_t> accum(H);
  for (size_t i = 0; i < H; ++i) {
    for (size_t j = 0; j < W; ++j) {
      int32_t g;
      std::cin >> g;
      accum[i] += g;
      graph.emplace_edge(row[i], column[j], g);
    }
  }
  int64_t sum = 0;
  for (size_t i = 0; i < H; ++i) {
    int64_t r;
    std::cin >> r;
    int64_t min = std::min(accum[i], r);
    sum += r - min;
    graph.emplace_edge(source, row[i], accum[i] - min);
  }
  for (size_t j = 0; j < W; ++j) {
    int64_t r;
    std::cin >> r;
    sum += r;
    graph.emplace_edge(column[j], sink, r);
  }
  std::cout << sum - push_relabel(graph).max_flow(source, sink) << '\n';
  return 0;
}
