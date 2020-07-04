
#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

#include "../algebraic/number_theory.cpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

int main() {
  size_t Q;
  std::cin >> Q;
  while (Q--) {
    uint64_t A;
    std::cin >> A;
    auto ans = enumerate_factors(A, true);
    std::cout << ans.size();
    for (auto x: ans) {
      std::cout << ' ' << x;
    }
    std::cout << '\n';
  }
  return 0;
}
