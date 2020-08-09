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


# :heavy_check_mark: test/fenwick_tree.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/fenwick_tree.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-05 18:30:10+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B">https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B</a>


## Depends on

* :heavy_check_mark: <a href="../../library/container/fenwick_tree.cpp.html">Fenwick Tree</a>
* :heavy_check_mark: <a href="../../library/other/bit_operation.cpp.html">Bit Operations</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp

#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"

#include "../container/fenwick_tree.cpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

int main() {
  size_t N, Q;
  std::cin >> N >> Q;
  fenwick_tree<uint32_t> seg(N);
  while (Q--) {
    char type;
    std::cin >> type;
    if (type == '0') {
      size_t x;
      uint32_t y;
      std::cin >> x >> y;
      seg.add(x - 1, y);
    }
    else {
      size_t x, y;
      std::cin >> x >> y;
      std::cout << seg.fold(x - 1, y) << '\n';
    }
  }
  return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/fenwick_tree.test.cpp"

#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"

#line 2 "container/fenwick_tree.cpp"

#line 2 "other/bit_operation.cpp"

#include <cstddef>
#include <cstdint>

constexpr size_t bit_ppc(const uint64_t x) {
  return __builtin_popcountll(x);
}

constexpr size_t bit_ctzr(const uint64_t x) {
  return x == 0 ? 64 : __builtin_ctzll(x);
}

constexpr size_t bit_ctzl(const uint64_t x) {
  return x == 0 ? 64 : __builtin_clzll(x);
}

constexpr size_t bit_width(const uint64_t x) { 
  return 64 - bit_ctzl(x);
}

constexpr uint64_t bit_msb(const uint64_t x) {
  return x == 0 ? 0 : uint64_t(1) << (bit_width(x) - 1);
}

constexpr uint64_t bit_lsb(const uint64_t x) {
  return x & (-x);
}

constexpr uint64_t bit_cover(const uint64_t x) {
  return x == 0 ? 0 : bit_msb(2 * x - 1);
}

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
#line 4 "container/fenwick_tree.cpp"

#line 6 "container/fenwick_tree.cpp"
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
    M_tree.assign(size + 1, value_type{});
  }

  void add(size_type index, const value_type& x) {
    ++index;
    while (index <= size()) {
      M_tree[index] += x;
      index += bit_lsb(index);
    }
  }

  value_type get(size_type index) const {
    ++index;
    value_type res{};
    while (index > 0) {
      res += M_tree[index];
      index -= bit_lsb(index);
    }
    return res;
  }
  value_type fold(size_type l, size_type r) const {
    if (l == 0 && r == 0) return value_type{};
    if (l == 0) return get(r - 1);
    return get(r - 1) - get(l - 1);
  }

  size_type size() const {
    return M_tree.size() - 1;
  }

};

/**
 * @title Fenwick Tree
 */
#line 5 "test/fenwick_tree.test.cpp"

#line 8 "test/fenwick_tree.test.cpp"
#include <iostream>

int main() {
  size_t N, Q;
  std::cin >> N >> Q;
  fenwick_tree<uint32_t> seg(N);
  while (Q--) {
    char type;
    std::cin >> type;
    if (type == '0') {
      size_t x;
      uint32_t y;
      std::cin >> x >> y;
      seg.add(x - 1, y);
    }
    else {
      size_t x, y;
      std::cin >> x >> y;
      std::cout << seg.fold(x - 1, y) << '\n';
    }
  }
  return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
