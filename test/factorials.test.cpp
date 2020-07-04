
#define PROBLEM "https://yukicoder.me/problems/no/117"

#include "../algebraic/factorials.cpp"
#include "../algebraic/modular.cpp"

#include <cstddef>
#include <iostream>

using m32 = modular<1000000007>;
factorials<m32, 2000000> fact;

m32 comb(size_t N, size_t K) {
  if (N < K) return m32(0);
  return fact(N, K);
}

m32 perm(size_t N, size_t K) {
  if (N < K) return m32(0);
  return fact.fact[N] * fact.fact_inv[N - K];
}

m32 homo(size_t N, size_t K) {
  if (N == 0 && K == 0) return m32(1);
  if (N == 0) return m32(0);
  return fact(N + K - 1, K);
}

int main() {
  size_t T;
  std::cin >> T;
  while (T--) {
    char type, dust;
    size_t N, K;
    std::cin >> type >> dust >> N >> dust >> K >> dust;
    if (type == 'C') std::cout << comb(N, K) << '\n';
    if (type == 'P') std::cout << perm(N, K) << '\n';
    if (type == 'H') std::cout << homo(N, K) << '\n';
  }
}
