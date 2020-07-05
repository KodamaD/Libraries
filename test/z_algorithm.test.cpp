
#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../string/z_algorithm.cpp"

#include <cstddef>
#include <vector>
#include <string>
#include <iostream>

int main() {
  std::string S;
  std::cin >> S;
  auto ans = z_algorithm(S.begin(), S.end());
  for (size_t i = 0; i < S.size(); ++i) {
    std::cout << ans[i];
    std::cout << (i + 1 == S.size() ? '\n' : ' ');
  }
  return 0;
}