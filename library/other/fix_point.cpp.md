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


# :heavy_check_mark: Lambda Recursion

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#795f3202b17cb6bc3d4b771d8c6c9eaf">other</a>
* <a href="{{ site.github.repository_url }}/blob/master/other/fix_point.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-03 12:07:15+09:00




## Required by

* :heavy_check_mark: <a href="../algebraic/fact_prime.cpp.html">Primes/Factors</a>
* :heavy_check_mark: <a href="../graph/dinic.cpp.html">Dinic</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/dinic.test.cpp.html">test/dinic.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/enumerate_divisors.test.cpp.html">test/enumerate_divisors.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/enumerate_factors.test.cpp.html">test/enumerate_factors.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <utility>

template <class Func>
struct fix_point_impl: private Func {
  explicit constexpr fix_point_impl(Func &&func): Func(std::forward<Func>(func)) { }
  template <class... Args>
  constexpr decltype(auto) operator () (Args &&... args) const {
    return Func::operator()(*this, std::forward<Args>(args)...);
  }
};

template <class Func>
constexpr decltype(auto) fix_point(Func &&func) {
  return fix_point_impl<Func>(std::forward<Func>(func));
}

/**
 * @title Lambda Recursion
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "other/fix_point.cpp"

#include <utility>

template <class Func>
struct fix_point_impl: private Func {
  explicit constexpr fix_point_impl(Func &&func): Func(std::forward<Func>(func)) { }
  template <class... Args>
  constexpr decltype(auto) operator () (Args &&... args) const {
    return Func::operator()(*this, std::forward<Args>(args)...);
  }
};

template <class Func>
constexpr decltype(auto) fix_point(Func &&func) {
  return fix_point_impl<Func>(std::forward<Func>(func));
}

/**
 * @title Lambda Recursion
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

