#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <iterator>
#include <cassert>

class bit_vector {
public:
  using size_type = size_t;
  using bit_type = uint64_t;
  using count_type = uint32_t;

private:
  size_type M_size;
  std::vector<bit_type> M_block;
  std::vector<count_type> M_accum;

public:
  bit_vector() = default;
  template <class InputIterator>
  explicit bit_vector(InputIterator first, InputIterator last) { construct(first, last); }

  template <class InputIterator>
  void construct(InputIterator first, InputIterator last) { 
    M_size = std::distance(first, last);
    size_type fixed_size = (M_size >> 6) + 1;
    M_block.assign(fixed_size, 0);
    M_accum.assign(fixed_size, 0);
    for (size_type i = 0; i < M_size; ++i) {
      M_block[i >> 6] |= (bit_type(*first) & 1) << (i & 63);
      ++first;
    }
    for (size_type i = 1; i < fixed_size; ++i) {
      M_accum[i] = M_accum[i - 1] + __builtin_popcountll(M_block[i - 1]);
    }
  }

  bool access(size_type idx) const {
    assert(idx < M_size);
    return M_block[idx >> 6] >> (idx & 63) & 1;
  }
  size_type rank(bool value, size_type idx) const {
    assert(idx <= M_size);
    bit_type mask = (bit_type(1) << (idx & 63)) - 1;
    size_type res = M_accum[idx >> 6] + __builtin_popcountll(M_block[idx >> 6] & mask);
    return value ? res : idx - res;
  }
  size_type select(bool value, size_type idx) const {
    if (idx >= rank(value, M_size)) {
      return M_size;
    }
    size_type ok = 0, ng = M_size;
    while (ng - ok > 1) {
      size_type md = (ok + ng) >> 1;
      (rank(value, md) <= idx ? ok : ng) = md;
    }
    return ok;
  }
  size_type select(bool value, size_type idx, size_type l) const {
    assert(l <= M_size);
    return select(value, idx + rank(value, l));
  }
};

/**
 * @title Succinct Bit Vector
 */