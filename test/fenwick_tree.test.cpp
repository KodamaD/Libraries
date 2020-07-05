
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"

#include "../container/fenwick_tree.cpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

int main() {
  size_t N, Q;
  std::cin >> N >> Q;
  fenwick_tree<uint32_t> seg(N);
  while (Q--) {
    char type;
    std::cin >> type;
    if (type == '0') {
      size_t x;
      uint32_t y;
      std::cin >> x >> y;
      seg.add(x - 1, y);
    }
    else {
      size_t x, y;
      std::cin >> x >> y;
      std::cout << seg.fold(x - 1, y) << '\n';
    }
  }
  return 0;
}
