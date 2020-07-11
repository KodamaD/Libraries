
#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"

#include "../container/sliding_window_aggregation.cpp"
#include "../algebraic/modular.cpp"

#include <iostream>
#include <cstddef>
#include <cstdint>
#include <vector>

using m32 = modular<998244353>;

struct st_monoid {
  struct value_structure {
    using type = std::pair<m32, m32>;
    static type identity() { return { m32(1), m32(0) }; }
    static type operation(const type& v1, const type& v2) { 
      return { v2.first * v1.first, v2.first * v1.second + v2.second };
    }
  };
};

int main() {
  size_t Q;
  std::cin >> Q;
  sliding_window_aggregation<st_monoid> que;
  while (Q--) {
    size_t type;
    std::cin >> type;
    if (type == 0) {
      m32 a, b;
      std::cin >> a.extract() >> b.extract();
      que.push({ a, b });
    }
    else if (type == 1) {
      que.pop();
    }
    else {
      m32 x;
      std::cin >> x.extract();
      auto fold = que.fold();
      std::cout << fold.first * x + fold.second << '\n';
    }
  }
  return 0;
}
