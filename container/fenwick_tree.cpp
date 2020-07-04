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
    node.assign(size + 1, 0);
  }

  void add(size_type index, const value_type& x) {
    ++index;
    while (index <= size()) {
      node[index] += x;
      index += least_significant_bit(index);
    }
  }

  value_type get(size_type index) const {
    ++index;
    value_type res = 0;
    while (index > 0) {
      res += node[index];
      index -= least_significant_bit(index);
    }
    return res;
  }
  value_type fold(size_type index l, size_type index r) const {
    return get(r - 1) - get(l - 1);
  }

  size_type size() const {
    return M_tree.size() - 1;
  }

};
