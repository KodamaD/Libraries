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
    - Last commit date: 2020-08-03 12:07:15+09:00




## Depends on

* :question: <a href="../other/monoid.cpp.html">other/monoid.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/segment_tree.test.cpp.html">test/segment_tree.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "../other/monoid.cpp"
#include <cstddef>
#include <vector>
#include <iterator>
#include <algorithm>

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
    index += size();
    M_tree[index] = fixed_value_monoid::convert(value);
    while (index != 1) {
      index >>= 1;
      M_fix_change(index);
    } 
  }

  value_type at(const size_type index) const { 
    return fixed_value_monoid::revert(M_tree[index + size()]);
  }

  value_type fold(size_type first, size_type last) const {
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
      last  >>= 1;
    }
    return fixed_value_monoid::revert(fixed_value_monoid::operation(fold_l, fold_r));
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

#line 1 "other/monoid.cpp"

#include <type_traits>
#include <utility>

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
  static constexpr typename T::type revert(const type &value) { return value.value; }

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
    return T::opration(val, op, std::forward<Args>(args)...);
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
#line 4 "container/segment_tree.cpp"
#include <cstddef>
#include <vector>
#include <iterator>
#include <algorithm>

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
    index += size();
    M_tree[index] = fixed_value_monoid::convert(value);
    while (index != 1) {
      index >>= 1;
      M_fix_change(index);
    } 
  }

  value_type at(const size_type index) const { 
    return fixed_value_monoid::revert(M_tree[index + size()]);
  }

  value_type fold(size_type first, size_type last) const {
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
      last  >>= 1;
    }
    return fixed_value_monoid::revert(fixed_value_monoid::operation(fold_l, fold_r));
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
