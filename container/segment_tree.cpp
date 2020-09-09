#pragma once

#include "../other/monoid.cpp"
#include "../other/bit_operation.cpp"

#include <cstddef>
#include <vector>
#include <iterator>
#include <algorithm>
#include <utility>
#include <type_traits>
#include <cassert>

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
    assert(index < size());
    index += size();
    M_tree[index] = fixed_value_monoid::convert(value);
    while (index != 1) {
      index >>= 1;
      M_fix_change(index);
    } 
  }

  value_type at(const size_type index) const { 
    assert(index < size());
    return fixed_value_monoid::revert(M_tree[index + size()]);
  }

  value_type fold(size_type first, size_type last) const {
    assert(first <= last);
    assert(last <= size());
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
      last >>= 1;
    }
    return fixed_value_monoid::revert(fixed_value_monoid::operation(fold_l, fold_r));
  }

  template <bool ToRight = true, class Constraint, std::enable_if_t<ToRight>* = nullptr> 
  size_type satisfies(const size_type left, Constraint &&func) const {
    assert(left <= size());
    if (fixed_value_monoid::satisfies(std::forward<Constraint>(func), 
      fixed_value_monoid::identity())) return left;
    size_type first = left + size();
    size_type last = 2 * size();
    const size_type last_c = last;
    fixed_value_type fold = fixed_value_monoid::identity();
    const auto try_merge = [&](const size_type index) {
      fixed_value_type tmp = fixed_value_monoid::operation(fold, M_tree[index]);
      if (fixed_value_monoid::satisfies(std::forward<Constraint>(func), tmp)) return true;
      fold = std::move(tmp);
      return false;
    };
    const auto subtree = [&](size_type index) {
      while (index < size()) {
        index <<= 1;
        if (!try_merge(index)) ++index;
      }
      return index - size() + 1;
    };
    size_type story = 0;
    while (first < last) {
      if (first & 1) {
        if (try_merge(first)) return subtree(first);
        ++first;
      }
      first >>= 1;
      last >>= 1;
      ++story;
    }
    while (story--) {
      last = last_c >> story;
      if (last & 1) {
        --last;
        if (try_merge(last)) return subtree(last);
      }
    }
    return size() + 1;
  }

  template <bool ToRight = true, class Constraint, std::enable_if_t<!ToRight>* = nullptr> 
  size_type satisfies(const size_type right, Constraint &&func) const {
    assert(right <= size());
    if (fixed_value_monoid::satisfies(std::forward<Constraint>(func), 
      fixed_value_monoid::identity())) return right;
    size_type first = size();
    size_type last = right + size();
    const size_type first_c = first;
    fixed_value_type fold = fixed_value_monoid::identity();
    const auto try_merge = [&](const size_type index) {
      fixed_value_type tmp = fixed_value_monoid::operation(M_tree[index], fold);
      if (fixed_value_monoid::satisfies(std::forward<Constraint>(func), tmp)) return true;
      fold = std::move(tmp);
      return false;
    };
    const auto subtree = [&](size_type index) {
      while (index < size()) {
        index <<= 1;
        if (try_merge(index + 1)) ++index;
      }
      return index - size();
    };
    size_type story = 0;
    while (first < last) {
      if (first & 1) ++first;
      if (last & 1) {
        --last;
        if (try_merge(last)) return subtree(last);
      }
      first >>= 1;
      last >>= 1;
      ++story;
    }
    const size_type cover = bit_cover(first_c);
    while (story--) {
      first = (cover >> story) - ((cover - first_c) >> story);
      if (first & 1) {
        if (try_merge(first)) return subtree(first);
      }
    }
    return size_type(-1);
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