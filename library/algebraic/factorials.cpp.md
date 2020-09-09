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


# :heavy_check_mark: Factorial

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c7f6ad568392380a8f4b4cecbaccb64c">algebraic</a>
* <a href="{{ site.github.repository_url }}/blob/master/algebraic/factorials.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-09 18:08:09+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/factorials.test.cpp.html">test/factorials.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cstddef>
#include <array>
#include <cassert>

template <class T, size_t N>
class factorials {
public:
  using value_type = T;

public:
  std::array<value_type, N + 1> fact{};
  std::array<value_type, N + 1> fact_inv{};

  factorials() {
    fact.front() = value_type(1);
    for (size_t i = 1; i <= N; ++i) {
      fact[i] = fact[i - 1] * value_type(i);
    }
    fact_inv.back() = ~fact.back();
    for (size_t i = N; i > 0; --i) {
      fact_inv[i - 1] = fact_inv[i] * value_type(i);
    }
  }

  value_type operator () (size_t n, size_t r) const {
    assert(n <= N);
    assert(n >= r);
    return fact[n] * fact_inv[n - r] * fact_inv[r];
  }
};

/**
 * @title Factorial
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "algebraic/factorials.cpp"

#include <cstddef>
#include <array>
#include <cassert>

template <class T, size_t N>
class factorials {
public:
  using value_type = T;

public:
  std::array<value_type, N + 1> fact{};
  std::array<value_type, N + 1> fact_inv{};

  factorials() {
    fact.front() = value_type(1);
    for (size_t i = 1; i <= N; ++i) {
      fact[i] = fact[i - 1] * value_type(i);
    }
    fact_inv.back() = ~fact.back();
    for (size_t i = N; i > 0; --i) {
      fact_inv[i - 1] = fact_inv[i] * value_type(i);
    }
  }

  value_type operator () (size_t n, size_t r) const {
    assert(n <= N);
    assert(n >= r);
    return fact[n] * fact_inv[n - r] * fact_inv[r];
  }
};

/**
 * @title Factorial
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

