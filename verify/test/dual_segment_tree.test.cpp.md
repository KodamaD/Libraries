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


# :heavy_check_mark: test/dual_segment_tree.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/dual_segment_tree.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-12 13:43:20+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_D">https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_D</a>


## Depends on

* :heavy_check_mark: <a href="../../library/container/dual_segment_tree.cpp.html">Dual Segment Tree</a>
* :heavy_check_mark: <a href="../../library/other/bit_operation.cpp.html">Bit Operations</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp

#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_D"

#include "../container/dual_segment_tree.cpp"

#include <cstddef>
#include <cstdint>
#include <vector>
#include <iostream>

struct dst_monoid {
  struct value_structure {
    using type = uint32_t;
  };
  struct operator_structure {
    class type {
      using base_type  = uint32_t;
      using usage_type = bool;
    public:
      base_type  value;
      usage_type available; 
      explicit type(): value(base_type{}), available(false) { }
      type(const base_type& value): value(value), available(true) { }
      operator base_type() const { return value; }
    };
    static type identity() { return type(); }
    static type operation(const type& v1, const type& v2) { 
      if (!v1.available) return v2;
      if (!v2.available) return v1;
      return v2;
    }
  };
  static typename value_structure::type operation(
    const typename value_structure::type    &val,
    const typename operator_structure::type &op) {
    if (!op.available) return val;
    return op.value;
  }
};

int main() {
  size_t N, Q;
  std::cin >> N >> Q;
  dual_segment_tree<dst_monoid> seg;
  {
    std::vector<uint32_t> build(N, (uint32_t(1) << 31) - 1);
    seg.construct(build.begin(), build.end());
  }
  while (Q--) {
    size_t type;
    std::cin >> type;
    if (type == 0) {
      size_t s, t;
      std::cin >> s >> t;
      uint32_t x;
      std::cin >> x;
      seg.operate(s, t + 1, x);
    }
    else {
      size_t i;
      std::cin >> i;
      std::cout << seg.at(i) << '\n';
    }
  }
  return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/dual_segment_tree.test.cpp"

#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_D"

#line 2 "container/dual_segment_tree.cpp"

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
#line 5 "container/dual_segment_tree.cpp"
#include <vector>
#include <iterator>
#include <algorithm>

template <class CombinedMonoid>
class dual_segment_tree {
public:
  using structure       = CombinedMonoid;
  using value_type      = typename CombinedMonoid::value_structure::type;
  using operator_monoid = typename CombinedMonoid::operator_structure;
  using operator_type   = typename CombinedMonoid::operator_structure::type;
  using size_type       = size_t;

private:
  static void S_apply(operator_type &op, const operator_type &add) {
    op = operator_monoid::operation(op, add);
  }

  void M_propagate(const size_type index) {
    S_apply(M_tree[index << 1 | 0], M_tree[index]);
    S_apply(M_tree[index << 1 | 1], M_tree[index]);
    M_tree[index] = operator_monoid::identity();
  }

  void M_pushdown(const size_type index) {
    const size_type lsb = count_zero_right(index);
    for (size_type story = bit_width(index); story != lsb; --story) {
      M_propagate(index >> story);
    }
  }

  std::vector<value_type> M_leaves; 
  std::vector<operator_type> M_tree;

public:
  dual_segment_tree() = default;
  explicit dual_segment_tree(const size_type size) { initialize(size); }
  template <class InputIterator>
  explicit dual_segment_tree(InputIterator first, InputIterator last) { construct(first, last); }

  void initialize(const size_type size) {
    clear();
    M_leaves.assign(size, value_type{});
    M_tree.assign(size << 1, operator_monoid::identity());
  }

  template <class InputIterator>
  void construct(InputIterator first, InputIterator last) {
    clear();
    const size_type size = std::distance(first, last);
    M_leaves.reserve(size);
    std::copy(first, last, std::back_inserter(M_leaves));
    M_tree.assign(size << 1, operator_monoid::identity());
  }

  value_type at(size_type index) const {
    const size_type index_c = index;
    index += size();
    operator_type op = M_tree[index];
    while (index != 1) {
      index >>= 1;
      S_apply(op, M_tree[index]);
    }
    return structure::operation(M_leaves[index_c], op);
  }

  void operate(size_type first, size_type last, const operator_type &op) {
    first += size();
    last  += size();
    M_pushdown(first);
    M_pushdown(last);
    while (first != last) {
      if (first & 1) {
        S_apply(M_tree[first], op);
        ++first;
      }
      if (last & 1) {
        --last;
        S_apply(M_tree[last], op);
      }
      first >>= 1;
      last  >>= 1;
    }
  }

  void assign(size_type index, const value_type &val) {
    const size_type index_c = index;
    index += size();
    for (size_type story = bit_width(index); story != 0; --story) {
      M_propagate(index >> story);
    }
    M_tree[index] = operator_monoid::identity();
    M_leaves[index_c] = val;
  }

  void clear() {
    M_leaves.clear();
    M_leaves.shrink_to_fit();
    M_tree.clear();
    M_tree.shrink_to_fit();
  }

  size_type size() const { 
    return M_leaves.size();
  }

};

/**
 * @title Dual Segment Tree
 */
#line 5 "test/dual_segment_tree.test.cpp"

#line 9 "test/dual_segment_tree.test.cpp"
#include <iostream>

struct dst_monoid {
  struct value_structure {
    using type = uint32_t;
  };
  struct operator_structure {
    class type {
      using base_type  = uint32_t;
      using usage_type = bool;
    public:
      base_type  value;
      usage_type available; 
      explicit type(): value(base_type{}), available(false) { }
      type(const base_type& value): value(value), available(true) { }
      operator base_type() const { return value; }
    };
    static type identity() { return type(); }
    static type operation(const type& v1, const type& v2) { 
      if (!v1.available) return v2;
      if (!v2.available) return v1;
      return v2;
    }
  };
  static typename value_structure::type operation(
    const typename value_structure::type    &val,
    const typename operator_structure::type &op) {
    if (!op.available) return val;
    return op.value;
  }
};

int main() {
  size_t N, Q;
  std::cin >> N >> Q;
  dual_segment_tree<dst_monoid> seg;
  {
    std::vector<uint32_t> build(N, (uint32_t(1) << 31) - 1);
    seg.construct(build.begin(), build.end());
  }
  while (Q--) {
    size_t type;
    std::cin >> type;
    if (type == 0) {
      size_t s, t;
      std::cin >> s >> t;
      uint32_t x;
      std::cin >> x;
      seg.operate(s, t + 1, x);
    }
    else {
      size_t i;
      std::cin >> i;
      std::cout << seg.at(i) << '\n';
    }
  }
  return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

