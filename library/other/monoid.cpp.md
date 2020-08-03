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


# :heavy_check_mark: other/monoid.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#795f3202b17cb6bc3d4b771d8c6c9eaf">other</a>
* <a href="{{ site.github.repository_url }}/blob/master/other/monoid.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-03 17:09:36+09:00




## Required by

* :heavy_check_mark: <a href="../container/dual_segment_tree.cpp.html">Dual Segment Tree</a>
* :heavy_check_mark: <a href="../container/lazy_propagation_segment_tree.cpp.html">Lazy Propagation Segment Tree</a>
* :heavy_check_mark: <a href="../container/segment_tree.cpp.html">Segment Tree</a>
* :heavy_check_mark: <a href="../container/sliding_window_aggregation.cpp.html">Sliding Window Aggregation</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/dual_segment_tree.test.cpp.html">test/dual_segment_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/lazy_propagation_segment_tree.test.cpp.html">test/lazy_propagation_segment_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/segment_tree.test.cpp.html">test/segment_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/sliding_window_aggregation.test.cpp.html">test/sliding_window_aggregation.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp

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

/**
 * Monoid Utility
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
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

/**
 * Monoid Utility
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

