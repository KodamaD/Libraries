
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../algebraic/ntt.cpp"
#include "../other/fast_io.cpp"

#include <iostream>
#include <vector>

fast_io::scanner cin;
fast_io::printer cout;

using m32 = modular<1000000007>;

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
  auto C = convolve_arbitrary_mod(A, B);
  for (size_t i = 0; i < C.size(); ++i) {
    std::cout << C[i];
    std::cout << (i + 1 == C.size() ? '\n' : ' ');
  }
  return 0;
}
