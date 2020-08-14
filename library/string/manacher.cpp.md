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


# :warning: Manacher

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b45cffe084dd3d20d928bee85e7b0f21">string</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/manacher.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-14 11:56:16+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <iterator>

template <class InputIterator>
class manacher_impl {
public:
  using value_type = typename InputIterator::value_type;

public:
  std::vector<size_t> odd, even;

  explicit manacher_impl(InputIterator first, InputIterator last, const value_type &never) {
    const size_t size = std::distance(first, last);
    odd.resize(size);
    even.resize(size - 1);
    std::vector<value_type> str;
    str.reserve(2 * size + 1);
    for (; first != last; ++first) {
      str.push_back(never);
      str.push_back(*first);
    }
    str.push_back(never);
    std::vector<int32_t> calc(str.size());
    int32_t i = 0, j = 0;
    while (i < (int32_t) str.size()) {
      while (i - j >= 0 && i + j < (int32_t) str.size() && str[i - j] == str[i + j]) {
        ++j;
      }
      calc[i] = j;
      int32_t k = 1;
      while (i - k >= 0 && k + calc[i - k] < j) {
        calc[i + k] = calc[i - k];
        ++k;
      }
      i += k;
      j -= k;
    }
    for (size_t k = 1; k + 1 < str.size(); ++k) {
      if (k % 2 == 1) {
        odd[k / 2] = calc[k] - 1;
      }
      else {
        even[k / 2 - 1] = calc[k] - 1;
      }
    }
  }

};

template <class InputIterator>
manacher_impl<InputIterator> manacher(InputIterator first, InputIterator last, const typename InputIterator::value_type &never) {
  return manacher_impl<InputIterator>(first, last, never);
}

/**
 * @title Manacher
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "string/manacher.cpp"

#include <cstddef>
#include <cstdint>
#include <vector>
#include <iterator>

template <class InputIterator>
class manacher_impl {
public:
  using value_type = typename InputIterator::value_type;

public:
  std::vector<size_t> odd, even;

  explicit manacher_impl(InputIterator first, InputIterator last, const value_type &never) {
    const size_t size = std::distance(first, last);
    odd.resize(size);
    even.resize(size - 1);
    std::vector<value_type> str;
    str.reserve(2 * size + 1);
    for (; first != last; ++first) {
      str.push_back(never);
      str.push_back(*first);
    }
    str.push_back(never);
    std::vector<int32_t> calc(str.size());
    int32_t i = 0, j = 0;
    while (i < (int32_t) str.size()) {
      while (i - j >= 0 && i + j < (int32_t) str.size() && str[i - j] == str[i + j]) {
        ++j;
      }
      calc[i] = j;
      int32_t k = 1;
      while (i - k >= 0 && k + calc[i - k] < j) {
        calc[i + k] = calc[i - k];
        ++k;
      }
      i += k;
      j -= k;
    }
    for (size_t k = 1; k + 1 < str.size(); ++k) {
      if (k % 2 == 1) {
        odd[k / 2] = calc[k] - 1;
      }
      else {
        even[k / 2 - 1] = calc[k] - 1;
      }
    }
  }

};

template <class InputIterator>
manacher_impl<InputIterator> manacher(InputIterator first, InputIterator last, const typename InputIterator::value_type &never) {
  return manacher_impl<InputIterator>(first, last, never);
}

/**
 * @title Manacher
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

