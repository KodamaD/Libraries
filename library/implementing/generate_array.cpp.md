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


# :warning: Random Array Generator

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#be68540dfa000a0fb38be40d32259215">implementing</a>
* <a href="{{ site.github.repository_url }}/blob/master/implementing/generate_array.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-20 23:34:30+09:00




## Depends on

* :heavy_check_mark: <a href="../other/random_number.cpp.html">Random Number</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp

#include "../other/random_number.cpp"

#include <cstddef>
#include <random>
#include <algorithm>
#include <vector>

template <class RandomAccessIterator>
void shuffle(RandomAccessIterator first, RandomAccessIterator last) {
  static std::default_random_engine gen(engine());
  std::shuffle(first, last, gen);
}

template <class T>
std::vector<T> fixed_range_array(const size_t size, const T lower, const T upper) {
  std::vector<T> res(size);
  for (auto &x: res) {
    x = random_number(lower, upper);
  }
  return res;
}

template <class T>
std::vector<T> fixed_sum_array(const size_t size, const T sum) {
  auto vec = fixed_range_array(size - 1, T(0), sum);
  vec.push_back(T(0));
  vec.push_back(sum);
  std::sort(vec.begin(), vec.end());
  std::vector<T> res(size);
  for (size_t i = 0; i < size; ++i) {
    res[i] = vec[i + 1] - vec[i];
  }
  return res;
}

std::vector<size_t> random_permutation(const size_t size) {
  std::vector<size_t> res(size);
  std::iota(res.begin(), res.end(), 0);
  shuffle(res.begin(), res.end());
  return res;
}

/**
 * @title Random Array Generator
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "implementing/generate_array.cpp"

#line 2 "other/random_number.cpp"

#include <cstdint>
#include <random>
#include <chrono>
#include <array>
#include <type_traits>

uint64_t engine() {
  static const auto rotate = [](const uint64_t x, const size_t k) {
    return (x << k) | (x >> (64 - k));
  };
  static auto array = [] {
    uint64_t seed = static_cast<uint64_t>(std::chrono::system_clock::now().time_since_epoch().count());
    std::array<uint64_t, 4> res{};
    for (size_t index = 0; index < 4; index++) {
      uint64_t value = (seed += 0x9e3779b97f4a7c15);
      value = (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9;
      value = (value ^ (value >> 27)) * 0x94d049bb133111eb;
      res[index] = value ^ (value >> 31);
    }
    return res;
  }();
  const uint64_t result = rotate(array[1] * 5, 7) * 9;
  const uint64_t old_value = array[1] << 17;
  array[2] ^= array[0];
  array[3] ^= array[1];
  array[1] ^= array[2];
  array[0] ^= array[3];
  array[2] ^= old_value;
  array[3] = rotate(array[3], 45);
  return result;
}

template <class Integer>
typename std::enable_if<std::is_integral<Integer>::value, Integer>::type random_number(Integer lower, Integer upper) {
  static std::default_random_engine gen(engine());
  return std::uniform_int_distribution<Integer>(lower, upper)(gen);
}

template <class Real>
typename std::enable_if<!std::is_integral<Real>::value, Real>::type random_number(Real lower, Real upper) {
  static std::default_random_engine gen(engine());
  return std::uniform_real_distribution<Real>(lower, upper)(gen);
}

/** 
 * @title Random Number
 */
#line 3 "implementing/generate_array.cpp"

#include <cstddef>
#line 6 "implementing/generate_array.cpp"
#include <algorithm>
#include <vector>

template <class RandomAccessIterator>
void shuffle(RandomAccessIterator first, RandomAccessIterator last) {
  static std::default_random_engine gen(engine());
  std::shuffle(first, last, gen);
}

template <class T>
std::vector<T> fixed_range_array(const size_t size, const T lower, const T upper) {
  std::vector<T> res(size);
  for (auto &x: res) {
    x = random_number(lower, upper);
  }
  return res;
}

template <class T>
std::vector<T> fixed_sum_array(const size_t size, const T sum) {
  auto vec = fixed_range_array(size - 1, T(0), sum);
  vec.push_back(T(0));
  vec.push_back(sum);
  std::sort(vec.begin(), vec.end());
  std::vector<T> res(size);
  for (size_t i = 0; i < size; ++i) {
    res[i] = vec[i + 1] - vec[i];
  }
  return res;
}

std::vector<size_t> random_permutation(const size_t size) {
  std::vector<size_t> res(size);
  std::iota(res.begin(), res.end(), 0);
  shuffle(res.begin(), res.end());
  return res;
}

/**
 * @title Random Array Generator
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

