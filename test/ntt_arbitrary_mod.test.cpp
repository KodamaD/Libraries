
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../algebraic/ntt_arbitrary.cpp"
#include "../algebraic/modular.cpp"
#include "../algebraic/runtime_modular.cpp"

#include <iostream>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <cstdlib>

namespace test1 {

using m32 = modular<1000000007>;

std::vector<uint32_t> run(const std::vector<uint32_t> &A_, const std::vector<uint32_t> &B_) {
  std::vector<m32> A, B;
  A.reserve(A_.size());
  B.reserve(B_.size());
  for (auto x: A_) {
    A.emplace_back(x);
  }
  for (auto x: B_) {
    B.emplace_back(x);
  }
  auto C = convolve_arbitrary_mod(A, B);
  std::vector<uint32_t> res;
  res.reserve(C.size());
  for (auto x: C) {
    res.push_back(x.get());
  }
  return res;
}

};

namespace test2 {

struct modulus_type { static inline uint32_t value; };
using m32 = runtime_modular<modulus_type>;

std::vector<uint32_t> run(const std::vector<uint32_t> &A_, const std::vector<uint32_t> &B_) {
  modulus_type::value = 1000000007;
  std::vector<m32> A, B;
  A.reserve(A_.size());
  B.reserve(B_.size());
  for (auto x: A_) {
    A.emplace_back(x);
  }
  for (auto x: B_) {
    B.emplace_back(x);
  }
  auto C = convolve_arbitrary_mod(A, B);
  std::vector<uint32_t> res;
  res.reserve(C.size());
  for (auto x: C) {
    res.push_back(x.get());
  }
  return res;
}

};

int main() {
  size_t N, M;
  std::cin >> N >> M;
  std::vector<uint32_t> A(N), B(M);
  for (auto &x: A) {
    std::cin >> x;
  }
  for (auto &x: B) {
    std::cin >> x;
  }
  auto C1 = test1::run(A, B);
  auto C2 = test2::run(A, B);
  if (C1 != C2) {
    std::exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < C1.size(); ++i) {
    std::cout << C1[i];
    std::cout << (i + 1 == C1.size() ? '\n' : ' ');
  }
}
