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


# :warning: test/discrete_log.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/discrete_log.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-13 16:51:07+09:00


* see: <a href="https://judge.yosupo.jp/problem/discrete_logarithm_mod">https://judge.yosupo.jp/problem/discrete_logarithm_mod</a>


## Depends on

* :heavy_check_mark: <a href="../algebraic/modular.cpp.html">Static Modint</a>
* :warning: <a href="../algebraic/modular_operation.cpp.html">Modular Operations</a>
* :warning: <a href="../other/random_number.cpp.html">Random Number</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp

#define PROBLEM "https://judge.yosupo.jp/problem/discrete_logarithm_mod"

#include "../algebraic/modular.cpp"
#include "../algebraic/modular_operation.cpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

int main() {
  size_t Q;
  std::cin >> Q;
  while (Q--) {
    uint32_t x, y;
    std::cin >> x >> y >> runtime_mod::value();
    const auto ans = log(rmint32_t(x), rmint32_t(y));
    if (ans == runtime_mod::value()) {
      std::cout << "-1\n";
    }
    else {
      std::cout << ans << '\n';
    }
  }
  return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/discrete_log.cpp"

#define PROBLEM "https://judge.yosupo.jp/problem/discrete_logarithm_mod"

#line 2 "algebraic/modular.cpp"

#include <cstdint>
#include <iostream>

template <uint32_t Mod>
class static_modint {
public:
  using value_type = uint32_t;
  using cover_type = uint64_t;

  template <class T>
  static constexpr value_type normalize(T value_) noexcept {
    if (value_ < 0) {
      value_ = -value_;
      value_ %= Mod;
      if (value_ == 0) return 0;
      return Mod - value_;
    }
    return value_ % Mod;
  }

private:
  value_type value;

public:
  constexpr static_modint() noexcept : value(0) { }
  template <class T>
  explicit constexpr static_modint(T value_) noexcept : value(normalize(value_)) { }
  template <class T>
  explicit constexpr operator T() const noexcept { return static_cast<T>(value); }

  constexpr value_type get() const noexcept { return value; }
  constexpr value_type &extract() noexcept { return value; }
  constexpr static_modint operator - () const noexcept { return static_modint(Mod - value); }
  constexpr static_modint operator ~ () const noexcept { return inverse(*this); }

  constexpr static_modint operator + (const static_modint &rhs) const noexcept { return static_modint(*this) += rhs; }
  constexpr static_modint& operator += (const static_modint &rhs) noexcept { 
    if ((value += rhs.value) >= Mod) value -= Mod; 
    return *this; 
  }

  constexpr static_modint operator - (const static_modint &rhs) const noexcept { return static_modint(*this) -= rhs; }
  constexpr static_modint& operator -= (const static_modint &rhs) noexcept { 
    if ((value += Mod - rhs.value) >= Mod) value -= Mod; 
    return *this; 
  }

  constexpr static_modint operator * (const static_modint &rhs) const noexcept { return static_modint(*this) *= rhs; }
  constexpr static_modint& operator *= (const static_modint &rhs) noexcept { 
    value = (cover_type) value * rhs.value % Mod;
    return *this;
  }

  constexpr static_modint operator / (const static_modint &rhs) const noexcept { return static_modint(*this) /= rhs; }
  constexpr static_modint& operator /= (const static_modint &rhs) noexcept { return (*this) *= inverse(rhs); }

  constexpr bool zero() const noexcept { return value == 0; }
  constexpr bool operator == (const static_modint &rhs) const noexcept { return value == rhs.value; }
  constexpr bool operator != (const static_modint &rhs) const noexcept { return value != rhs.value; }

  friend std::ostream& operator << (std::ostream &stream, const static_modint &rhs) { return stream << rhs.value; }
  friend constexpr static_modint inverse(static_modint val) noexcept { return power(val, Mod - 2); }
  friend constexpr static_modint power(static_modint val, cover_type exp) noexcept { 
    static_modint res(1);
    for (; exp > 0; exp >>= 1, val *= val) if (exp & 1) res *= val;
    return res;
  }

};

template <uint32_t Mod>
using mint32_t = static_modint<Mod>;

/**
 * @title Static Modint
 */
#line 2 "algebraic/modular_operation.cpp"

#line 2 "other/random_number.cpp"

#line 4 "other/random_number.cpp"
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
#line 4 "algebraic/modular_operation.cpp"

#line 6 "algebraic/modular_operation.cpp"
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
#line 6 "test/discrete_log.cpp"

#include <cstddef>
#line 10 "test/discrete_log.cpp"

int main() {
  size_t Q;
  std::cin >> Q;
  while (Q--) {
    uint32_t x, y;
    std::cin >> x >> y >> runtime_mod::value();
    const auto ans = log(rmint32_t(x), rmint32_t(y));
    if (ans == runtime_mod::value()) {
      std::cout << "-1\n";
    }
    else {
      std::cout << ans << '\n';
    }
  }
  return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

