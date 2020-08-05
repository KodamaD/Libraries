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


# :heavy_check_mark: Disjoint Sparse Table

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5f0b6ebc4bea10285ba2b8a6ce78b863">container</a>
* <a href="{{ site.github.repository_url }}/blob/master/container/disjoint_sparse_table.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-05 18:30:10+09:00




## Depends on

* :heavy_check_mark: <a href="../other/bit_operation.cpp.html">Bit Operations</a>
* :heavy_check_mark: <a href="../other/monoid.cpp.html">Monoid Utility</a>


## Required by

* :heavy_check_mark: <a href="dst_tree.cpp.html">DST Tree</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/dst_tree.test.cpp.html">test/dst_tree.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "../other/bit_operation.cpp"
#include "../other/monoid.cpp"

#include <cstddef>
#include <vector>

template <class SemiGroup>
class disjoint_sparse_table {
public:
  using structure       = SemiGroup;
  using value_semigroup = typename SemiGroup::value_structure;
  using value_type      = typename SemiGroup::value_structure::type;
  using size_type       = size_t;

private:

  std::vector<std::vector<value_type>> M_table;

public:
  disjoint_sparse_table() = default;
  template <class InputIterator>
  explicit disjoint_sparse_table(InputIterator first, InputIterator last) { construct(first, last); }

  template <class InputIterator>
  void construct(InputIterator first, InputIterator last) {
    clear();
    const size_type size = std::distance(first, last);
    const size_type height = bit_width(size);
    M_table.resize(height, std::vector<value_type>(size));
    M_table.front() = std::vector<value_type>(first, last);
    for (size_type story = 1; story < height; ++story) {
      const size_type bit = (1 << story);
      for (size_type left = 0; left < size; left += (bit << 1)) {
        const size_type mid = (left + bit < size ? left + bit : size);
        M_table[story][mid - 1] = M_table[0][mid - 1];
        for (size_type i = mid - 1; i-- != left;) {
          M_table[story][i] = value_semigroup::operation(M_table[0][i], M_table[story][i + 1]);
        }
        if (mid >= size) continue;
        const size_type right = (mid + bit < size ? mid + bit : size);
        M_table[story][mid] = M_table[0][mid];
        for (size_type i = mid + 1; i != right; ++i) {
          M_table[story][i] = value_semigroup::operation(M_table[story][i - 1], M_table[0][i]);
        }
      }
    }
  }

  value_type fold(const size_type first, size_type last) const {
    if (first == last) return empty_exception<value_semigroup>();
    if (first == --last) return M_table[0][first];
    const size_type height = bit_width(first ^ last) - 1;
    return value_semigroup::operation(M_table[height][first], M_table[height][last]);
  }

  void clear() {
    M_table.clear();
    M_table.shrink_to_fit();
  }
  size_type size() const {
    if (M_table.empty()) return 0;
    return M_table.front().size();
  }
  bool empty() const {
    return M_table.empty();
  }

};

/**
 * @title Disjoint Sparse Table
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "container/disjoint_sparse_table.cpp"

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
#line 2 "other/monoid.cpp"

#include <type_traits>
#include <utility>
#include <stdexcept>

template <class T, class = void>
class has_identity: public std::false_type { };

template <class T>
class has_identity<T, typename std::conditional<false, decltype(T::identity()), void>::type>: public std::true_type { };

template <class T>
constexpr typename std::enable_if<has_identity<T>::value, typename T::type>::type empty_exception() {
  return T::identity();
}
template <class T>
[[noreturn]] constexpr typename std::enable_if<!has_identity<T>::value, typename T::type>::type empty_exception() {
  throw std::runtime_error("type T has no identity");
}

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

/**
 * @title Monoid Utility
 */
#line 5 "container/disjoint_sparse_table.cpp"

#line 7 "container/disjoint_sparse_table.cpp"
#include <vector>

template <class SemiGroup>
class disjoint_sparse_table {
public:
  using structure       = SemiGroup;
  using value_semigroup = typename SemiGroup::value_structure;
  using value_type      = typename SemiGroup::value_structure::type;
  using size_type       = size_t;

private:

  std::vector<std::vector<value_type>> M_table;

public:
  disjoint_sparse_table() = default;
  template <class InputIterator>
  explicit disjoint_sparse_table(InputIterator first, InputIterator last) { construct(first, last); }

  template <class InputIterator>
  void construct(InputIterator first, InputIterator last) {
    clear();
    const size_type size = std::distance(first, last);
    const size_type height = bit_width(size);
    M_table.resize(height, std::vector<value_type>(size));
    M_table.front() = std::vector<value_type>(first, last);
    for (size_type story = 1; story < height; ++story) {
      const size_type bit = (1 << story);
      for (size_type left = 0; left < size; left += (bit << 1)) {
        const size_type mid = (left + bit < size ? left + bit : size);
        M_table[story][mid - 1] = M_table[0][mid - 1];
        for (size_type i = mid - 1; i-- != left;) {
          M_table[story][i] = value_semigroup::operation(M_table[0][i], M_table[story][i + 1]);
        }
        if (mid >= size) continue;
        const size_type right = (mid + bit < size ? mid + bit : size);
        M_table[story][mid] = M_table[0][mid];
        for (size_type i = mid + 1; i != right; ++i) {
          M_table[story][i] = value_semigroup::operation(M_table[story][i - 1], M_table[0][i]);
        }
      }
    }
  }

  value_type fold(const size_type first, size_type last) const {
    if (first == last) return empty_exception<value_semigroup>();
    if (first == --last) return M_table[0][first];
    const size_type height = bit_width(first ^ last) - 1;
    return value_semigroup::operation(M_table[height][first], M_table[height][last]);
  }

  void clear() {
    M_table.clear();
    M_table.shrink_to_fit();
  }
  size_type size() const {
    if (M_table.empty()) return 0;
    return M_table.front().size();
  }
  bool empty() const {
    return M_table.empty();
  }

};

/**
 * @title Disjoint Sparse Table
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

