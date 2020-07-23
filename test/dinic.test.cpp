
#define PROBLEM "https://yukicoder.me/problems/no/1123"

#include "../graph/network.cpp"
#include "../graph/dinic.cpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

int main() {
  size_t H, W;
  std::cin >> H >> W;
  std::vector<uint32_t> A(H), B(W);
  for (auto &x: A) {
    std::cin >> x;
  }
  for (auto &x: B) {
    std::cin >> x;
  }
  const auto sumA = std::accumulate(A.cbegin(), A.cend(), uint32_t(0));
  const auto sumB = std::accumulate(B.cbegin(), B.cend(), uint32_t(0));
  if (sumA != sumB) {
    std::cout << ":(\n";
    return 0;
  }
  size_t K;
  std::cin >> K;
  std::vector<std::vector<char>> ans(H, std::vector<char>(W, '.'));
  while (K--) {
    size_t x, y;
    std::cin >> x >> y;
    --x; --y;
    ans[x][y] = 'x';
  }
  network<flow_edge<uint32_t>> graph;
  const auto S = graph.add_vertex();
  const auto T = graph.add_vertex();
  const auto left = graph.add_vertices(H);
  const auto right = graph.add_vertices(W);
  for (size_t i = 0; i < H; ++i) {
    graph.emplace_edge(S, left[i], A[i]);
  }
  for (size_t j = 0; j < W; ++j) {
    graph.emplace_edge(right[j], T, B[j]);
  }
  for (size_t i = 0; i < H; ++i) {
    for (size_t j = 0; j < W; ++j) {
      if (ans[i][j] != 'x') {
        graph.emplace_edge(left[i], right[j], 1);
      }
    }
  }
  const auto [flow, result] = dinic(graph).max_flow<false>(S, T);
  if (flow != sumA) {
    std::cout << ":(\n";
    return 0;
  }
  std::cout << "Yay!\n";
  for (size_t i = 0; i < H; ++i) {
    for (const auto &e: result[left[i]]) {
      if (e.flow > 0) {
        ans[i][right.to_index(e.dest)] = 'o';
      }
    }
  }
  for (const auto &vec: ans) {
    for (auto x: vec) {
      std::cout << x;
    }
    std::cout << '\n';
  }
  return 0;
}
