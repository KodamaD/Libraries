#pragma once

#include "../other/bit_operation.cpp"

#include <cstddef>
#include <vector>
#include <cassert>
#include <type_traits>

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
    M_tree.assign(size + 1, value_type { });
  }

  void add(size_type index, const value_type& x) {
    assert(index < size());
    ++index;
    while (index <= size()) {
      M_tree[index] += x;
      index += bit_lsb(index);
    }
  }

  template <size_type Indexed = 1>
  value_type get(size_type index) const {
    assert(index < size());
    index += Indexed;
    value_type res{ };
    while (index > 0) {
      res += M_tree[index];
      index -= bit_lsb(index);
    }
    return res;
  }
  value_type fold(size_type first, size_type last) const {
    assert(first <= last);
    assert(last <= size());
    value_type res{};
    while (first < last) {
      res += M_tree[last];
      last -= bit_lsb(last);
    }
    while (last < first) {
      res -= M_tree[first];
      first -= bit_lsb(first);
    }
    return res;
  }

  template <class Func>
  size_type satisfies(const size_type left, Func &&func) const {
    assert(left <= size());
    if (func(value_type { })) return left;
    value_type val = -get<0>(left);
    size_type res = 0;
    for (size_type cur = bit_cover(size() + 1) >> 1; cur > 0; cur >>= 1) {
      if ((res + cur <= left) || (res + cur <= size() && !func(val + M_tree[res + cur]))) {
        val += M_tree[res + cur];
        res += cur;
      }
    }
    return res + 1;
  }

  void clear() {
    M_tree.clear();
    M_tree.shrink_to_fit();
  }
  size_type size() const {
    return M_tree.size() - 1;
  }
};

/**
 * @title Fenwick Tree
 */