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


# :warning: Reverser

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#795f3202b17cb6bc3d4b771d8c6c9eaf">other</a>
* <a href="{{ site.github.repository_url }}/blob/master/other/rev.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-01 22:24:08+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <type_traits>
#include <iterator>
#include <utility>

template <class T>
class rev_impl {
public:
  using iterator = typename std::decay<T>::type::reverse_iterator;

private:
  const iterator M_begin;
  const iterator M_end;

public:
  constexpr rev_impl(T &&cont) noexcept: M_begin(std::rbegin(cont)), M_end(std::rend(cont)) { }
  constexpr iterator begin() const noexcept { return M_begin; }
  constexpr iterator end() const noexcept { return M_end; }

};

template <class T>
constexpr decltype(auto) rev(T &&cont) {
  return rev_impl<T>(std::forward<T>(cont));
}

/**
 * @title Reverser
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "other/rev.cpp"

#include <type_traits>
#include <iterator>
#include <utility>

template <class T>
class rev_impl {
public:
  using iterator = typename std::decay<T>::type::reverse_iterator;

private:
  const iterator M_begin;
  const iterator M_end;

public:
  constexpr rev_impl(T &&cont) noexcept: M_begin(std::rbegin(cont)), M_end(std::rend(cont)) { }
  constexpr iterator begin() const noexcept { return M_begin; }
  constexpr iterator end() const noexcept { return M_end; }

};

template <class T>
constexpr decltype(auto) rev(T &&cont) {
  return rev_impl<T>(std::forward<T>(cont));
}

/**
 * @title Reverser
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

