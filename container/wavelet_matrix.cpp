#pragma once

#include "../container/bit_vector.cpp"

#include <array>
#include <algorithm>

template <class T, size_t W>
class wavelet_matrix {
public:
  using value_type = T;
  using size_type = size_t;

  static constexpr size_type word_size = W;

private:
  size_type M_size;
  std::array<bit_vector, word_size> M_fid;
  std::array<size_type, word_size> M_zero;

public:
  wavelet_matrix() = default;
  template <class InputIterator>
  explicit wavelet_matrix(InputIterator first, InputIterator last) { construct(first, last); }

  template <class InputIterator>
  void construct(InputIterator first, InputIterator last) { 
    M_size = std::distance(first, last);
    std::vector<bool> bit(M_size);
    std::vector<value_type> current(first, last);
    std::vector<value_type> next(M_size);
    for (size_type k = word_size; k--;) {
      auto l = next.begin();
      auto r = next.rbegin();
      for (size_type i = 0; i < M_size; ++i) {
        bit[i] = current[i] >> k & 1;
        (bit[i] ? *(r++) : *(l++)) = current[i];
      }
      M_fid[k].construct(bit.begin(), bit.end());
      M_zero[k] = l - next.begin();
      std::reverse(next.rbegin(), r);
      current.swap(next);
    }
  }

  size_type rank(value_type value, size_type l, size_type r) const {
    for (size_type k = word_size; k--;) {
      bool p = value >> k & 1;
      l = M_fid[k].rank(p, l) + p * M_zero[k];
      r = M_fid[k].rank(p, r) + p * M_zero[k];
    }
    return r - l;
  }

  size_type select(value_type value, size_type index) const {
    std::array<size_type, word_size + 1> l, r;
    l[word_size] = 0;
    r[word_size] = M_size;
    for (size_type k = word_size; k--;) {
      bool p = value >> k & 1;
      l[k] = M_fid[k].rank(p, l[k + 1]) + p * M_zero[k];
      r[k] = M_fid[k].rank(p, r[k + 1]) + p * M_zero[k];
    }
    if (r[0] - l[0] <= index) {
      return M_size;
    }
    for (size_type k = 0; k < word_size; ++k) {
      bool p = value >> k & 1;
      index = M_fid[k].select(p, index, l[k + 1]) - l[k + 1];
    }
    return index;
  }

  value_type access(size_type index) const {
    value_type res = 0;
    for (size_type k = word_size; k--;) {
      bool p = M_fid[k].access(index);
      res |= value_type(p) << k;
      index = M_fid[k].rank(p, index) + p * M_zero[k];
    }
    return res;
  }

  value_type quantile(size_type index, size_type l, size_type r) const {
    value_type res = 0;
    for (size_type k = word_size; k--;) {
      size_type lc = M_fid[k].rank(1, l);
      size_type rc = M_fid[k].rank(1, r);
      size_type zc = (r - l) - (rc - lc);
      bool p = (index >= zc);
      res |= value_type(p) << k;
      if (p) {
        l = lc + M_zero[k];
        r = rc + M_zero[k];
        index -= zc;
      }
      else {
        l -= lc;
        r -= rc;
      }
    }
    return res;
  }

  size_type count(size_type l, size_type r, value_type value) const {
    size_type res = 0;
    for (size_type k = word_size; k--;) {
      size_type lc = M_fid[k].rank(1, l);
      size_type rc = M_fid[k].rank(1, r);
      if (value >> (k) & 1) {
        l = lc + M_zero[k];
        r = rc + M_zero[k];
      }
      else {
        l -= lc;
        r -= rc;
        res += (rc - lc);
      }
    }
    return res + (r - l);
  }
  size_type count(size_type l, size_type r, value_type lb, value_type ub) const {
    return count(l, r, lb) - count(l, r, ub);
  }

};

/**
 * @title Wavelet Matrix
 */