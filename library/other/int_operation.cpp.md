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


# :warning: Integer Operations

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#795f3202b17cb6bc3d4b771d8c6c9eaf">other</a>
* <a href="{{ site.github.repository_url }}/blob/master/other/int_operation.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-13 16:51:07+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cstdint>
#include <type_traits>
#include <limits>

template <class T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
constexpr T isqrt(const T x) {
  T ok = 0, ng = std::numeric_limits<T>::max();
  while (ng - ok > 1) {
    const T md = ok + ((ng - ok) >> 1);
    (md > x / md ? ng : ok) = md;
  }
  return ok;
}

template <class T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
constexpr T ipower(T x, uint64_t e) {
  T res = 1;
  while (e > 0) {
    if (e & 1) res *= x;
    e >>= 1;
    if (e > 0) x *= x;
  }
  return res;
}

/**
 * @title Integer Operations
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "other/int_operation.cpp"

#include <cstdint>
#include <type_traits>
#include <limits>

template <class T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
constexpr T isqrt(const T x) {
  T ok = 0, ng = std::numeric_limits<T>::max();
  while (ng - ok > 1) {
    const T md = ok + ((ng - ok) >> 1);
    (md > x / md ? ng : ok) = md;
  }
  return ok;
}

template <class T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
constexpr T ipower(T x, uint64_t e) {
  T res = 1;
  while (e > 0) {
    if (e & 1) res *= x;
    e >>= 1;
    if (e > 0) x *= x;
  }
  return res;
}

/**
 * @title Integer Operations
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

