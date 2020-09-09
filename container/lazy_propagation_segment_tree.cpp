#pragma once

#include "../other/bit_operation.cpp"
#include "../other/monoid.cpp"

#include <cstddef>
#include <vector>
#include <iterator>
#include <algorithm>

template <class CombinedMonoid>
class lazy_propagation_segment_tree {
public:
  using structure       = CombinedMonoid;
  using value_monoid    = typename CombinedMonoid::value_structure;
  using operator_monoid = typename CombinedMonoid::operator_structure;
  using value_type      = typename CombinedMonoid::value_structure::type;
  using operator_type   = typename CombinedMonoid::operator_structure::type;
  using size_type       = size_t;

private:
  using fixed_operator_monoid = fixed_monoid<operator_monoid>;
  using fixed_operator_type   = typename fixed_operator_monoid::type;

  class node_type {
  public:
    value_type    value;
    fixed_operator_type lazy;
    node_type(
      const value_type    &value = value_monoid::identity(),
      const fixed_operator_type &lazy = fixed_operator_monoid::identity()
    ): value(value), lazy(lazy) { }
  };

  static void S_apply(node_type &node, const fixed_operator_type &op, const size_type length) {
    fixed_operator_monoid::operate(structure::operation, node.value, op, length);
    node.lazy = fixed_operator_monoid::operation(node.lazy, op);
  }

  void M_propagate(const size_type index, const size_type length) {
    S_apply(M_tree[index << 1 | 0], M_tree[index].lazy, length);
    S_apply(M_tree[index << 1 | 1], M_tree[index].lazy, length);
    M_tree[index].lazy = fixed_operator_monoid::identity();
  }
  void M_fix_change(const size_type index) {
    M_tree[index].value = 
      value_monoid::operation(M_tree[index << 1 | 0].value, M_tree[index << 1 | 1].value);
  }

  void M_pushdown(const size_type index) {
    const size_type lsb = bit_ctzr(index);
    for (size_type story = bit_width(index); story != lsb; --story) {
      M_propagate(index >> story, 1 << (story - 1));
    }
  }
  void M_pullup(size_type index) {
    index >>= bit_ctzr(index);
    while (index != 1) {
      index >>= 1;
      M_fix_change(index);
    }
  }

  std::vector<node_type> M_tree;

public:
  lazy_propagation_segment_tree() = default;
  explicit lazy_propagation_segment_tree(const size_type size) { initialize(size); }
  template <class InputIterator>
  explicit lazy_propagation_segment_tree(InputIterator first, InputIterator last) { construct(first, last); }

  void initialize(const size_type size) {
    clear();
    M_tree.assign(size << 1, node_type());
  }

  template <class InputIterator>
  void construct(InputIterator first, InputIterator last) {
    clear();
    const size_type size = std::distance(first, last);
    M_tree.reserve(size << 1);
    M_tree.assign(size, node_type());
    for (; first != last; ++first) {
      M_tree.emplace_back(*first, fixed_operator_monoid::identity());
    }
    for (size_type index = size - 1; index != 0; --index) {
      M_fix_change(index);
    }
  }

  value_type fold(size_type first, size_type last) {
    first += size();
    last  += size();
    M_pushdown(first);
    M_pushdown(last);
    value_type fold_l = value_monoid::identity();
    value_type fold_r = value_monoid::identity();
    while (first != last) {
      if (first & 1) {
        fold_l = value_monoid::operation(fold_l, M_tree[first].value);
        ++first;
      }
      if (last & 1) {
        --last;
        fold_r = value_monoid::operation(M_tree[last].value, fold_r);
      }
      first >>= 1;
      last  >>= 1;
    }
    return value_monoid::operation(fold_l, fold_r);
  }

  void operate(size_type first, size_type last, const operator_type &op_) {
    const auto op = fixed_operator_monoid::convert(op_);
    first += size();
    last  += size();
    M_pushdown(first);
    M_pushdown(last);
    const size_type first_c = first;
    const size_type last_c  = last;
    for (size_type story = 0; first != last; ++story) {
      if (first & 1) {
        S_apply(M_tree[first], op, 1 << story);
        ++first;
      }
      if (last & 1) {
        --last;
        S_apply(M_tree[last], op, 1 << story);
      }
      first >>= 1;
      last  >>= 1;
    }
    M_pullup(first_c);
    M_pullup(last_c);
  }

  void assign(size_type index, const value_type &val) {
    index += size();
    for (size_type story = bit_width(index); story != 0; --story) {
      M_propagate(index >> story, 1 << (story - 1));
    }
    M_tree[index].value = val;
    M_tree[index].lazy  = fixed_operator_monoid::identity();
    while (index != 1) {
      index >>= 1;
      M_fix_change(index);
    }
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
 * @title Lazy Propagation Segment Tree
 */