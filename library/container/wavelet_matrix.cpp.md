---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: Wavelet Matrix

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5f0b6ebc4bea10285ba2b8a6ce78b863">container</a>
* <a href="{{ site.github.repository_url }}/blob/master/container/wavelet_matrix.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-09 18:08:09+09:00




## Depends on

* :heavy_check_mark: <a href="bit_vector.cpp.html">Succinct Bit Vector</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/wavelet_matrix_quantile.test.cpp.html">test/wavelet_matrix_quantile.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "../container/bit_vector.cpp"

#include <array>
#include <algorithm>
#include <cassert>

template <class T, size_t W>
class wavelet_matrix {
public:
  using value_type = T;
  using size_type = size_t;

private:
  size_type M_size;
  std::array<bit_vector, W> M_fid;
  std::array<size_type, W> M_zero;

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
    for (size_type k = W; k--;) {
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
    assert(l <= r);
    assert(r <= M_size);
    for (size_type k = W; k--;) {
      bool p = value >> k & 1;
      l = M_fid[k].rank(p, l) + p * M_zero[k];
      r = M_fid[k].rank(p, r) + p * M_zero[k];
    }
    return r - l;
  }

  size_type select(value_type value, size_type index) const {
    std::array<size_type, W + 1> l, r;
    l[W] = 0;
    r[W] = M_size;
    for (size_type k = W; k--;) {
      bool p = value >> k & 1;
      l[k] = M_fid[k].rank(p, l[k + 1]) + p * M_zero[k];
      r[k] = M_fid[k].rank(p, r[k + 1]) + p * M_zero[k];
    }
    if (r[0] - l[0] <= index) {
      return M_size;
    }
    for (size_type k = 0; k < W; ++k) {
      bool p = value >> k & 1;
      index = M_fid[k].select(p, index, l[k + 1]) - l[k + 1];
    }
    return index;
  }

  value_type access(size_type index) const {
    assert(index < M_size);
    value_type res = 0;
    for (size_type k = W; k--;) {
      bool p = M_fid[k].access(index);
      res |= value_type(p) << k;
      index = M_fid[k].rank(p, index) + p * M_zero[k];
    }
    return res;
  }

  value_type quantile(size_type index, size_type l, size_type r) const {
    assert(l <= r);
    assert(r <= M_size);
    value_type res = 0;
    for (size_type k = W; k--;) {
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
    assert(l <= r);
    assert(r <= M_size);
    size_type res = 0;
    for (size_type k = W; k--;) {
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
    assert(l <= r);
    assert(r <= M_size);
    return count(l, r, lb) - count(l, r, ub);
  }
};

/**
 * @title Wavelet Matrix
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "container/wavelet_matrix.cpp"

#line 2 "container/bit_vector.cpp"

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
#line 4 "container/wavelet_matrix.cpp"

#include <array>
#include <algorithm>
#line 8 "container/wavelet_matrix.cpp"

template <class T, size_t W>
class wavelet_matrix {
public:
  using value_type = T;
  using size_type = size_t;

private:
  size_type M_size;
  std::array<bit_vector, W> M_fid;
  std::array<size_type, W> M_zero;

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
    for (size_type k = W; k--;) {
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
    assert(l <= r);
    assert(r <= M_size);
    for (size_type k = W; k--;) {
      bool p = value >> k & 1;
      l = M_fid[k].rank(p, l) + p * M_zero[k];
      r = M_fid[k].rank(p, r) + p * M_zero[k];
    }
    return r - l;
  }

  size_type select(value_type value, size_type index) const {
    std::array<size_type, W + 1> l, r;
    l[W] = 0;
    r[W] = M_size;
    for (size_type k = W; k--;) {
      bool p = value >> k & 1;
      l[k] = M_fid[k].rank(p, l[k + 1]) + p * M_zero[k];
      r[k] = M_fid[k].rank(p, r[k + 1]) + p * M_zero[k];
    }
    if (r[0] - l[0] <= index) {
      return M_size;
    }
    for (size_type k = 0; k < W; ++k) {
      bool p = value >> k & 1;
      index = M_fid[k].select(p, index, l[k + 1]) - l[k + 1];
    }
    return index;
  }

  value_type access(size_type index) const {
    assert(index < M_size);
    value_type res = 0;
    for (size_type k = W; k--;) {
      bool p = M_fid[k].access(index);
      res |= value_type(p) << k;
      index = M_fid[k].rank(p, index) + p * M_zero[k];
    }
    return res;
  }

  value_type quantile(size_type index, size_type l, size_type r) const {
    assert(l <= r);
    assert(r <= M_size);
    value_type res = 0;
    for (size_type k = W; k--;) {
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
    assert(l <= r);
    assert(r <= M_size);
    size_type res = 0;
    for (size_type k = W; k--;) {
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
    assert(l <= r);
    assert(r <= M_size);
    return count(l, r, lb) - count(l, r, ub);
  }
};

/**
 * @title Wavelet Matrix
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

