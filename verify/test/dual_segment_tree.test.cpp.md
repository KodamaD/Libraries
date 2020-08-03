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
    - Last commit date: 2020-08-03 12:32:12+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_D">https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_D</a>


## Depends on

* :heavy_check_mark: <a href="../../library/container/dual_segment_tree.cpp.html">Dual Segment Tree</a>
* :heavy_check_mark: <a href="../../library/other/bit_operation.cpp.html">Bit Operations</a>
* :heavy_check_mark: <a href="../../library/other/monoid.cpp.html">other/monoid.cpp</a>


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
    using type = uint32_t;
    static type operation(const type&, const type &v2) {
      return v2;
    }
  };
  static typename value_structure::type operation(
    const typename value_structure::type    &,
    const typename operator_structure::type &op) {
    return op;
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
#line 1 "other/monoid.cpp"

#include <type_traits>
#include <utility>
#include <stdexcept>

template <class T, class = void>
class has_identity: public std::false_type { };

template <class T>
class has_identity<T, typename std::conditional<false, decltype(T::identity()), void>::type>: public std::true_type { };

template <class T, bool HasIdentity>
class fixed_monoid_impl: public T {
public:
  static constexpr typename T::type convert(const typename T::type &value) { return value; }
  static constexpr typename T::type revert(const typename T::type &value) { return value; }

};

template <class T>
class fixed_monoid_impl<T, false>: private T {
public:
  class type {
  public:
    typename T::type value;
    bool state;
  
    explicit constexpr type(): value(typename T::type { }), state(false) { }
    explicit constexpr type(const typename T::type &value): value(value), state(true) { }

  };

  static constexpr type convert(const typename T::type &value) { return type(value); }
  static constexpr typename T::type revert(const type &value) { 
    if (!value.state) throw std::runtime_error("attempted to revert identity to non-monoid"); 
    return value.value; 
  }

  static constexpr type identity() { return type(); }
  static constexpr type operation(const type &v1, const type &v2) {
    if (!v1.state) return v2;
    if (!v2.state) return v1;
    return type(T::operation(v1.value, v2.value));
  }

};

template <class T>
using fixed_monoid = fixed_monoid_impl<T, has_identity<T>::value>;

template <class T, bool HasIdentity>
class fixed_combined_monoid_impl {
public:
  using value_structure    = typename T::value_structure;
  using operator_structure = fixed_monoid<typename T::operator_structure>;

  template <class... Args>
  static constexpr typename value_structure::type operation(
    const typename value_structure::type    &val,
    const typename operator_structure::type &op,
    Args&&... args) {
    return T::operation(val, op, std::forward<Args>(args)...);
  }

};

template <class T>
class fixed_combined_monoid_impl<T, false> {
public:
  using value_structure    = typename T::value_structure;
  using operator_structure = fixed_monoid<typename T::operator_structure>;

  template <class... Args>
  static constexpr typename value_structure::type operation(
    const typename value_structure::type    &val,
    const typename operator_structure::type &op,
    Args&&... args) {
    if (!op.state) return val;
    return T::operation(val, op.value, std::forward<Args>(args)...);
  }

};

template <class T>
using fixed_combined_monoid = fixed_combined_monoid_impl<T, has_identity<typename T::operator_structure>::value>;
#line 6 "container/dual_segment_tree.cpp"
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
  using fixed_structure       = fixed_combined_monoid<structure>;
  using fixed_operator_monoid = typename fixed_structure::operator_structure;
  using fixed_operator_type   = typename fixed_operator_monoid::type;

  static void S_apply(fixed_operator_type &op, const fixed_operator_type &add) {
    op = fixed_operator_monoid::operation(op, add);
  }

  void M_propagate(const size_type index) {
    S_apply(M_tree[index << 1 | 0], M_tree[index]);
    S_apply(M_tree[index << 1 | 1], M_tree[index]);
    M_tree[index] = fixed_operator_monoid::identity();
  }

  void M_pushdown(const size_type index) {
    const size_type lsb = bit_ctzr(index);
    for (size_type story = bit_width(index); story != lsb; --story) {
      M_propagate(index >> story);
    }
  }

  std::vector<value_type> M_leaves; 
  std::vector<fixed_operator_type> M_tree;

public:
  dual_segment_tree() = default;
  explicit dual_segment_tree(const size_type size) { initialize(size); }
  template <class InputIterator>
  explicit dual_segment_tree(InputIterator first, InputIterator last) { construct(first, last); }

  void initialize(const size_type size) {
    clear();
    M_leaves.assign(size, value_type{});
    M_tree.assign(size << 1, fixed_operator_monoid::identity());
  }

  template <class InputIterator>
  void construct(InputIterator first, InputIterator last) {
    clear();
    const size_type size = std::distance(first, last);
    M_leaves.reserve(size);
    std::copy(first, last, std::back_inserter(M_leaves));
    M_tree.assign(size << 1, fixed_operator_monoid::identity());
  }

  value_type at(size_type index) const {
    const size_type index_c = index;
    index += size();
    fixed_operator_type op = M_tree[index];
    while (index != 1) {
      index >>= 1;
      S_apply(op, M_tree[index]);
    }
    return fixed_structure::operation(M_leaves[index_c], op);
  }

  void operate(size_type first, size_type last, const operator_type &op_) {
    const auto op = fixed_operator_monoid::convert(op_);
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
    M_tree[index] = fixed_operator_monoid::identity();
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
    using type = uint32_t;
    static type operation(const type&, const type &v2) {
      return v2;
    }
  };
  static typename value_structure::type operation(
    const typename value_structure::type    &,
    const typename operator_structure::type &op) {
    return op;
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

