
#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include "../container/dst_tree.cpp"

#include <iostream>
#include <cstddef>
#include <vector>

struct semigroup {
  struct value_structure {
    using type = int32_t;
    static constexpr type operation(const type& v1, const type& v2) { 
      return v1 < v2 ? v1 : v2;
    }
  };
};

int main() {
  size_t N, Q;
  std::cin >> N >> Q;
  std::vector<int32_t> A(N);
  for (auto &x: A) {
    std::cin >> x;
  }
  dst_tree<semigroup> dst(A.begin(), A.end());
  while (Q--) {
    size_t l, r;
    std::cin >> l >> r;
    std::cout << dst.fold(l, r) << '\n';
  }
  return 0;
}
