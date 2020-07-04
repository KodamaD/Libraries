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


# :warning: container/li_chao_tree.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5f0b6ebc4bea10285ba2b8a6ce78b863">container</a>
* <a href="{{ site.github.repository_url }}/blob/master/container/li_chao_tree.cpp">View this file on GitHub</a>
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
#include <iterator>
#include <algorithm>
#include <functional>

template <class T, class U = std::less<T>>
class li_chao_tree {
public:
  using value_type = T;
  using compare_type = U;
  using size_type = size_t;

  static constexpr compare_type compare{};
  static constexpr value_type max_inf = std::numeric_limits<value_type>::max();
  static constexpr value_type min_inf = std::numeric_limits<value_type>::min();
  static constexpr value_type identity = compare(min_inf, max_inf) ? max_inf : min_inf;

  struct line_type {
    value_type a, b;
    line_type(value_type a_ = 0, value_type b_ = identity): a(a_), b(b_) { }
    value_type operator () (value_type x) const { return a * x + b; }
  };

private:
  size_t M_size;
  std::vector<value_type> M_coordinate;
  std::vector<line_type> M_line;

  void M_add_line_impl(line_type line, size_type k, size_type l, size_type r) {
    size_type m = (l + r) >> 1;
    value_type x_l = M_coordinate[l];
    value_type x_m = M_coordinate[m];
    value_type x_r = M_coordinate[r];
    bool left = compare(line(x_l), M_line[k](x_l));
    bool mid = compare(line(x_m), M_line[k](x_m));
    bool right = compare(line(x_r), M_line[k](x_r));
    if (left && right) { M_line[k] = line; return; }
    if (!left && !right) return;
    if (mid) std::swap(line, M_line[k]);
    if (left != mid) M_add_line_impl(line, k << 1, l, m);
    else M_add_line_impl(line, k << 1 | 1, m + 1, r);
  }

public:
  li_chao_tree() = default;
  li_chao_tree(const std::vector<value_type> &coordinate_) { build(coordinate_); }

  void build(const std::vector<value_type> &coordinate_) {
    M_coordinate = coordinate_;
    M_size = next_power_of_two(coordinate_.size());
    value_type margin = M_coordinate.empty() ? 0 : M_coordinate.back();
    M_coordinate.resize(M_size, margin);
    M_line.assign(M_size << 1, line_type());
  }

  void add_line(line_type line) {
    M_add_line_impl(line, 1, 0, M_size - 1);
  }

  void add_segment(line_type line, value_type l, value_type r) {
    if (M_coordinate.front() > r) return;
    size_type i = std::lower_bound(M_coordinate.begin(), M_coordinate.end(), l) - M_coordinate.begin();
    size_type j = std::upper_bound(M_coordinate.begin(), M_coordinate.end(), r) - M_coordinate.begin();
    add_segment_compressed(line, i, j);
  }
  void add_segment_compressed(line_type line, size_type l, size_type r) {
    size_type cur_l = l, cur_r = r;
    size_type cur_size = 1;
    l += M_size;
    r += M_size;
    while (l < r) {
      if (l & 1) { 
        M_add_line_impl(line, l, cur_l, cur_l + cur_size - 1);
        ++l;
        cur_l += cur_size;
      }
      if (r & 1) {
        --r;
        cur_r -= cur_size;
        M_add_line_impl(line, r, cur_r, cur_r + cur_size - 1);
      }
      l >>= 1;
      r >>= 1;
      cur_size <<= 1;
    }
  }

  value_type get(value_type x) const {
    auto itr = std::lower_bound(M_coordinate.begin(), M_coordinate.end(), x);
    if (itr == M_coordinate.end() || x != *itr) return identity;
    return get_compressed(itr - M_coordinate.begin());
  }
  value_type get_compressed(size_type k) const {
    value_type x = M_coordinate[k];
    value_type res = identity;
    k += M_size;
    while (k > 0) {
      if (compare(M_line[k](x), res)) res = M_line[k](x);
      k >>= 1;
    }
    return res;
  }

};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "container/li_chao_tree.cpp"

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
#line 5 "container/li_chao_tree.cpp"
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>

