
/**
 * @title Template
 */

#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
#include <array>
#include <cassert>

#include "/Users/kodamankod/Desktop/cpp_programming/Library/other/range.cpp"

using i32 = std::int32_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using isize = std::ptrdiff_t;
using usize = std::size_t;

template <class T, T Div = 2>
constexpr T infty = std::numeric_limits<T>::max() / Div;

template <class T>
using Vec = std::vector<T>;

int main() {
  
  return 0;
}
