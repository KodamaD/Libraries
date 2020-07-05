
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../algebraic/ntt_arbitrary.cpp"
#include "../algebraic/runtime_modular.cpp"

#include <iostream>
#include <vector>
#include <cstddef>
#include <cstdint>

struct modulus_type { static inline uint32_t value; };
using m32 = runtime_modular<modulus_type>;

int main() {
  modulus_type::value = 1000000007;
  size_t N, M;
  std::cin >> N >> M;
  std::vector<m32> A(N), B(M);
  for (auto &x: A) {
    std::cin >> x.extract();
  }
  for (auto &x: B) {
    std::cin >> x.extract();
  }
  auto C = convolve_arbitrary_mod(A, B);
  for (size_t i = 0; i < C.size(); ++i) {
    std::cout << C[i];
    std::cout << (i + 1 == C.size() ? '\n' : ' ');
  }
  return 0;
}
