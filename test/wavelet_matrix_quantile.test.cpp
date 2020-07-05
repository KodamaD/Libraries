
#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include "../container/wavelet_matrix.cpp"

#include <cstddef>
#include <cstdint>
#include <vector>
#include <iostream>

int main() {
  size_t N, Q;
  std::cin >> N >> Q;
  std::vector<uint32_t> A(N);
  for (auto &x: A) {
    std::cin >> x;
  }
  wavelet_matrix<uint32_t, 30> matrix(A.begin(), A.end());
  while (Q--) {
    size_t l, r, k;
    std::cin >> l >> r >> k;
    std::cout << matrix.quantile(k, l, r) << '\n';
  }
  return 0;
}
