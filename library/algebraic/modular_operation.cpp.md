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


# :question: Modular Operations

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c7f6ad568392380a8f4b4cecbaccb64c">algebraic</a>
* <a href="{{ site.github.repository_url }}/blob/master/algebraic/modular_operation.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-11 15:45:19+09:00




## Depends on

* :question: <a href="../other/random_number.cpp.html">Random Number</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/discrete_log.test.cpp.html">test/discrete_log.test.cpp</a>
* :x: <a href="../../verify/test/sqrt_mod.test.cpp.html">test/sqrt_mod.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp

#include "../other/random_number.cpp"

#include <cstdint>
#include <unordered_map>

template <class Modular>
Modular sqrt(const Modular value) {
  if (value == Modular(0)) return value;
  const auto mod = Modular::mod();
  if (mod == 2) return value;
  if (power(value, (mod - 1) >> 1) != Modular(1)) return Modular(0);
  if (mod % 4 == 3) return power(value, (mod + 1) >> 2);
  if (mod % 8 == 5) {
    if (power(value, (mod - 1) >> 2) == Modular(1)) return power(value, (mod + 3) >> 3);
    else return power(Modular(2), (mod - 1) >> 2) * power(value, (mod + 3) >> 3);
  }
  Modular f0, f1(1), g0(1), g1, D, tmp;
  while (true) {
    f0.extract() = random_number<uint32_t>(2, mod - 1);
    D = f0 * f0 - value;
    if (D == Modular(0)) return f0;
    if (power(D, (mod - 1) >> 1) == Modular(-1)) break;
  }
  for (uint32_t exp = (mod + 1) >> 1; exp > 0; exp >>= 1) {
    if (exp & 1) {
      tmp = g0 * f0 + D * (g1 * f1);
      g1 = g0 * f1 + g1 * f0;
      g0 = tmp;
    }
    tmp = f0 * f0 + D * (f1 * f1);
    f1 = Modular(2) * f0 * f1;
    f0 = tmp;
  }
  return g0;
}

template <class Modular>
uint64_t log(const Modular x, const Modular y) {
  static const auto gcd = [&](uint64_t a, uint64_t b) {
    while (b != 0) std::swap(a %= b, b);
    return a;
  };
  const auto mod = Modular::mod();
  const uint64_t base = uint64_t(x);
  uint64_t anti = uint64_t(y);
  uint64_t g = 1;
  for (uint64_t m = mod; m > 0; m >>= 1) (g *= base) %= mod;
  g = gcd(g, mod);
  uint64_t c = 0, t = 1;
  while (t % g != 0) {
    if (t == anti) return c;
    (t *= base) %= mod;
    ++c;
  }
  if (anti % g != 0) return mod;
  t /= g, anti /= g;
  const uint64_t n = mod / g;
  uint64_t h = 0, gs = 1;
  while (h * h < n) (gs *= base) %= n, ++h;
  std::unordered_map<uint64_t, uint64_t> bs;
  uint64_t s = 0, e = anti;
  while (s < h) {
    (e *= base) %= n;
    bs[e] = ++s;
  }
  s = 0, e = t;
  while (s < n) {
    (e *= gs) %= n;
    s += h;
    if (bs.count(e)) return c + s - bs[e];
  }
  return mod;
}

/**
 * @title Modular Operations
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "algebraic/modular_operation.cpp"

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
#line 3 "algebraic/modular_operation.cpp"

#line 5 "algebraic/modular_operation.cpp"
#include <unordered_map>

template <class Modular>
Modular sqrt(const Modular value) {
  if (value == Modular(0)) return value;
  const auto mod = Modular::mod();
  if (mod == 2) return value;
  if (power(value, (mod - 1) >> 1) != Modular(1)) return Modular(0);
  if (mod % 4 == 3) return power(value, (mod + 1) >> 2);
  if (mod % 8 == 5) {
    if (power(value, (mod - 1) >> 2) == Modular(1)) return power(value, (mod + 3) >> 3);
    else return power(Modular(2), (mod - 1) >> 2) * power(value, (mod + 3) >> 3);
  }
  Modular f0, f1(1), g0(1), g1, D, tmp;
  while (true) {
    f0.extract() = random_number<uint32_t>(2, mod - 1);
    D = f0 * f0 - value;
    if (D == Modular(0)) return f0;
    if (power(D, (mod - 1) >> 1) == Modular(-1)) break;
  }
  for (uint32_t exp = (mod + 1) >> 1; exp > 0; exp >>= 1) {
    if (exp & 1) {
      tmp = g0 * f0 + D * (g1 * f1);
      g1 = g0 * f1 + g1 * f0;
      g0 = tmp;
    }
    tmp = f0 * f0 + D * (f1 * f1);
    f1 = Modular(2) * f0 * f1;
    f0 = tmp;
  }
  return g0;
}

template <class Modular>
uint64_t log(const Modular x, const Modular y) {
  static const auto gcd = [&](uint64_t a, uint64_t b) {
    while (b != 0) std::swap(a %= b, b);
    return a;
  };
  const auto mod = Modular::mod();
  const uint64_t base = uint64_t(x);
  uint64_t anti = uint64_t(y);
  uint64_t g = 1;
  for (uint64_t m = mod; m > 0; m >>= 1) (g *= base) %= mod;
  g = gcd(g, mod);
  uint64_t c = 0, t = 1;
  while (t % g != 0) {
    if (t == anti) return c;
    (t *= base) %= mod;
    ++c;
  }
  if (anti % g != 0) return mod;
  t /= g, anti /= g;
  const uint64_t n = mod / g;
  uint64_t h = 0, gs = 1;
  while (h * h < n) (gs *= base) %= n, ++h;
  std::unordered_map<uint64_t, uint64_t> bs;
  uint64_t s = 0, e = anti;
  while (s < h) {
    (e *= base) %= n;
    bs[e] = ++s;
  }
  s = 0, e = t;
  while (s < n) {
    (e *= gs) %= n;
    s += h;
    if (bs.count(e)) return c + s - bs[e];
  }
  return mod;
}

/**
 * @title Modular Operations
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

