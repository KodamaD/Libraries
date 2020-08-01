
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../algebraic/ntt.cpp"

#include <iostream>
#include <vector>

using m32 = mint32_t<998244353>;

int main() {
  size_t N, M;
  std::cin >> N >> M;
  std::vector<m32> A(N), B(M);
  for (auto &x: A) {
    std::cin >> x.extract();
  }
  for (auto &x: B) {
    std::cin >> x.extract();
  }
  using ntt = number_theoretic_transform<m32>;
  auto C = ntt::convolve(A, B);
  for (size_t i = 0; i < C.size(); ++i) {
    std::cout << C[i];
    std::cout << (i + 1 == C.size() ? '\n' : ' ');
  }
  return 0;
}
