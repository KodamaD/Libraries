
#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "../graph/heavy_light_decomposition.cpp"

#include <cstddef>
#include <iostream>
#include <algorithm>
#include <set>

int main() {
  size_t N, Q;
  std::cin >> N >> Q;
  heavy_light_decomposition hld(N);
  for (size_t i = 1; i < N; ++i) {
    size_t p;
    std::cin >> p;
    hld.add_edge(i, p);
  }
  hld.construct();
  while (Q--) {
    size_t u, v;
    std::cin >> u >> v;
    std::cout << hld.lca(u, v) << '\n';
  }
  return 0;
}
