
#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include "../other/fast_io.cpp"

int main() {
  size_t Q;
  cin.scan(Q);
  while (Q--) {
    uint64_t a, b;
    cin.scan(a, b);
    cout.println(a + b);
  }
}
