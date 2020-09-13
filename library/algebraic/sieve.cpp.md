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


# :warning: algebraic/sieve.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c7f6ad568392380a8f4b4cecbaccb64c">algebraic</a>
* <a href="{{ site.github.repository_url }}/blob/master/algebraic/sieve.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-13 16:51:07+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <array>
#include <vector>
#include <utility>
#include <cassert>
#include <numeric>
#include <type_traits>

template <size_t N>
class sieve {
private:
  std::array<uint32_t, N + 1> M_smallest;

public:
  sieve() {
    std::iota(M_smallest.begin(), M_smallest.end(), (uint32_t) 0);
    for (uint32_t i = 2; i <= N; ++i) {
      if (M_smallest[i] == i) {
        for (uint32_t j = i + i; j <= N; j += i) {
          if (M_smallest[j] == j) {
            M_smallest[j] = i;
          }
        }
      }
    }
  }

  template <class T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
  std::vector<std::pair<T, size_t>> factorize(T x) {
    assert(x > 0);
    assert((size_t) x <= N);
    std::vector<std::pair<T, size_t>> res;
    while (x != 1) {
      const auto cur = M_smallest[x];
      res.emplace_back((T) cur, 0);
      while (M_smallest[x] == cur) {
        res.back().second++;
        x /= cur;
      }
    }
    return res;
  }
  bool operator [] (const size_t n) const {
    if (n <= 1) return false;
    assert(n <= N);
    return (M_smallest[n] == (uint32_t) n);
  }
};

/**
 * Sieve of Eratosthenes
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "algebraic/sieve.cpp"

#include <cstddef>
#include <cstdint>
#include <array>
#include <vector>
#include <utility>
#include <cassert>
#include <numeric>
#include <type_traits>

template <size_t N>
class sieve {
private:
  std::array<uint32_t, N + 1> M_smallest;

public:
  sieve() {
    std::iota(M_smallest.begin(), M_smallest.end(), (uint32_t) 0);
    for (uint32_t i = 2; i <= N; ++i) {
      if (M_smallest[i] == i) {
        for (uint32_t j = i + i; j <= N; j += i) {
          if (M_smallest[j] == j) {
            M_smallest[j] = i;
          }
        }
      }
    }
  }

  template <class T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
  std::vector<std::pair<T, size_t>> factorize(T x) {
    assert(x > 0);
    assert((size_t) x <= N);
    std::vector<std::pair<T, size_t>> res;
    while (x != 1) {
      const auto cur = M_smallest[x];
      res.emplace_back((T) cur, 0);
      while (M_smallest[x] == cur) {
        res.back().second++;
        x /= cur;
      }
    }
    return res;
  }
  bool operator [] (const size_t n) const {
    if (n <= 1) return false;
    assert(n <= N);
    return (M_smallest[n] == (uint32_t) n);
  }
};

/**
 * Sieve of Eratosthenes
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

