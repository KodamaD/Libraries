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


# :heavy_check_mark: Factors/Divisors

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c7f6ad568392380a8f4b4cecbaccb64c">algebraic</a>
* <a href="{{ site.github.repository_url }}/blob/master/algebraic/fact_prime.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-13 16:51:07+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/enumerate_factors.test.cpp.html">test/enumerate_factors.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cstddef>
#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <type_traits>

template <class T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
std::vector<std::pair<T, size_t>> factorize(T x) {
  assert(x > 0);
  if (x == 1) return { };
  std::vector<std::pair<T, size_t>> res;
  for (T i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
      res.emplace_back(i, 0);
      while (x % i == 0) {
        res.back().second++;
        x /= i;
      }
    }
  }
  if (x > 1) {
    res.emplace_back(x, 1);
  }
  return res;
}

template <class T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
std::vector<T> divisors(const T x) {
  std::vector<T> small, big;
  for (T i = 1; i * i <= x; ++i) {
    if (x % i == 0) {
      small.push_back(i);
      if (i * i != x) {
        big.push_back(x / i);
      }
    }
  }
  small.reserve(small.size() + big.size());
  std::copy(big.rbegin(), big.rend(), std::back_inserter(small));
  return small;
}

/**
 * @title Factors/Divisors
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "algebraic/fact_prime.cpp"

#include <cstddef>
#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <type_traits>

template <class T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
std::vector<std::pair<T, size_t>> factorize(T x) {
  assert(x > 0);
  if (x == 1) return { };
  std::vector<std::pair<T, size_t>> res;
  for (T i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
      res.emplace_back(i, 0);
      while (x % i == 0) {
        res.back().second++;
        x /= i;
      }
    }
  }
  if (x > 1) {
    res.emplace_back(x, 1);
  }
  return res;
}

template <class T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
std::vector<T> divisors(const T x) {
  std::vector<T> small, big;
  for (T i = 1; i * i <= x; ++i) {
    if (x % i == 0) {
      small.push_back(i);
      if (i * i != x) {
        big.push_back(x / i);
      }
    }
  }
  small.reserve(small.size() + big.size());
  std::copy(big.rbegin(), big.rend(), std::back_inserter(small));
  return small;
}

/**
 * @title Factors/Divisors
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

