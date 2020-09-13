
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_A"

#include "../algebraic/fact_prime.cpp"

#include <cstdint>
#include <iostream>

int main() {
  uint32_t N;
  std::cin >> N;
  std::cout << N << ':';
  for (auto [p, e]: factorize(N)) {
    while (e--) {
      std::cout << ' ' << p;
    }
  }
  std::cout << '\n';
  return 0;
}
