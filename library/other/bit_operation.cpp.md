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
    - Last commit date: 2020-07-12 13:43:20+09:00




## Required by

* :heavy_check_mark: <a href="../algebraic/fft.cpp.html">Fast Fourier Transform</a>
* :heavy_check_mark: <a href="../algebraic/ntt.cpp.html">Number Theoretic Transform</a>
* :heavy_check_mark: <a href="../algebraic/ntt_arbitrary.cpp.html">Number Theoretic Transform (arbitrary mod)</a>
* :heavy_check_mark: <a href="../container/dual_segment_tree.cpp.html">Dual Segment Tree</a>
* :heavy_check_mark: <a href="../container/fenwick_tree.cpp.html">Fenwick Tree</a>
* :heavy_check_mark: <a href="../container/lazy_propagation_segment_tree.cpp.html">Lazy Propagation Segment Tree</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/dual_segment_tree.test.cpp.html">test/dual_segment_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/fenwick_tree.test.cpp.html">test/fenwick_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/fft.test.cpp.html">test/fft.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/lazy_propagation_segment_tree.test.cpp.html">test/lazy_propagation_segment_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/ntt.test.cpp.html">test/ntt.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/ntt_arbitrary_mod.test.cpp.html">test/ntt_arbitrary_mod.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/ntt_arbitrary_runtimemod.test.cpp.html">test/ntt_arbitrary_runtimemod.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cstddef>
#include <cstdint>

constexpr size_t popcount(const uint64_t x) {
  return __builtin_popcountll(x);
}

constexpr size_t count_zero_right(const uint64_t x) {
  return x == 0 ? 64 : __builtin_ctzll(x);
}

constexpr size_t count_zero_left(const uint64_t x) {
  return x == 0 ? 64 : __builtin_clzll(x);
}

constexpr size_t bit_width(const uint64_t x) { 
  return 64 - count_zero_left(x);
}

constexpr uint64_t most_significant_bit(const uint64_t x) {
  return x == 0 ? 0 : uint64_t(1) << (bit_width(x) - 1);
}

constexpr uint64_t least_significant_bit(const uint64_t x) {
  return x & (-x);
}

constexpr uint64_t next_power_of_two(const uint64_t x) {
  return x == 0 ? 0 : most_significant_bit(2 * x - 1);
}

constexpr uint32_t bit_reverse_32(uint32_t x) {
  x = ((x >> 1) & 0x55555555) | ((x & 0x55555555) << 1);
  x = ((x >> 2) & 0x33333333) | ((x & 0x33333333) << 2);
  x = ((x >> 4) & 0x0F0F0F0F) | ((x & 0x0F0F0F0F) << 4);
  x = ((x >> 8) & 0x00FF00FF) | ((x & 0x00FF00FF) << 8);
  x = ( x >> 16             ) | ( x               << 16);
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

constexpr size_t popcount(const uint64_t x) {
  return __builtin_popcountll(x);
}

constexpr size_t count_zero_right(const uint64_t x) {
  return x == 0 ? 64 : __builtin_ctzll(x);
}

constexpr size_t count_zero_left(const uint64_t x) {
  return x == 0 ? 64 : __builtin_clzll(x);
}

constexpr size_t bit_width(const uint64_t x) { 
  return 64 - count_zero_left(x);
}

constexpr uint64_t most_significant_bit(const uint64_t x) {
  return x == 0 ? 0 : uint64_t(1) << (bit_width(x) - 1);
}

constexpr uint64_t least_significant_bit(const uint64_t x) {
  return x & (-x);
}

constexpr uint64_t next_power_of_two(const uint64_t x) {
  return x == 0 ? 0 : most_significant_bit(2 * x - 1);
}

constexpr uint32_t bit_reverse_32(uint32_t x) {
  x = ((x >> 1) & 0x55555555) | ((x & 0x55555555) << 1);
  x = ((x >> 2) & 0x33333333) | ((x & 0x33333333) << 2);
  x = ((x >> 4) & 0x0F0F0F0F) | ((x & 0x0F0F0F0F) << 4);
  x = ((x >> 8) & 0x00FF00FF) | ((x & 0x00FF00FF) << 8);
  x = ( x >> 16             ) | ( x               << 16);
  return x;
}

/**
 * @title Bit Operations
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

