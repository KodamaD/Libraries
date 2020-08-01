
#define PROBLEM "https://yukicoder.me/problems/no/888"

#include "../algebraic/fact_prime.cpp"

#include <cstdint>
#include <iostream>

int main() {
  uint64_t N;
  std::cin >> N;
  uint64_t ans = 0;
  for (auto x: enumerate_divisors(N, false)) {
    ans += x;
  }
  std::cout << ans << '\n';
  return 0;
}
