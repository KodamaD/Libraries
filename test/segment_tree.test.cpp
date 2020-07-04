
#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include "../container/segment_tree.cpp"
#include "../algebraic/modular.cpp"

#include <utility>
#include <iostream>
#include <cstddef>
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
  size_t N, Q;
  std::cin >> N >> Q;
  std::vector<std::pair<m32, m32>> F(N);
  for (auto &[p, q]: F) {
    std::cin >> p.extract() >> q.extract();
  }
  segment_tree<st_monoid> seg(F.begin(), F.end());
  while (Q--) {
    size_t t;
    std::cin >> t;
    if (t == 0) {
      size_t i;
      m32 a, b;
      std::cin >> i >> a.extract() >> b.extract();
      seg.assign(i, { a, b });
    }
    else {
      size_t l, r;
      m32 x;
      std::cin >> l >> r >> x.extract();
      auto p = seg.fold(l, r);
      std::cout << p.first * x + p.second << '\n';
    }
  }
  return 0;
}
