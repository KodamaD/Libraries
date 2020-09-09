#pragma once

#include "../other/monoid.cpp"

#include <cstddef>
#include <stack>
#include <cassert>

template <class SemiGroup>
class sliding_window_aggregation {
public:
  using structure       = SemiGroup;
  using value_semigroup = typename SemiGroup::value_structure;
  using value_type      = typename SemiGroup::value_structure::type;
  using size_type       = size_t;

private:
  class node_type {
  public:
    value_type value, sum;
    node_type(const value_type &value, const value_type &sum): value(value), sum(sum) { }
  };

  std::stack<node_type> M_front, M_back;

public:
  sliding_window_aggregation(): M_front(), M_back() { }

  value_type fold() const {
    if (empty()) return empty_exception<value_semigroup>();
    if (M_front.empty()) return M_back.top().sum;
    else if (M_back.empty()) return M_front.top().sum;
    return value_semigroup::operation(M_front.top().sum, M_back.top().sum);
  }

  void push(const value_type &x) {
    if (M_back.empty()) M_back.emplace(x, x);
    else {
      value_type tmp = value_semigroup::operation(M_back.top().sum, x);
      M_back.emplace(x, tmp);
    }
  }
  void pop() {
    assert(!empty());
    if (M_front.empty()) {
      M_front.emplace(M_back.top().value, M_back.top().value);
      M_back.pop();
      while (!M_back.empty()) {
        value_type tmp = value_semigroup::operation(M_back.top().value, M_front.top().sum);
        M_front.emplace(M_back.top().value, tmp);
        M_back.pop();
      }
    }
    M_front.pop();
  }

  size_type size() const {
    return M_front.size() + M_back.size();
  }
  bool empty() const {
    return M_front.empty() && M_back.empty();
  }
};

/**
 * @title Sliding Window Aggregation
 */