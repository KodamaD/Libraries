#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include "../graph/network.cpp"
#include "../graph/scc.cpp"

#include <cstddef>
#include <iostream>

int main() {
  size_t N, M;
  std::cin >> N >> M;
  network<base_edge> net;
  net.add_vertices<false>(N);
  for (size_t i = 0; i < M; ++i) {
    size_t a, b;
    std::cin >> a >> b;
    net.emplace_edge(a, b);
  }
  const auto group = strongly_connected_components(net).decompose();
  std::cout << group.size() << '\n';
  for (const auto &vec: group) {
    std::cout << vec.size();
    for (const auto u: vec) {
      std::cout << ' ' << u;
    }
    std::cout << '\n';
  }
  return 0;
}
