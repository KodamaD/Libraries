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


# :heavy_check_mark: Static Modint

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c7f6ad568392380a8f4b4cecbaccb64c">algebraic</a>
* <a href="{{ site.github.repository_url }}/blob/master/algebraic/modular.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-13 16:51:07+09:00




## Required by

* :warning: <a href="../test/discrete_log.cpp.html">test/discrete_log.cpp</a>
* :warning: <a href="../test/sqrt_mod.cpp.html">test/sqrt_mod.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/factorials.test.cpp.html">test/factorials.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/lazy_propagation_segment_tree.test.cpp.html">test/lazy_propagation_segment_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/matrix.test.cpp.html">test/matrix.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/segment_tree.test.cpp.html">test/segment_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/sliding_window_aggregation.test.cpp.html">test/sliding_window_aggregation.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

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
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

