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


# :heavy_check_mark: Monoid Utility

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#795f3202b17cb6bc3d4b771d8c6c9eaf">other</a>
* <a href="{{ site.github.repository_url }}/blob/master/other/monoid.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-09 22:02:05+09:00




## Required by

* :heavy_check_mark: <a href="../container/disjoint_sparse_table.cpp.html">Disjoint Sparse Table</a>
* :heavy_check_mark: <a href="../container/dst_tree.cpp.html">DST Tree</a>
* :heavy_check_mark: <a href="../container/dual_segment_tree.cpp.html">Dual Segment Tree</a>
* :heavy_check_mark: <a href="../container/lazy_propagation_segment_tree.cpp.html">Lazy Propagation Segment Tree</a>
* :heavy_check_mark: <a href="../container/segment_tree.cpp.html">Segment Tree</a>
* :heavy_check_mark: <a href="../container/sliding_window_aggregation.cpp.html">Sliding Window Aggregation</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/dst_tree.test.cpp.html">test/dst_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/dual_segment_tree.test.cpp.html">test/dual_segment_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/lazy_propagation_segment_tree.test.cpp.html">test/lazy_propagation_segment_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/segment_tree.test.cpp.html">test/segment_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/sliding_window_aggregation.test.cpp.html">test/sliding_window_aggregation.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

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
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

