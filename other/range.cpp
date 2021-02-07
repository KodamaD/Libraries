#pragma once

#include <algorithm>

class range {
  struct iter {
    std::size_t itr;
    constexpr iter(std::size_t pos) noexcept: itr(pos) { }
    constexpr void operator ++ () noexcept { ++itr; }
    constexpr bool operator != (iter other) const noexcept { return itr != other.itr; }
    constexpr std::size_t operator * () const noexcept { return itr; }
  };

  struct reviter {
    std::size_t itr;
    constexpr reviter(std::size_t pos) noexcept: itr(pos) { }
    constexpr void operator ++ () noexcept { --itr; }
    constexpr bool operator != (reviter other) const noexcept { return itr != other.itr; }
    constexpr std::size_t operator * () const noexcept { return itr; }
  };

  const iter first, last;

public:
  constexpr range(std::size_t first, std::size_t last) noexcept: first(first), last(std::max(first, last)) { }
  constexpr iter begin() const noexcept { return first; }
  constexpr iter end() const noexcept { return last; }
  constexpr reviter rbegin() const noexcept { return reviter(*last - 1); } 
  constexpr reviter rend() const noexcept { return reviter(*first - 1); } 
};

/**
 * @title Range
 */