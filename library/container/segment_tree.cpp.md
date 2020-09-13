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


# :heavy_check_mark: Segment Tree

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5f0b6ebc4bea10285ba2b8a6ce78b863">container</a>
* <a href="{{ site.github.repository_url }}/blob/master/container/segment_tree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-13 16:51:07+09:00




## Depends on

* :heavy_check_mark: <a href="../other/bit_operation.cpp.html">Bit Operations</a>
* :heavy_check_mark: <a href="../other/monoid.cpp.html">Monoid Utility</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/segment_tree.test.cpp.html">test/segment_tree.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "../other/monoid.cpp"
#include "../other/bit_operation.cpp"

#include <cstddef>
#include <vector>
#include <iterator>
#include <algorithm>
#include <utility>
#include <type_traits>
#include <cassert>

template <class Monoid>
class segment_tree {
public:
  using structure    = Monoid;
  using value_monoid = typename Monoid::value_structure;
  using value_type   = typename Monoid::value_structure::type;
  using size_type    = size_t;

private:
  using fixed_value_monoid = fixed_monoid<value_monoid>;
  using fixed_value_type   = typename fixed_value_monoid::type;

  std::vector<fixed_value_type> M_tree;

  void M_fix_change(const size_type index) {
    M_tree[index] = fixed_value_monoid::operation(M_tree[index << 1 | 0], M_tree[index << 1 | 1]);
  }

public:
  segment_tree() = default;
  explicit segment_tree(const size_type size) { initialize(size); }
  template <class InputIterator>
  explicit segment_tree(InputIterator first, InputIterator last) { construct(first, last); }

  void initialize(const size_type size) {
    clear();
    M_tree.assign(size << 1, fixed_value_monoid::identity());
  }

  template <class InputIterator>
  void construct(InputIterator first, InputIterator last) {
    clear();
    const size_type size = std::distance(first, last);
    M_tree.reserve(size << 1);
    M_tree.assign(size, fixed_value_monoid::identity());
    std::transform(first, last, std::back_inserter(M_tree), [&](const value_type &value) {
      return fixed_value_monoid::convert(value);
    });
    for (size_type index = size - 1; index != 0; --index) {
      M_fix_change(index);
    }
  }

  void assign(size_type index, const value_type &value) {
    assert(index < size());
    index += size();
    M_tree[index] = fixed_value_monoid::convert(value);
    while (index != 1) {
      index >>= 1;
      M_fix_change(index);
    } 
  }

  value_type at(const size_type index) const { 
    assert(index < size());
    return fixed_value_monoid::revert(M_tree[index + size()]);
  }

  value_type fold(size_type first, size_type last) const {
    assert(first <= last);
    assert(last <= size());
    first += size();
    last += size();
    fixed_value_type fold_l = fixed_value_monoid::identity();
    fixed_value_type fold_r = fixed_value_monoid::identity();
    while (first != last) {
      if (first & 1) {
        fold_l = fixed_value_monoid::operation(fold_l, M_tree[first]);
        ++first;
      }
      if (last & 1) {
        --last;
        fold_r = fixed_value_monoid::operation(M_tree[last], fold_r);      
      }
      first >>= 1;
      last >>= 1;
    }
    return fixed_value_monoid::revert(fixed_value_monoid::operation(fold_l, fold_r));
  }

  template <bool ToRight = true, class Constraint, std::enable_if_t<ToRight>* = nullptr> 
  size_type satisfies(const size_type left, Constraint &&func) const {
    assert(left <= size());
    if (fixed_value_monoid::satisfies(std::forward<Constraint>(func), 
      fixed_value_monoid::identity())) return left;
    size_type first = left + size();
    size_type last = 2 * size();
    const size_type last_c = last;
    fixed_value_type fold = fixed_value_monoid::identity();
    const auto try_merge = [&](const size_type index) {
      fixed_value_type tmp = fixed_value_monoid::operation(fold, M_tree[index]);
      if (fixed_value_monoid::satisfies(std::forward<Constraint>(func), tmp)) return true;
      fold = std::move(tmp);
      return false;
    };
    const auto subtree = [&](size_type index) {
      while (index < size()) {
        index <<= 1;
        if (!try_merge(index)) ++index;
      }
      return index - size() + 1;
    };
    size_type story = 0;
    while (first < last) {
      if (first & 1) {
        if (try_merge(first)) return subtree(first);
        ++first;
      }
      first >>= 1;
      last >>= 1;
      ++story;
    }
    while (story--) {
      last = last_c >> story;
      if (last & 1) {
        --last;
        if (try_merge(last)) return subtree(last);
      }
    }
    return size() + 1;
  }

