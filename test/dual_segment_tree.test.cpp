
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_D"

#include "../container/dual_segment_tree.cpp"

#include <cstddef>
#include <cstdint>
#include <vector>
#include <iostream>

struct dst_monoid {
  struct value_structure {
    using type = uint32_t;
  };
  struct operator_structure {
    using type = uint32_t;
    static type operation(const type&, const type &v2) {
      return v2;
    }
  };
  static typename value_structure::type operation(
    const typename value_structure::type    &,
    const typename operator_structure::type &op) {
    return op;
  }
};

int main() {
  size_t N, Q;
  std::cin >> N >> Q;
  dual_segment_tree<dst_monoid> seg;
  {
    std::vector<uint32_t> build(N, (uint32_t(1) << 31) - 1);
    seg.construct(build.begin(), build.end());
  }
  while (Q--) {
    size_t type;
    std::cin >> type;
    if (type == 0) {
      size_t s, t;
      std::cin >> s >> t;
      uint32_t x;
      std::cin >> x;
      seg.operate(s, t + 1, x);
    }
    else {
      size_t i;
      std::cin >> i;
      std::cout << seg.at(i) << '\n';
    }
  }
  return 0;
}
