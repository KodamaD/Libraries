
#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
#include <array>

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
  using itr = int64_t;
  struct iterator {
    itr i;
    constexpr iterator(itr i_): i(i_) { }
    constexpr void operator ++ () { ++i; }
    constexpr itr operator * () const { return i; }
    constexpr bool operator != (iterator x) const { return i != x.i; }
  };
  const iterator l, r;
  constexpr range(itr l_, itr r_): l(l_), r(std::max(l_, r_)) { }
  constexpr iterator begin() const { return l; }
  constexpr iterator end() const { return r; }
};

struct revrange {
  using itr = int64_t;
  struct iterator {
    itr i;
    constexpr iterator(itr i_): i(i_) { }
    constexpr void operator ++ () { --i; }
    constexpr itr operator * () const { return i; }
    constexpr bool operator != (iterator x) const { return i != x.i; }
  };
  const iterator l, r;
  constexpr revrange(itr l_, itr r_): l(l_ - 1), r(std::max(l_, r_) - 1) { }
  constexpr iterator begin() const { return r; }
  constexpr iterator end() const { return l; }
};

using i32 = int32_t;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;

constexpr i32 inf32 = (i32(1) << 30) - 1;
constexpr i64 inf64 = (i64(1) << 62) - 1;

int main() {
  
  return 0;
}
