
#define PROBLEM "https://judge.yosupo.jp/problem/discrete_logarithm_mod"

#include "../algebraic/modular.cpp"
#include "../algebraic/mod_log.cpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

int main() {
  size_t Q;
  std::cin >> Q;
  while (Q--) {
    uint32_t x, y;
    std::cin >> x >> y >> dynamic_modulus<>::mod();
    const auto ans = log(rmint32_t(x), rmint32_t(y));
    if (ans == dynamic_modulus<>::mod()) {
      std::cout << "-1\n";
    }
    else {
      std::cout << ans << '\n';
    }
  }
  return 0;
}
