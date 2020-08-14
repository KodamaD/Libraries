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


# :heavy_check_mark: test/z_algorithm.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/z_algorithm.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-14 11:56:16+09:00


* see: <a href="https://judge.yosupo.jp/problem/zalgorithm">https://judge.yosupo.jp/problem/zalgorithm</a>


## Depends on

* :heavy_check_mark: <a href="../../library/string/z_algorithm.cpp.html">Z-Algorithm</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp

#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../string/z_algorithm.cpp"

#include <cstddef>
#include <vector>
#include <string>
#include <iostream>

int main() {
  std::string S;
  std::cin >> S;
  auto ans = z_algorithm(S.begin(), S.end());
  for (size_t i = 0; i < S.size(); ++i) {
    std::cout << ans[i];
    std::cout << (i + 1 == S.size() ? '\n' : ' ');
  }
  return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/z_algorithm.test.cpp"

#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

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
#line 5 "test/z_algorithm.test.cpp"

#line 8 "test/z_algorithm.test.cpp"
#include <string>
#include <iostream>

int main() {
  std::string S;
  std::cin >> S;
  auto ans = z_algorithm(S.begin(), S.end());
  for (size_t i = 0; i < S.size(); ++i) {
    std::cout << ans[i];
    std::cout << (i + 1 == S.size() ? '\n' : ' ');
  }
  return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

