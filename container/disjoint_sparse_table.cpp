#pragma once

#include "../other/bit_operation.cpp"
#include "../other/monoid.cpp"

#include <cstddef>
#include <vector>

template <class SemiGroup>
class disjoint_sparse_table {
public:
  using structure       = SemiGroup;
  using value_semigroup = typename SemiGroup::value_structure;
  using value_type      = typename SemiGroup::value_structure::type;
  using size_type       = size_t;

private:

  std::vector<std::vector<value_type>> M_table;

public:
  disjoint_sparse_table() = default;
  template <class InputIterator>
  explicit disjoint_sparse_table(InputIterator first, InputIterator last) { construct(first, last); }

  template <class InputIterator>
  void construct(InputIterator first, InputIterator last) {
    clear();
    const size_type size = std::distance(first, last);
    const size_type height = bit_width(size);
    M_table.resize(height, std::vector<value_type>(size));
    M_table.front() = std::vector<value_type>(first, last);
    for (size_type story = 1; story < height; ++story) {
      const size_type bit = (1 << story);
      for (size_type left = 0; left < size; left += (bit << 1)) {
        const size_type mid = (left + bit < size ? left + bit : size);
        M_table[story][mid - 1] = M_table[0][mid - 1];
        for (size_type i = mid - 1; i-- != left;) {
          M_table[story][i] = value_semigroup::operation(M_table[0][i], M_table[story][i + 1]);
        }
        if (mid >= size) continue;
        const size_type right = (mid + bit < size ? mid + bit : size);
        M_table[story][mid] = M_table[0][mid];
        for (size_type i = mid + 1; i != right; ++i) {
          M_table[story][i] = value_semigroup::operation(M_table[story][i - 1], M_table[0][i]);
        }
      }
    }
  }

  value_type fold(const size_type first, size_type last) const {
    if (first == last) return empty_exception<value_semigroup>();
    if (first == --last) return M_table[0][first];
    const size_type height = bit_width(first ^ last) - 1;
    return value_semigroup::operation(M_table[height][first], M_table[height][last]);
  }

  void clear() {
    M_table.clear();
    M_table.shrink_to_fit();
  }
  size_type size() const {
    if (M_table.empty()) return 0;
    return M_table.front().size();
  }
  bool empty() const {
    return M_table.empty();
  }

};

/**
 * @title Disjoint Sparse Table
 */