
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include "../graph/union_find.cpp"

#include <cstddef>
#include <iostream>

int main() {
  size_t N, Q;
  std::cin >> N >> Q;
  union_find dsu(N);
  while (Q--) {
    size_t t, u, v;
    std::cin >> t >> u >> v;
    if (t == 0) {
      dsu.unite(u, v);
    }
    else {
      std::cout << dsu.same_component(u, v) << '\n';
    }
  }
}
