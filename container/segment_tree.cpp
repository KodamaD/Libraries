#pragma once

#include "../other/monoid.cpp"
#include <cstddef>
#include <vector>
#include <iterator>
#include <algorithm>

template <class Monoid>
class segment_tree {
public:
  using structure    = Monoid;
  using value_monoid = typename Monoid::value_structure;
  using value_type   = typename Monoid::value_structure::type;
  using size_type    = size_t;

private:
  using fixed_value_monoid = fixed_monoid<value_monoid>;
  using fixed_value_type   = typename fixed_value_monoid::type;

  std::vector<fixed_value_type> M_tree;

  void M_fix_change(const size_type index) {
    M_tree[index] = fixed_value_monoid::operation(M_tree[index << 1 | 0], M_tree[index << 1 | 1]);
  }

public:
  segment_tree() = default;
  explicit segment_tree(const size_type size) { initialize(size); }
  template <class InputIterator>
  explicit segment_tree(InputIterator first, InputIterator last) { construct(first, last); }

  void initialize(const size_type size) {
    clear();
    M_tree.assign(size << 1, fixed_value_monoid::identity());
  }

  template <class InputIterator>
  void construct(InputIterator first, InputIterator last) {
    clear();
    const size_type size = std::distance(first, last);
    M_tree.reserve(size << 1);
    M_tree.assign(size, fixed_value_monoid::identity());
    std::transform(first, last, std::back_inserter(M_tree), [&](const value_type &value) {
      return fixed_value_monoid::convert(value);
    });
    for (size_type index = size - 1; index != 0; --index) {
      M_fix_change(index);
    }
  }

  void assign(size_type index, const value_type &value) {
    index += size();
    M_tree[index] = fixed_value_monoid::convert(value);
    while (index != 1) {
      index >>= 1;
      M_fix_change(index);
    } 
  }

  value_type at(const size_type index) const { 
    return fixed_value_monoid::revert(M_tree[index + size()]);
  }

  value_type fold(size_type first, size_type last) const {
    first += size();
    last += size();
    fixed_value_type fold_l = fixed_value_monoid::identity();
    fixed_value_type fold_r = fixed_value_monoid::identity();
    while (first != last) {
      if (first & 1) {
        fold_l = fixed_value_monoid::operation(fold_l, M_tree[first]);
        ++first;
      }
      if (last & 1) {
        --last;
        fold_r = fixed_value_monoid::operation(M_tree[last], fold_r);      
      }
      first >>= 1;
      last  >>= 1;
    }
    return fixed_value_monoid::revert(fixed_value_monoid::operation(fold_l, fold_r));
  }

  void clear() {
    M_tree.clear();
    M_tree.shrink_to_fit();
  }

  size_type size() const { 
    return M_tree.size() >> 1;
  }

};

/**
 * @title Segment Tree
 */