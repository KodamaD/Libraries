
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"

#include "../graph/heavy_light_decomposition.cpp"
#include "../container/fenwick_tree.cpp"

#include <cstddef>
#include <cstdint>
#include <vector>
#include <iostream>

int main() {
  size_t N, Q;
  std::cin >> N >> Q;
  std::vector<uint64_t> A(N);
  for (auto &x: A) {
    std::cin >> x;
  }
  heavy_light_decomposition hld(N);
  for (size_t i = 1; i < N; ++i) {
    size_t x, y;
    std::cin >> x >> y;
    hld.add_edge(x, y);
  }
  hld.construct();
  fenwick_tree<uint64_t> fen(N);
  for (size_t i = 0; i < N; ++i) {
    fen.add(hld.label[i], A[i]);
  }
  uint64_t answer;
  const auto query = [&](const size_t x, const size_t y) {
    answer += fen.fold(x, y + 1);
  };
  while (Q--) {
    size_t t;
    std::cin >> t;
    if (t == 0) {
      size_t p;
      uint64_t x;
      std::cin >> p >> x;
      fen.add(hld.label[p], x);
    }
    else {
      size_t x, y;
      std::cin >> x >> y;
      answer = 0;
      hld.each_vertex(x, y, query);
      std::cout << answer << '\n';
    }
  }
  return 0;
}
