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


# :warning: Randomized Queue

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5f0b6ebc4bea10285ba2b8a6ce78b863">container</a>
* <a href="{{ site.github.repository_url }}/blob/master/container/randomized_queue.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-05 19:22:30+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <iterator>
#include <algorithm>

template <class T>
class randomized_queue {
public:
  using value_type = T;
  using size_type = size_t;

  static uint64_t engine() {
    static uint64_t current = 7511168;
    current ^= (current << 9);
    current ^= (current >> 7);
    return current;
  }
  
private:
  std::vector<value_type> M_data;

public:
  randomized_queue() = default;
  template <class InputIterator>
  explicit randomized_queue(InputIterator first, InputIterator last) { construct(first, last); }

  template <class InputIterator>
  void construct(InputIterator first, InputIterator last) { 
    clear();
    const size_type size = std::distance(first, last);
    M_data.reserve(size);
    std::copy(first, last, std::back_inserter(M_data));
  }

  void shuffle() {
    std::swap(M_data.back(), M_data[engine() % M_data.size()]);
  }

  value_type front() const {
    return M_data.back();
  }
  bool empty() const {
    return M_data.empty();
  }
  size_type size() const {
    return M_data.size();
  }

  void push(const value_type &val) {
    M_data.push_back(val);
    shuffle();
  }
  void pop() {
    M_data.pop_back();
    if (!M_data.empty()) {
      shuffle();
    }
  }
  void clear() {
    M_data.clear();
    M_data.shrink_to_fit();
  }

};

/**
 * @title Randomized Queue
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "container/randomized_queue.cpp"

#include <cstddef>
#include <cstdint>
#include <vector>
#include <iterator>
#include <algorithm>

template <class T>
class randomized_queue {
public:
  using value_type = T;
  using size_type = size_t;

  static uint64_t engine() {
    static uint64_t current = 7511168;
    current ^= (current << 9);
    current ^= (current >> 7);
    return current;
  }
  
private:
  std::vector<value_type> M_data;

public:
  randomized_queue() = default;
  template <class InputIterator>
  explicit randomized_queue(InputIterator first, InputIterator last) { construct(first, last); }

  template <class InputIterator>
  void construct(InputIterator first, InputIterator last) { 
    clear();
    const size_type size = std::distance(first, last);
    M_data.reserve(size);
    std::copy(first, last, std::back_inserter(M_data));
  }

  void shuffle() {
    std::swap(M_data.back(), M_data[engine() % M_data.size()]);
  }

  value_type front() const {
    return M_data.back();
  }
  bool empty() const {
    return M_data.empty();
  }
  size_type size() const {
    return M_data.size();
  }

  void push(const value_type &val) {
    M_data.push_back(val);
    shuffle();
  }
  void pop() {
    M_data.pop_back();
    if (!M_data.empty()) {
      shuffle();
    }
  }
  void clear() {
    M_data.clear();
    M_data.shrink_to_fit();
  }

};

/**
 * @title Randomized Queue
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

