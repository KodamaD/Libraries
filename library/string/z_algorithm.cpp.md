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


# :heavy_check_mark: Z-Algorithm

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b45cffe084dd3d20d928bee85e7b0f21">string</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/z_algorithm.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-14 11:56:16+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/z_algorithm.test.cpp.html">test/z_algorithm.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cstddef>
#include <vector>

template <class InputIterator>
std::vector<size_t> z_algorithm(InputIterator first, InputIterator last) {
  const std::vector<typename InputIterator::value_type> str(first, last);
  const size_t size = str.size();
  std::vector<size_t> result(size);
  result[0] = size;
  size_t i = 1, j = 0;
  while (i < size) {
    while (i + j < size && str[i + j] == str[j]) {
      ++j;
    }
    result[i] = j;
    if (j == 0) { 
      ++i; 
      continue; 
    }
    size_t k = 1;
    while (i + k < size && k + result[k] < j) { 
      result[i + k] = result[k];
      ++k; 
    }
    i += k;
    j -= k;
  }
  return result;
}

/**
 * @title Z-Algorithm
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "string/z_algorithm.cpp"

#include <cstddef>
#include <vector>

template <class InputIterator>
std::vector<size_t> z_algorithm(InputIterator first, InputIterator last) {
  const std::vector<typename InputIterator::value_type> str(first, last);
  const size_t size = str.size();
  std::vector<size_t> result(size);
  result[0] = size;
  size_t i = 1, j = 0;
  while (i < size) {
    while (i + j < size && str[i + j] == str[j]) {
      ++j;
    }
    result[i] = j;
    if (j == 0) { 
      ++i; 
      continue; 
    }
    size_t k = 1;
    while (i + k < size && k + result[k] < j) { 
      result[i + k] = result[k];
      ++k; 
    }
    i += k;
    j -= k;
  }
  return result;
}

/**
 * @title Z-Algorithm
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

