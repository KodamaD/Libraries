
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
    class type {
      using base_type  = uint32_t;
      using usage_type = bool;
    public:
      base_type  value;
      usage_type available; 
      explicit type(): value(base_type{}), available(false) { }
      type(const base_type& value): value(value), available(true) { }
      operator base_type() const { return value; }
    };
    static type identity() { return type(); }
    static type operation(const type& v1, const type& v2) { 
      if (!v1.available) return v2;
      if (!v2.available) return v1;
      return v2;
    }
  };
  static typename value_structure::type operation(
    const typename value_structure::type    &val,
    const typename operator_structure::type &op) {
    if (!op.available) return val;
    return op.value;
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
