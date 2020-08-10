#pragma once

#include <type_traits>
#include <iterator>
#include <utility>

template <class T>
class rev_impl {
public:
  using iterator = decltype(std::rbegin(std::declval<T>()));

private:
  const iterator M_begin;
  const iterator M_end;

public:
  constexpr rev_impl(T &&cont) noexcept: M_begin(std::rbegin(cont)), M_end(std::rend(cont)) { }
  constexpr iterator begin() const noexcept { return M_begin; }
  constexpr iterator end() const noexcept { return M_end; }

};

template <class T>
constexpr decltype(auto) rev(T &&cont) {
  return rev_impl<T>(std::forward<T>(cont));
}

/**
 * @title Reverser
 */