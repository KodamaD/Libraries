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


# :warning: container/fenwick_tree.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5f0b6ebc4bea10285ba2b8a6ce78b863">container</a>
* <a href="{{ site.github.repository_url }}/blob/master/container/fenwick_tree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-04 16:35:04+09:00




## Depends on

* :question: <a href="../other/bit_operation.cpp.html">other/bit_operation.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "../other/bit_operation.cpp"
#include <cstddef>
#include <vector>

template <class T>
class fenwick_tree {
public:
  using value_type = T;
  using size_type = size_t;

private:
  std::vector<value_type> M_tree;

public:
  fenwick_tree() = default;
  explicit fenwick_tree(size_type size) { initialize(size); }

  void initialize(size_type size) {
    node.assign(size + 1, 0);
  }

  void add(size_type index, const value_type& x) {
    ++index;
    while (index <= size()) {
      node[index] += x;
      index += least_significant_bit(index);
    }
  }

  value_type get(size_type index) const {
    ++index;
    value_type res = 0;
    while (index > 0) {
      res += node[index];
      index -= least_significant_bit(index);
    }
    return res;
  }
  value_type fold(size_type index l, size_type index r) const {
    return get(r - 1) - get(l - 1);
  }

  size_type size() const {
    return M_tree.size() - 1;
  }

};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "container/fenwick_tree.cpp"

#line 2 "other/bit_operation.cpp"

#include <cstddef>
#include <cstdint>

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
  constexpr uint32_t b16 = 0b00000000000000001111111111111111;
  constexpr uint32_t  b8 = 0b00000000111111110000000011111111;
  constexpr uint32_t  b4 = 0b00001111000011110000111100001111;
  constexpr uint32_t  b2 = 0b00110011001100110011001100110011;
  constexpr uint32_t  b1 = 0b01010101010101010101010101010101;
  x = ((x >> 16) & b16) | ((x & b16) << 16);
  x = ((x >>  8) &  b8) | ((x &  b8) <<  8);
  x = ((x >>  4) &  b4) | ((x &  b4) <<  4);
  x = ((x >>  2) &  b2) | ((x &  b2) <<  2);
  x = ((x >>  1) &  b1) | ((x &  b1) <<  1);
  return x;
}
#line 5 "container/fenwick_tree.cpp"
#include <vector>

template <class T>
class fenwick_tree {
public:
  using value_type = T;
  using size_type = size_t;

private:
  std::vector<value_type> M_tree;

public:
  fenwick_tree() = default;
  explicit fenwick_tree(size_type size) { initialize(size); }

  void initialize(size_type size) {
    node.assign(size + 1, 0);
  }

  void add(size_type index, const value_type& x) {
    ++index;
    while (index <= size()) {
      node[index] += x;
      index += least_significant_bit(index);
    }
  }

  value_type get(size_type index) const {
    ++index;
    value_type res = 0;
    while (index > 0) {
      res += node[index];
      index -= least_significant_bit(index);
    }
    return res;
  }
  value_type fold(size_type index l, size_type index r) const {
    return get(r - 1) - get(l - 1);
  }

  size_type size() const {
    return M_tree.size() - 1;
  }

};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

