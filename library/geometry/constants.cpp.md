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


# :warning: Geometric Constants

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed7daeb157cd9b31e53896ad3c771a26">geometry</a>
* <a href="{{ site.github.repository_url }}/blob/master/geometry/constants.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-11 19:42:18+09:00




## Required by

* :warning: <a href="figures.cpp.html">2D Figures</a>
* :warning: <a href="polygon.cpp.html">2D Polygons</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cmath>

template <class T>
struct real_constant;

template <>
struct real_constant<double> {
  using value_type = double;
  static constexpr value_type infinity() { return 1e9; }
  static constexpr value_type epsilon() { return 1e-9; }
  static constexpr value_type pi() { return std::acos(-1.0); }
};

template <>
struct real_constant<long double> {
  using value_type = long double;
  static constexpr value_type infinity() { return 1e18; }
  static constexpr value_type epsilon() { return 1e-10; }
  static constexpr value_type pi() { return std::acos(-1.0L); }
};

template <>
struct real_constant<__float128> {
  using value_type = __float128;
  static constexpr value_type infinity() { return 1e18; }
  static constexpr value_type epsilon() { return 1e-10; }
  static constexpr value_type pi() { return std::acos(-1.0L); }
};

template <>
struct real_constant<int32_t> {
  using value_type = int32_t;
  static constexpr value_type infinity() { return 1e9; }
  static constexpr value_type epsilon() { return 1; }
};

template <>
struct real_constant<int64_t> {
  using value_type = int64_t;
  static constexpr value_type infinity() { return 1e18; }
  static constexpr value_type epsilon() { return 1; }
};

template <class T, class U>
bool leq(T x, U y) {
  return x - y < real_constant<T>::epsilon();
}
template <class T, class U>
bool geq(T x, U y) {
  return y - x < real_constant<T>::epsilon();
}
template <class T, class U>
bool equal(T x, U y) {
  return leq(x, y) && geq(x, y);
}

template <class T>
T to_radian(T deg) {
  return deg * real_constant<T>::pi() / 180;
}
template <class T>
T to_degree(T rad) {
  return rad / real_constant<T>::pi() * 180;
}

/**
 * @title Geometric Constants
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "geometry/constants.cpp"

#include <cmath>

template <class T>
struct real_constant;

template <>
struct real_constant<double> {
  using value_type = double;
  static constexpr value_type infinity() { return 1e9; }
  static constexpr value_type epsilon() { return 1e-9; }
  static constexpr value_type pi() { return std::acos(-1.0); }
};

template <>
struct real_constant<long double> {
  using value_type = long double;
  static constexpr value_type infinity() { return 1e18; }
  static constexpr value_type epsilon() { return 1e-10; }
  static constexpr value_type pi() { return std::acos(-1.0L); }
};

template <>
struct real_constant<__float128> {
  using value_type = __float128;
  static constexpr value_type infinity() { return 1e18; }
  static constexpr value_type epsilon() { return 1e-10; }
  static constexpr value_type pi() { return std::acos(-1.0L); }
};

template <>
struct real_constant<int32_t> {
  using value_type = int32_t;
  static constexpr value_type infinity() { return 1e9; }
  static constexpr value_type epsilon() { return 1; }
};

template <>
struct real_constant<int64_t> {
  using value_type = int64_t;
  static constexpr value_type infinity() { return 1e18; }
  static constexpr value_type epsilon() { return 1; }
};

template <class T, class U>
bool leq(T x, U y) {
  return x - y < real_constant<T>::epsilon();
}
template <class T, class U>
bool geq(T x, U y) {
  return y - x < real_constant<T>::epsilon();
}
template <class T, class U>
bool equal(T x, U y) {
  return leq(x, y) && geq(x, y);
}

template <class T>
T to_radian(T deg) {
  return deg * real_constant<T>::pi() / 180;
}
template <class T>
T to_degree(T rad) {
  return rad / real_constant<T>::pi() * 180;
}

/**
 * @title Geometric Constants
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

