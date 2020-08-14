
#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"

#include "../algebraic/modular.cpp"
#include "../algebraic/modular_operation.cpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

int main() {
  size_t Q;
  std::cin >> Q;
  while (Q--) {
    uint32_t x;
    std::cin >> x >> runtime_mod::value();
    if (x == 0) std::cout << "0\n";
    else {
      const auto ans = sqrt(rmint32_t(x));
      if (ans.zero()) std::cout << "-1\n";
      else std::cout << ans << '\n';
    }
  }
  return 0;
}
