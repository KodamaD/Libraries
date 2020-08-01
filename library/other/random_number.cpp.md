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


# :warning: Random Number

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#795f3202b17cb6bc3d4b771d8c6c9eaf">other</a>
* <a href="{{ site.github.repository_url }}/blob/master/other/random_number.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-01 22:24:08+09:00




## Required by

* :warning: <a href="../string/rolling_hash.cpp.html">Rolling Hash</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp

#include <cstdint>
#include <random>
#include <chrono>
#include <array>

uint64_t engine() {
  const auto rotate = [](const uint64_t x, const size_t k) {
    return (x << k) | (x >> (64 - k));
  };
  static auto array = [] {
    uint64_t seed = std::chrono::system_clock::now().time_since_epoch().count();
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
Integer random_integer(Integer lower, Integer upper) {
  static std::default_random_engine gen(engine());
  return std::uniform_int_distribution<Integer>(lower, upper)(gen);
}

template <class Real>
Real random_real(Real lower, Real upper) {
  static std::default_random_engine gen(engine());
  return std::uniform_real_distribution<Real>(lower, upper)(gen);
}

/** 
 * @title Random Number
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "other/random_number.cpp"

#include <cstdint>
#include <random>
#include <chrono>
#include <array>

uint64_t engine() {
  const auto rotate = [](const uint64_t x, const size_t k) {
    return (x << k) | (x >> (64 - k));
  };
  static auto array = [] {
    uint64_t seed = std::chrono::system_clock::now().time_since_epoch().count();
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
Integer random_integer(Integer lower, Integer upper) {
  static std::default_random_engine gen(engine());
  return std::uniform_int_distribution<Integer>(lower, upper)(gen);
}

template <class Real>
Real random_real(Real lower, Real upper) {
  static std::default_random_engine gen(engine());
  return std::uniform_real_distribution<Real>(lower, upper)(gen);
}

/** 
 * @title Random Number
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

