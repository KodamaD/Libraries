
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/NTL_2_F"

#include "../algebraic/fft.cpp"

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <utility>
#include <cstdint>
#include <cstdlib>

int main() {
  std::string A, B;
  std::cin >> A >> B;
  bool negative = false;
  auto fix = [&](std::string &&S) -> std::vector<uint32_t> {
    if (S == "0") {
      std::cout << "0\n";
      std::exit(EXIT_SUCCESS);
    }
    std::reverse(S.begin(), S.end());
    if (S.back() == '-') {
      negative ^= 1;
      S.pop_back();
    }
    std::vector<uint32_t> res(S.size());
    std::transform(S.begin(), S.end(), res.begin(), [&](auto c) {
      return c - '0';
    });
    return res;
  };
  fast_fourier_transform<double> fft;
  auto C = fft.convolve(fix(std::move(A)), fix(std::move(B)));
  std::vector<char> ans;
  ans.reserve(C.size());
  uint32_t sum = 0;
  for (auto x: C) {
    sum += x;
    ans.push_back((sum % 10) + '0');
    sum /= 10;
  }
  while (sum > 0) {
    ans.push_back((sum % 10) + '0');
    sum /= 10;
  }
  if (negative) {
    ans.push_back('-');
  }
  std::reverse(ans.begin(), ans.end());
  for (auto x: ans) {
    std::cout << x;
  }
  std::cout << '\n';
  return 0;
}
