
#include "../container/disjoint_sparse_table.cpp"

#include <cstddef>
#include <vector>
#include <cassert>

template <class SemiGroup>
class dst_tree {
public:
  using structure       = SemiGroup;
  using value_semigroup = typename SemiGroup::value_structure;
  using value_type      = typename SemiGroup::value_structure::type;
  using size_type       = size_t;

private:
  size_type M_size = 0, M_logn = 0;
  std::vector<disjoint_sparse_table<structure>> M_tree;

public:
  dst_tree() = default;
  template <class InputIterator>
  explicit dst_tree(InputIterator first, InputIterator last) { construct(first, last); }

  template <class InputIterator>
  void construct(InputIterator first, InputIterator last) {
    clear();
    M_size = std::distance(first, last);
    M_logn = bit_width(M_size);
    const size_type blocks = (M_size + M_logn - 1) / M_logn;
    M_tree.reserve(blocks + 1);
    std::vector<value_type> all;
    all.reserve(blocks);
    size_type cur = 0;
    while (cur != M_size) {
      const size_type len = std::min(M_size - cur, M_logn);
      auto right = first;
      std::advance(right, len);
      M_tree.emplace_back(first, right);
      all.push_back(M_tree.back().fold(0, len));
      cur += len;
      first = right;
    }
    M_tree.emplace_back(all.begin(), all.end());
  }

  value_type fold(const size_type first, size_type last) const {
    assert(first <= last);
    assert(last <= size());
    if (first == last--) return empty_exception<value_semigroup>();
    const size_type fsec = first / M_logn, lsec = last / M_logn;
    const size_type fidx = first - fsec * M_logn, lidx = last - lsec * M_logn;
    if (fsec == lsec) return M_tree[fsec].fold(fidx, lidx + 1);
    const value_type fres = M_tree[fsec].fold(fidx, M_logn);
    const value_type lres = M_tree[lsec].fold(0, lidx + 1);
    if (fsec + 1 == lsec) return value_semigroup::operation(fres, lres);
    const value_type mres = M_tree.back().fold(fsec + 1, lsec);
    return value_semigroup::operation(value_semigroup::operation(fres, mres), lres);
  }

  void clear() {
    M_tree.clear();
    M_tree.shrink_to_fit();
    M_size = M_logn = 0;
  }
  size_type size() const {
    return M_size;
  }
};

/**
 * @title DST Tree
 */