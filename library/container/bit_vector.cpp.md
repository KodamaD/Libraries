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


# :heavy_check_mark: Succinct Bit Vector

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5f0b6ebc4bea10285ba2b8a6ce78b863">container</a>
* <a href="{{ site.github.repository_url }}/blob/master/container/bit_vector.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-05 19:22:30+09:00




## Required by

* :heavy_check_mark: <a href="wavelet_matrix.cpp.html">Wavelet Matrix</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/wavelet_matrix_quantile.test.cpp.html">test/wavelet_matrix_quantile.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <iterator>

class bit_vector {
public:
  using size_type = size_t;
  using bit_type = uint64_t;
  using count_type = uint32_t;

private:
  static constexpr size_type S_block_size = 64;

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
    size_type fixed_size = M_size / S_block_size + 1;
    M_block.assign(fixed_size, 0);
    M_accum.assign(fixed_size, 0);
    for (size_type i = 0; i < M_size; ++i) {
      M_block[i / S_block_size] |= (bit_type(*first) & 1) << (i & (S_block_size - 1));
      ++first;
    }
    for (size_type i = 1; i < fixed_size; ++i) {
      M_accum[i] = M_accum[i - 1] + __builtin_popcountll(M_block[i - 1]);
    }
  }

  bool access(size_type idx) const {
    return M_block[idx / S_block_size] >> (idx & (S_block_size - 1)) & 1;
  }
  size_type rank(bool value, size_type idx) const {
    bit_type mask = (bit_type(1) << (idx & (S_block_size - 1))) - 1;
    size_type res = M_accum[idx / S_block_size] + __builtin_popcountll(M_block[idx / S_block_size] & mask);
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
    return select(value, idx + rank(value, l));
  }

};

/**
 * @title Succinct Bit Vector
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "container/bit_vector.cpp"

#include <cstddef>
#include <cstdint>
#include <vector>
#include <iterator>

class bit_vector {
public:
  using size_type = size_t;
  using bit_type = uint64_t;
  using count_type = uint32_t;

private:
  static constexpr size_type S_block_size = 64;

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
    size_type fixed_size = M_size / S_block_size + 1;
    M_block.assign(fixed_size, 0);
    M_accum.assign(fixed_size, 0);
    for (size_type i = 0; i < M_size; ++i) {
      M_block[i / S_block_size] |= (bit_type(*first) & 1) << (i & (S_block_size - 1));
      ++first;
    }
    for (size_type i = 1; i < fixed_size; ++i) {
      M_accum[i] = M_accum[i - 1] + __builtin_popcountll(M_block[i - 1]);
    }
  }

  bool access(size_type idx) const {
    return M_block[idx / S_block_size] >> (idx & (S_block_size - 1)) & 1;
  }
  size_type rank(bool value, size_type idx) const {
    bit_type mask = (bit_type(1) << (idx & (S_block_size - 1))) - 1;
    size_type res = M_accum[idx / S_block_size] + __builtin_popcountll(M_block[idx / S_block_size] & mask);
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
    return select(value, idx + rank(value, l));
  }

};

/**
 * @title Succinct Bit Vector
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

