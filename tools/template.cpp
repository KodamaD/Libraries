
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <numeric>

template <class T, class U>
inline bool chmin(T &lhs, const U &rhs) {
  if (lhs > rhs) { lhs = rhs; return true; }
  return false;
}

template <class T, class U>
inline bool chmax(T &lhs, const U &rhs) {
  if (lhs < rhs) { lhs = rhs; return true; }
  return false;
}

struct range {
  using int_ = int_fast64_t;
  struct itr {
    int_ i;
    constexpr itr(int_ i_): i(i_) { }
    constexpr void operator ++ () { ++i; }
    constexpr int_ operator * () const { return i; }
    constexpr bool operator != (itr x) const { return i != x.i; }
  };
  const itr l, r;
  constexpr range(int_ l_, int_ r_): l(l_), r(std::max(l_, r_)) { }
  constexpr itr begin() const { return l; }
  constexpr itr end() const { return r; }
};

struct revrange {
  using int_ = int_fast64_t;
  struct itr {
    int_ i;
    constexpr itr(int_ i_): i(i_) { }
    constexpr void operator ++ () { --i; }
    constexpr int_ operator * () const { return i; }
    constexpr bool operator != (itr x) const { return i != x.i; }
  };
  const itr l, r;
  constexpr revrange(int_ l_, int_ r_): l(l_ - 1), r(std::max(l_, r_) - 1) { }
  constexpr itr begin() const { return r; }
  constexpr itr end() const { return l; }
};

using i32 = int_fast32_t;
using i64 = int_fast64_t;
using u32 = uint_fast32_t;
using u64 = uint_fast64_t;

constexpr i32 inf32 = (i32(1) << 30) - 1;
constexpr i64 inf64 = (i64(1) << 62) - 1;

int main() {

  return 0;
}
