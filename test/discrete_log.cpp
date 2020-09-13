
#define PROBLEM "https://judge.yosupo.jp/problem/discrete_logarithm_mod"

#include "../algebraic/modular.cpp"
#include "../algebraic/modular_operation.cpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

int main() {
  size_t Q;
  std::cin >> Q;
  while (Q--) {
    uint32_t x, y;
    std::cin >> x >> y >> runtime_mod::value();
    const auto ans = log(rmint32_t(x), rmint32_t(y));
    if (ans == runtime_mod::value()) {
      std::cout << "-1\n";
    }
    else {
      std::cout << ans << '\n';
    }
  }
  return 0;
}
