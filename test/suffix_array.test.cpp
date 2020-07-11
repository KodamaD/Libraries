
#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include "../string/suffix_array.cpp"

#include <cstddef>
#include <iostream>
#include <string>

int main() {  
  std::string S;
  std::cin >> S;
  suffix_array<char> ans(S.begin(), S.end());
  for (size_t i = 1; i <= S.size(); ++i) {
    std::cout << ans[i] << " \n"[i == S.size()];
  }
  return 0;
}