  template <bool ToRight = true, class Constraint, std::enable_if_t<!ToRight>* = nullptr> 
  size_type satisfies(const size_type right, Constraint &&func) const {
    assert(right <= size());
    if (fixed_value_monoid::satisfies(std::forward<Constraint>(func), 
      fixed_value_monoid::identity())) return right;
    size_type first = size();
    size_type last = right + size();
    const size_type first_c = first;
    fixed_value_type fold = fixed_value_monoid::identity();
    const auto try_merge = [&](const size_type index) {
      fixed_value_type tmp = fixed_value_monoid::operation(M_tree[index], fold);
      if (fixed_value_monoid::satisfies(std::forward<Constraint>(func), tmp)) return true;
      fold = std::move(tmp);
      return false;
    };
    const auto subtree = [&](size_type index) {
      while (index < size()) {
        index <<= 1;
        if (try_merge(index + 1)) ++index;
      }
      return index - size();
    };
    size_type story = 0;
    while (first < last) {
      if (first & 1) ++first;
      if (last & 1) {
        --last;
        if (try_merge(last)) return subtree(last);
      }
      first >>= 1;
      last >>= 1;
      ++story;
    }
    const size_type cover = bit_cover(first_c);
    while (story--) {
      first = (cover >> story) - ((cover - first_c) >> story);
      if (first & 1) {
        if (try_merge(first)) return subtree(first);
      }
    }
    return size_type(-1);
  }

  void clear() {
    M_tree.clear();
    M_tree.shrink_to_fit();
  }
  size_type size() const { 
    return M_tree.size() >> 1;
  }
};

/**
 * @title Segment Tree
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "container/segment_tree.cpp"

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
  using type = typename T::type;

  static constexpr type convert(const type &value) { return value; }
  static constexpr type revert(const type &value) { return value; }

  template <class Mapping, class Value, class... Args>
  static constexpr void operate(Mapping &&func, Value &value, const type &op, Args&&... args) {
    value = func(value, op, std::forward<Args>(args)...);
  }
  template <class Constraint>
  static constexpr bool satisfies(Constraint &&func, const type &value) {
    return func(value);
  }
};

template <class T>
class fixed_monoid_impl<T, false> {
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
    value = func(value, op.value, std::forward<Args>(args)...);
  }
  template <class Constraint>
  static constexpr bool satisfies(Constraint &&func, const type &value) {
    if (!value.state) return false;
    return func(value.value);
  }
};

template <class T>
using fixed_monoid = fixed_monoid_impl<T, has_identity<T>::value>;

/**
 * @title Monoid Utility
 */
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
#line 5 "container/segment_tree.cpp"

#line 7 "container/segment_tree.cpp"
#include <vector>
#include <iterator>
#include <algorithm>
#line 12 "container/segment_tree.cpp"
#include <cassert>

template <class Monoid>
class segment_tree {
public:
  using structure    = Monoid;
  using value_monoid = typename Monoid::value_structure;
  using value_type   = typename Monoid::value_structure::type;
  using size_type    = size_t;

private:
  using fixed_value_monoid = fixed_monoid<value_monoid>;
  using fixed_value_type   = typename fixed_value_monoid::type;

  std::vector<fixed_value_type> M_tree;

  void M_fix_change(const size_type index) {
    M_tree[index] = fixed_value_monoid::operation(M_tree[index << 1 | 0], M_tree[index << 1 | 1]);
  }

public:
  segment_tree() = default;
  explicit segment_tree(const size_type size) { initialize(size); }
  template <class InputIterator>
  explicit segment_tree(InputIterator first, InputIterator last) { construct(first, last); }

  void initialize(const size_type size) {
    clear();
    M_tree.assign(size << 1, fixed_value_monoid::identity());
  }

