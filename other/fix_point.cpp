#pragma once

#include <utility>

template <class Func>
struct fix_point_impl: private Func {
  explicit constexpr fix_point_impl(Func &&func): Func(std::forward<Func>(func)) { }
  template <class... Args>
  constexpr decltype(auto) operator () (Args &&... args) const {
    return Func::operator()(*this, std::forward<Args>(args)...);
  }
};

template <class Func>
constexpr decltype(auto) fix_point(Func &&func) {
  return fix_point_impl<Func>(std::forward<Func>(func));
}

/**
 * @title Lambda Recursion
 */