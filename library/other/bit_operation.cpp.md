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


# :heavy_check_mark: Bit Operations

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#795f3202b17cb6bc3d4b771d8c6c9eaf">other</a>
* <a href="{{ site.github.repository_url }}/blob/master/other/bit_operation.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-09 18:08:09+09:00




## Required by

* :warning: <a href="../algebraic/ntt.cpp.html">Number Theoretic Transform</a>
* :heavy_check_mark: <a href="../container/disjoint_sparse_table.cpp.html">Disjoint Sparse Table</a>
* :heavy_check_mark: <a href="../container/dst_tree.cpp.html">DST Tree</a>
* :heavy_check_mark: <a href="../container/dual_segment_tree.cpp.html">Dual Segment Tree</a>
* :heavy_check_mark: <a href="../container/fenwick_tree.cpp.html">Fenwick Tree</a>
* :heavy_check_mark: <a href="../container/lazy_propagation_segment_tree.cpp.html">Lazy Propagation Segment Tree</a>
* :heavy_check_mark: <a href="../container/segment_tree.cpp.html">Segment Tree</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/dst_tree.test.cpp.html">test/dst_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/dual_segment_tree.test.cpp.html">test/dual_segment_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/fenwick_tree.test.cpp.html">test/fenwick_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/lazy_propagation_segment_tree.test.cpp.html">test/lazy_propagation_segment_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/segment_tree.test.cpp.html">test/segment_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/vertex_set_path_sum.test.cpp.html">test/vertex_set_path_sum.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cstddef>
#include <cstdint>

constexpr size_t bit_ppc(const uint64_t x) { return __builtin_popcountll(x); }
constexpr size_t bit_ctzr(const uint64_t x) { return x == 0 ? 64 : __builtin_ctzll(x); }
constexpr size_t bit_ctzl(const uint64_t x) { return x == 0 ? 64 : __builtin_clzll(x); }
constexpr size_t bit_width(const uint64_t x) { return 64 - bit_ctzl(x); }
constexpr uint64_t bit_msb(const uint64_t x) { return x == 0 ? 0 : uint64_t(1) << (bit_width(x) - 1); }
constexpr uint64_t bit_lsb(const uint64_t x) { return x & (-x); }
constexpr uint64_t bit_cover(const uint64_t x) { return x == 0 ? 0 : bit_msb(2 * x - 1); }

constexpr uint64_t bit_rev(uint64_t x) {
  x = ((x >> 1) & 0x5555555555555555) | ((x & 0x5555555555555555) << 1);
  x = ((x >> 2) & 0x3333333333333333) | ((x & 0x3333333333333333) << 2);
  x = ((x >> 4) & 0x0F0F0F0F0F0F0F0F) | ((x & 0x0F0F0F0F0F0F0F0F) << 4);
  x = ((x >> 8) & 0x00FF00FF00FF00FF) | ((x & 0x00FF00FF00FF00FF) << 8);
  x = ((x >> 16) & 0x0000FFFF0000FFFF) | ((x & 0x0000FFFF0000FFFF) << 16);
  x = (x >> 32) | (x << 32);
  return x;
}

/**
 * @title Bit Operations
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "other/bit_operation.cpp"

#include <cstddef>
#include <cstdint>

constexpr size_t bit_ppc(const uint64_t x) { return __builtin_popcountll(x); }
constexpr size_t bit_ctzr(const uint64_t x) { return x == 0 ? 64 : __builtin_ctzll(x); }
constexpr size_t bit_ctzl(const uint64_t x) { return x == 0 ? 64 : __builtin_clzll(x); }
constexpr size_t bit_width(const uint64_t x) { return 64 - bit_ctzl(x); }
constexpr uint64_t bit_msb(const uint64_t x) { return x == 0 ? 0 : uint64_t(1) << (bit_width(x) - 1); }
constexpr uint64_t bit_lsb(const uint64_t x) { return x & (-x); }
constexpr uint64_t bit_cover(const uint64_t x) { return x == 0 ? 0 : bit_msb(2 * x - 1); }

constexpr uint64_t bit_rev(uint64_t x) {
  x = ((x >> 1) & 0x5555555555555555) | ((x & 0x5555555555555555) << 1);
  x = ((x >> 2) & 0x3333333333333333) | ((x & 0x3333333333333333) << 2);
  x = ((x >> 4) & 0x0F0F0F0F0F0F0F0F) | ((x & 0x0F0F0F0F0F0F0F0F) << 4);
  x = ((x >> 8) & 0x00FF00FF00FF00FF) | ((x & 0x00FF00FF00FF00FF) << 8);
  x = ((x >> 16) & 0x0000FFFF0000FFFF) | ((x & 0x0000FFFF0000FFFF) << 16);
  x = (x >> 32) | (x << 32);
  return x;
}

/**
 * @title Bit Operations
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

