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


# :heavy_check_mark: DST Tree

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5f0b6ebc4bea10285ba2b8a6ce78b863">container</a>
* <a href="{{ site.github.repository_url }}/blob/master/container/dst_tree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-09 18:26:02+09:00




## Depends on

* :heavy_check_mark: <a href="disjoint_sparse_table.cpp.html">Disjoint Sparse Table</a>
* :question: <a href="../other/bit_operation.cpp.html">Bit Operations</a>
* :question: <a href="../other/monoid.cpp.html">Monoid Utility</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/dst_tree.test.cpp.html">test/dst_tree.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp

#include "../container/disjoint_sparse_table.cpp"

#include <cstddef>
#include <vector>
#include <cassert>

template <class SemiGroup>
class dst_tree {
public:
  using structure       = SemiGroup;
  using value_semigroup = typename SemiGroup::value_structure;
  using value_type      = typename SemiGroup::value_structure::type;
  using size_type       = size_t;

private:
  size_type M_size = 0, M_logn = 0;
  std::vector<disjoint_sparse_table<structure>> M_tree;

public:
  dst_tree() = default;
  template <class InputIterator>
  explicit dst_tree(InputIterator first, InputIterator last) { construct(first, last); }

  template <class InputIterator>
  void construct(InputIterator first, InputIterator last) {
    clear();
    M_size = std::distance(first, last);
    M_logn = bit_width(M_size);
    const size_type blocks = (M_size + M_logn - 1) / M_logn;
    M_tree.reserve(blocks + 1);
    std::vector<value_type> all;
    all.reserve(blocks);
    size_type cur = 0;
    while (cur != M_size) {
      const size_type len = std::min(M_size - cur, M_logn);
      auto right = first;
      std::advance(right, len);
      M_tree.emplace_back(first, right);
      all.push_back(M_tree.back().fold(0, len));
      cur += len;
      first = right;
    }
    M_tree.emplace_back(all.begin(), all.end());
  }

  value_type fold(const size_type first, size_type last) const {
    assert(first <= last);
    assert(last <= size());
    if (first == last--) return empty_exception<value_semigroup>();
    const size_type fsec = first / M_logn, lsec = last / M_logn;
    const size_type fidx = first - fsec * M_logn, lidx = last - lsec * M_logn;
    if (fsec == lsec) return M_tree[fsec].fold(fidx, lidx + 1);
    const value_type fres = M_tree[fsec].fold(fidx, M_logn);
    const value_type lres = M_tree[lsec].fold(0, lidx + 1);
    if (fsec + 1 == lsec) return value_semigroup::operation(fres, lres);
    const value_type mres = M_tree.back().fold(fsec + 1, lsec);
    return value_semigroup::operation(value_semigroup::operation(fres, mres), lres);
  }

  void clear() {
    M_tree.clear();
    M_tree.shrink_to_fit();
    M_size = M_logn = 0;
  }
  size_type size() const {
    return M_size;
  }
};

/**
 * @title DST Tree
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "container/dst_tree.cpp"

#line 2 "container/disjoint_sparse_table.cpp"

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
[[noreturn]] typename std::enable_if<!has_identity<T>::value, typename T::type>::type empty_exception() {
  throw std::runtime_error("type T has no identity");
}

template <class T, bool HasIdentity>
class fixed_monoid_impl: public T {
public:
  static constexpr typename T::type convert(const typename T::type &value) { return value; }
  static constexpr typename T::type revert(const typename T::type &value) { return value; }

  template <class Mapping, class Value, class... Args>
  static constexpr void operate(Mapping &&func, Value &value, const typename T::type &op, Args&&... args) {
    value = func(value, op, std::forward<Args>(args)...);
  }
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

  template <class Mapping, class Value, class... Args>
  static constexpr void operate(Mapping &&func, Value &value, const type &op, Args&&... args) {
    if (!op.state) return;
    value = func(value, op, std::forward<Args>(args)...);
  }
};

template <class T>
using fixed_monoid = fixed_monoid_impl<T, has_identity<T>::value>;

/**
 * @title Monoid Utility
 */
#line 5 "container/disjoint_sparse_table.cpp"

#line 7 "container/disjoint_sparse_table.cpp"
#include <vector>
#include <cassert>

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
    assert(first <= last);
    assert(last <= size());
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
};

/**
 * @title Disjoint Sparse Table
 */
#line 3 "container/dst_tree.cpp"

#line 7 "container/dst_tree.cpp"

template <class SemiGroup>
class dst_tree {
public:
  using structure       = SemiGroup;
  using value_semigroup = typename SemiGroup::value_structure;
  using value_type      = typename SemiGroup::value_structure::type;
  using size_type       = size_t;

private:
  size_type M_size = 0, M_logn = 0;
  std::vector<disjoint_sparse_table<structure>> M_tree;

public:
  dst_tree() = default;
  template <class InputIterator>
  explicit dst_tree(InputIterator first, InputIterator last) { construct(first, last); }

  template <class InputIterator>
  void construct(InputIterator first, InputIterator last) {
    clear();
    M_size = std::distance(first, last);
    M_logn = bit_width(M_size);
    const size_type blocks = (M_size + M_logn - 1) / M_logn;
    M_tree.reserve(blocks + 1);
    std::vector<value_type> all;
    all.reserve(blocks);
    size_type cur = 0;
    while (cur != M_size) {
      const size_type len = std::min(M_size - cur, M_logn);
      auto right = first;
      std::advance(right, len);
      M_tree.emplace_back(first, right);
      all.push_back(M_tree.back().fold(0, len));
      cur += len;
      first = right;
    }
    M_tree.emplace_back(all.begin(), all.end());
  }

  value_type fold(const size_type first, size_type last) const {
    assert(first <= last);
    assert(last <= size());
    if (first == last--) return empty_exception<value_semigroup>();
    const size_type fsec = first / M_logn, lsec = last / M_logn;
    const size_type fidx = first - fsec * M_logn, lidx = last - lsec * M_logn;
    if (fsec == lsec) return M_tree[fsec].fold(fidx, lidx + 1);
    const value_type fres = M_tree[fsec].fold(fidx, M_logn);
    const value_type lres = M_tree[lsec].fold(0, lidx + 1);
    if (fsec + 1 == lsec) return value_semigroup::operation(fres, lres);
    const value_type mres = M_tree.back().fold(fsec + 1, lsec);
    return value_semigroup::operation(value_semigroup::operation(fres, mres), lres);
  }

  void clear() {
    M_tree.clear();
    M_tree.shrink_to_fit();
    M_size = M_logn = 0;
  }
  size_type size() const {
    return M_size;
  }
};

/**
 * @title DST Tree
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

