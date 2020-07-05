#pragma once

#include "../other/bit_operation.cpp"
#include <cstddef>
#include <vector>

template <class T>
class fenwick_tree {
public:
  using value_type = T;
  using size_type = size_t;

private:
  std::vector<value_type> M_tree;

public:
  fenwick_tree() = default;
  explicit fenwick_tree(size_type size) { initialize(size); }

  void initialize(size_type size) {
    M_tree.assign(size + 1, value_type{});
  }

  void add(size_type index, const value_type& x) {
    ++index;
    while (index <= size()) {
      M_tree[index] += x;
      index += least_significant_bit(index);
    }
  }

  value_type get(size_type index) const {
    ++index;
    value_type res{};
    while (index > 0) {
      res += M_tree[index];
      index -= least_significant_bit(index);
    }
    return res;
  }
  value_type fold(size_type l, size_type r) const {
    if (l == 0 && r == 0) return value_type{};
    if (l == 0) return get(r - 1);
    return get(r - 1) - get(l - 1);
  }

  size_type size() const {
    return M_tree.size() - 1;
  }

};

/**
 * @title Fenwick Tree
 */