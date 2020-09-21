
#define PROBLEM "https://judge.yosupo.jp/problem/min_cost_b_flow"

#include "../graph/network_simplex.cpp"

#include <cstddef>
#include <cstdint>
#include <string>
#include <iostream>
#include <algorithm>

std::string to_str(__int128_t x) {
  if (x == 0) {
    return "0";
  }
  std::string s;
  bool neg = false;
  if (x < 0) {
    x = -x;
    neg = true;
  }
  while (x > 0) {
    s += '0' + x % 10;
    x /= 10;
  }
  if (neg) {
    s += '-';
  }
  std::reverse(s.begin(), s.end());
  return s;
}

int main() {
  size_t N, M;
  std::cin >> N >> M;
  network_simplex<int64_t, int64_t> net(N);
  for (size_t i = 0; i < N; ++i) {
    int64_t p;
    std::cin >> p;
    net.add_supply(i, p);
  }
  for (size_t i = 0; i < M; ++i) {
    size_t s, t;
    int64_t l, u, c;
    std::cin >> s >> t >> l >> u >> c;
    net.add_edge(s, t, l, u, c);
  }
  const auto ans = net.solve();
  if (ans.feasible) {
    std::cout << to_str(ans.calculate<__int128_t>()) << '\n';
    for (const auto p: ans.potentials) {
      std::cout << p << '\n';
    }
    for (const auto [f, c]: ans.edges) {
      std::cout << f << '\n';
    }
  }
  else {
    std::cout << "infeasible\n";
  }
  return 0;
}