  template <class InputIterator>
  void construct(InputIterator first, InputIterator last) {
    clear();
    const size_type size = std::distance(first, last);
    M_tree.reserve(size << 1);
    M_tree.assign(size, fixed_value_monoid::identity());
    std::transform(first, last, std::back_inserter(M_tree), [&](const value_type &value) {
      return fixed_value_monoid::convert(value);
    });
    for (size_type index = size - 1; index != 0; --index) {
      M_fix_change(index);
    }
  }

  void assign(size_type index, const value_type &value) {
    assert(index < size());
    index += size();
    M_tree[index] = fixed_value_monoid::convert(value);
    while (index != 1) {
      index >>= 1;
      M_fix_change(index);
    } 
  }

  value_type at(const size_type index) const { 
    assert(index < size());
    return fixed_value_monoid::revert(M_tree[index + size()]);
  }

  value_type fold(size_type first, size_type last) const {
    assert(first <= last);
    assert(last <= size());
    first += size();
    last += size();
    fixed_value_type fold_l = fixed_value_monoid::identity();
    fixed_value_type fold_r = fixed_value_monoid::identity();
    while (first != last) {
      if (first & 1) {
        fold_l = fixed_value_monoid::operation(fold_l, M_tree[first]);
        ++first;
      }
      if (last & 1) {
        --last;
        fold_r = fixed_value_monoid::operation(M_tree[last], fold_r);      
      }
      first >>= 1;
      last >>= 1;
    }
    return fixed_value_monoid::revert(fixed_value_monoid::operation(fold_l, fold_r));
  }

  template <bool ToRight = true, class Constraint, std::enable_if_t<ToRight>* = nullptr> 
  size_type satisfies(const size_type left, Constraint &&func) const {
    assert(left <= size());
    if (fixed_value_monoid::satisfies(std::forward<Constraint>(func), 
      fixed_value_monoid::identity())) return left;
    size_type first = left + size();
    size_type last = 2 * size();
    const size_type last_c = last;
    fixed_value_type fold = fixed_value_monoid::identity();
    const auto try_merge = [&](const size_type index) {
      fixed_value_type tmp = fixed_value_monoid::operation(fold, M_tree[index]);
      if (fixed_value_monoid::satisfies(std::forward<Constraint>(func), tmp)) return true;
      fold = std::move(tmp);
      return false;
    };
    const auto subtree = [&](size_type index) {
      while (index < size()) {
        index <<= 1;
        if (!try_merge(index)) ++index;
      }
      return index - size() + 1;
    };
    size_type story = 0;
    while (first < last) {
      if (first & 1) {
        if (try_merge(first)) return subtree(first);
        ++first;
      }
      first >>= 1;
      last >>= 1;
      ++story;
    }
    while (story--) {
      last = last_c >> story;
      if (last & 1) {
        --last;
        if (try_merge(last)) return subtree(last);
      }
    }
    return size() + 1;
  }

  template <bool ToRight = true, class Constraint, std::enable_if_t<!ToRight>* = nullptr> 
  size_type satisfies(const size_type right, Constraint &&func) const {
    assert(right <= size());
    if (fixed_value_monoid::satisfies(std::forward<Constraint>(func), 
      fixed_value_monoid::identity())) return right;
    size_type first = size();
    size_type last = right + size();
    const size_type first_c = first;
    fixed_value_type fold = fixed_value_monoid::identity();
    const auto try_merge = [&](const size_type index) {
      fixed_value_type tmp = fixed_value_monoid::operation(M_tree[index], fold);
      if (fixed_value_monoid::satisfies(std::forward<Constraint>(func), tmp)) return true;
      fold = std::move(tmp);
      return false;
    };
    const auto subtree = [&](size_type index) {
      while (index < size()) {
        index <<= 1;
        if (try_merge(index + 1)) ++index;
      }
      return index - size();
    };
    size_type story = 0;
    while (first < last) {
      if (first & 1) ++first;
      if (last & 1) {
        --last;
        if (try_merge(last)) return subtree(last);
      }
      first >>= 1;
      last >>= 1;
      ++story;
    }
    const size_type cover = bit_cover(first_c);
    while (story--) {
      first = (cover >> story) - ((cover - first_c) >> story);
      if (first & 1) {
        if (try_merge(first)) return subtree(first);
      }
    }
    return size_type(-1);
  }

  void clear() {
    M_tree.clear();
    M_tree.shrink_to_fit();
  }
  size_type size() const { 
    return M_tree.size() >> 1;
  }
};

/**
 * @title Segment Tree
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

