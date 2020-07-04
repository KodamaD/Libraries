
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../algebraic/ntt.cpp"
#include "../other/fast_io.cpp"

#include <vector>

fast_io::scanner cin;
fast_io::printer cout;

using m32 = modular<998244353>;

int main() {
  size_t N, M;
  cin.scan(N, M);
  std::vector<m32> A(N), B(M);
  for (auto &x: A) {
    cin.scan(x.extract());
  }
  for (auto &x: B) {
    cin.scan(x.extract());
  }
  using ntt = number_theoretic_transform<m32>;
  auto C = ntt::convolve(A, B);
  for (size_t i = 0; i < C.size(); ++i) {
    cout.print(C[i].get());
    cout.print(i + 1 == C.size() ? '\n' : ' ');
  }
  return 0;
}
