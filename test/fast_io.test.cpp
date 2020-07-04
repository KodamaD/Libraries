
#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include "../other/fast_io.cpp"

#include <cstddef>
#include <cstdint>

fast_io::scanner cin;
fast_io::printer cout;

int main() {
  size_t Q;
  cin.scan(Q);
  while (Q--) {
    uint64_t a, b;
    cin.scan(a, b);
    cout.println(a + b);
  }
}