template <class T, class U = std::less<T>>
class li_chao_tree {
public:
  using value_type = T;
  using compare_type = U;
  using size_type = size_t;

  static constexpr compare_type compare{};
  static constexpr value_type max_inf = std::numeric_limits<value_type>::max();
  static constexpr value_type min_inf = std::numeric_limits<value_type>::min();
  static constexpr value_type identity = compare(min_inf, max_inf) ? max_inf : min_inf;

  struct line_type {
    value_type a, b;
    line_type(value_type a_ = 0, value_type b_ = identity): a(a_), b(b_) { }
    value_type operator () (value_type x) const { return a * x + b; }
  };

private:
  size_t M_size;
  std::vector<value_type> M_coordinate;
  std::vector<line_type> M_line;

  void M_add_line_impl(line_type line, size_type k, size_type l, size_type r) {
    size_type m = (l + r) >> 1;
    value_type x_l = M_coordinate[l];
    value_type x_m = M_coordinate[m];
    value_type x_r = M_coordinate[r];
    bool left = compare(line(x_l), M_line[k](x_l));
    bool mid = compare(line(x_m), M_line[k](x_m));
    bool right = compare(line(x_r), M_line[k](x_r));
    if (left && right) { M_line[k] = line; return; }
    if (!left && !right) return;
    if (mid) std::swap(line, M_line[k]);
    if (left != mid) M_add_line_impl(line, k << 1, l, m);
    else M_add_line_impl(line, k << 1 | 1, m + 1, r);
  }

public:
  li_chao_tree() = default;
  li_chao_tree(const std::vector<value_type> &coordinate_) { build(coordinate_); }

  void build(const std::vector<value_type> &coordinate_) {
    M_coordinate = coordinate_;
    M_size = next_power_of_two(coordinate_.size());
    value_type margin = M_coordinate.empty() ? 0 : M_coordinate.back();
    M_coordinate.resize(M_size, margin);
    M_line.assign(M_size << 1, line_type());
  }

  void add_line(line_type line) {
    M_add_line_impl(line, 1, 0, M_size - 1);
  }

  void add_segment(line_type line, value_type l, value_type r) {
    if (M_coordinate.front() > r) return;
    size_type i = std::lower_bound(M_coordinate.begin(), M_coordinate.end(), l) - M_coordinate.begin();
    size_type j = std::upper_bound(M_coordinate.begin(), M_coordinate.end(), r) - M_coordinate.begin();
    add_segment_compressed(line, i, j);
  }
  void add_segment_compressed(line_type line, size_type l, size_type r) {
    size_type cur_l = l, cur_r = r;
    size_type cur_size = 1;
    l += M_size;
    r += M_size;
    while (l < r) {
      if (l & 1) { 
        M_add_line_impl(line, l, cur_l, cur_l + cur_size - 1);
        ++l;
        cur_l += cur_size;
      }
      if (r & 1) {
        --r;
        cur_r -= cur_size;
        M_add_line_impl(line, r, cur_r, cur_r + cur_size - 1);
      }
      l >>= 1;
      r >>= 1;
      cur_size <<= 1;
    }
  }

  value_type get(value_type x) const {
    auto itr = std::lower_bound(M_coordinate.begin(), M_coordinate.end(), x);
    if (itr == M_coordinate.end() || x != *itr) return identity;
    return get_compressed(itr - M_coordinate.begin());
  }
  value_type get_compressed(size_type k) const {
    value_type x = M_coordinate[k];
    value_type res = identity;
    k += M_size;
    while (k > 0) {
      if (compare(M_line[k](x), res)) res = M_line[k](x);
      k >>= 1;
    }
    return res;
  }

};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

