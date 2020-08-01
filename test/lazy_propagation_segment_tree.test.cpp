
#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include "../container/lazy_propagation_segment_tree.cpp"
#include "../algebraic/modular.cpp"

#include <utility>
#include <iostream>
#include <cstddef>
#include <vector>

using m32 = mint32_t<998244353>;

struct lst_monoid {
  struct value_structure {
    using type = m32;
    static type identity() { return m32(0); }
    static type operation(const type& v1, const type& v2) { 
      return v1 + v2;
    }
  };
  struct operator_structure {
    using type = std::pair<m32, m32>;
    static type identity() { return { m32(1), m32(0) }; }
    static type operation(const type& v1, const type& v2) { 
      return { v2.first * v1.first, v2.first * v1.second + v2.second };
    }
  };
  static typename value_structure::type operation(
    const typename value_structure::type    &val,
    const typename operator_structure::type &op,
    const size_t length = 1) {
    return op.first * val + op.second * m32(length);
  }
};

int main() {
  size_t N, Q;
  std::cin >> N >> Q;
  std::vector<m32> A(N);
  for (auto &x: A) {
    std::cin >> x.extract();
  }
  lazy_propagation_segment_tree<lst_monoid> seg(A.begin(), A.end());
  while (Q--) {
    size_t t;
    std::cin >> t;
    if (t == 0) {
      size_t l, r;
      m32 b, c;
      std::cin >> l >> r >> b.extract() >> c.extract();
      seg.operate(l, r, { b, c });
    }
    else {
      size_t l, r;
      std::cin >> l >> r;
      std::cout << seg.fold(l, r).get() << '\n';
    }
  }
  return 0;
}
