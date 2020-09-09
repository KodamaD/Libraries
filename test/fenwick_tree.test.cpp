
#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "../container/fenwick_tree.cpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

int main() {
  size_t N, Q;
  std::cin >> N >> Q;
  fenwick_tree<uint64_t> seg(N);
  for (size_t i = 0; i < N; ++i) {
    uint32_t x;
    std::cin >> x;
    seg.add(i, x);
  }
  while (Q--) {
    char type;
    std::cin >> type;
    if (type == '0') {
      size_t x;
      uint32_t y;
      std::cin >> x >> y;
      seg.add(x, y);
    }
    else {
      size_t x, y;
      std::cin >> x >> y;
      std::cout << seg.fold(x, y) << '\n';
    }
  }
  return 0;
}
