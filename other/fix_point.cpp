#pragma once

#include <utility>

template <class Func>
struct fix_point: private Func {
  explicit constexpr fix_point(Func &&func): Func(std::forward<Func>(func)) { }
  template <class... Args>
  constexpr decltype(auto) operator () (Args &&... args) const {
    return Func::operator()(*this, std::forward<Args>(args)...);
  }
};

template <class Func>
constexpr decltype(auto) make_fix_point(Func &&func) {
  return fix_point<Func>(std::forward<Func>(func));
}

/**
 * @title Lambda Recursion
 */