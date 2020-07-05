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


# :heavy_check_mark: Modint (runtime mod)

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c7f6ad568392380a8f4b4cecbaccb64c">algebraic</a>
* <a href="{{ site.github.repository_url }}/blob/master/algebraic/runtime_modular.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-05 19:42:48+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/ntt_arbitrary_runtimemod.test.cpp.html">test/ntt_arbitrary_runtimemod.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cstdint>
#include <iostream>

template <class Modulus>
class runtime_modular {
public:
  using value_type = uint32_t;
  using max_type = uint64_t;
  
  static value_type mod() { return Modulus::value; } 
  static value_type get_mod() { return Modulus::value; }

  template <class T>
  static value_type normalize(T value_) {
    if (value_ < 0) {
      value_ = -value_;
      value_ %= mod();
      if (value_ == 0) return 0;
      return mod() - value_;
    }
    return value_ % mod();
  }

private:
  value_type value;

public:
  runtime_modular(): value(0) { }
  template <class T>
  explicit runtime_modular(T value_): value(normalize(value_)) { }
  template <class T>
  explicit operator T() { return static_cast<T>(value); }

  value_type get() const { return value; }
  runtime_modular operator - () const { return runtime_modular(mod() - value); }
  runtime_modular operator ~ () const { return inverse(); }

  value_type &extract() { return value; }
  runtime_modular inverse() const { return power(mod() - 2); }
  runtime_modular power(max_type exp) const {
    runtime_modular res(1), mult(*this);
    while (exp > 0) {
      if (exp & 1) res *= mult;
      mult *= mult;
      exp >>= 1;
    }
    return res;
  }

  runtime_modular operator + (const runtime_modular &rhs) const { return runtime_modular(*this) += rhs; }
  runtime_modular& operator += (const runtime_modular &rhs) { 
    if ((value += rhs.value) >= mod()) value -= mod(); 
    return *this; 
  }

  runtime_modular operator - (const runtime_modular &rhs) const { return runtime_modular(*this) -= rhs; }
  runtime_modular& operator -= (const runtime_modular &rhs) { 
    if ((value += mod() - rhs.value) >= mod()) value -= mod(); 
    return *this; 
  }

  runtime_modular operator * (const runtime_modular &rhs) const { return runtime_modular(*this) *= rhs; }
  runtime_modular& operator *= (const runtime_modular &rhs) { 
    value = (max_type) value * rhs.value % mod();
    return *this;
  }

  runtime_modular operator / (const runtime_modular &rhs) const { return runtime_modular(*this) /= rhs; }
  runtime_modular& operator /= (const runtime_modular &rhs) { return (*this) *= rhs.inverse(); }

  bool zero() const { return value == 0; }
  bool operator == (const runtime_modular &rhs) const { return value == rhs.value; }
  bool operator != (const runtime_modular &rhs) const { return value != rhs.value; }
  friend std::ostream& operator << (std::ostream &stream, const runtime_modular &rhs) {
    return stream << rhs.value;
  }

};

/**
 * @title Modint (runtime mod)
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "algebraic/runtime_modular.cpp"

#include <cstdint>
#include <iostream>

template <class Modulus>
class runtime_modular {
public:
  using value_type = uint32_t;
  using max_type = uint64_t;
  
  static value_type mod() { return Modulus::value; } 
  static value_type get_mod() { return Modulus::value; }

  template <class T>
  static value_type normalize(T value_) {
    if (value_ < 0) {
      value_ = -value_;
      value_ %= mod();
      if (value_ == 0) return 0;
      return mod() - value_;
    }
    return value_ % mod();
  }

private:
  value_type value;

public:
  runtime_modular(): value(0) { }
  template <class T>
  explicit runtime_modular(T value_): value(normalize(value_)) { }
  template <class T>
  explicit operator T() { return static_cast<T>(value); }

  value_type get() const { return value; }
  runtime_modular operator - () const { return runtime_modular(mod() - value); }
  runtime_modular operator ~ () const { return inverse(); }

  value_type &extract() { return value; }
  runtime_modular inverse() const { return power(mod() - 2); }
  runtime_modular power(max_type exp) const {
    runtime_modular res(1), mult(*this);
    while (exp > 0) {
      if (exp & 1) res *= mult;
      mult *= mult;
      exp >>= 1;
    }
    return res;
  }

  runtime_modular operator + (const runtime_modular &rhs) const { return runtime_modular(*this) += rhs; }
  runtime_modular& operator += (const runtime_modular &rhs) { 
    if ((value += rhs.value) >= mod()) value -= mod(); 
    return *this; 
  }

  runtime_modular operator - (const runtime_modular &rhs) const { return runtime_modular(*this) -= rhs; }
  runtime_modular& operator -= (const runtime_modular &rhs) { 
    if ((value += mod() - rhs.value) >= mod()) value -= mod(); 
    return *this; 
  }

  runtime_modular operator * (const runtime_modular &rhs) const { return runtime_modular(*this) *= rhs; }
  runtime_modular& operator *= (const runtime_modular &rhs) { 
    value = (max_type) value * rhs.value % mod();
    return *this;
  }

  runtime_modular operator / (const runtime_modular &rhs) const { return runtime_modular(*this) /= rhs; }
  runtime_modular& operator /= (const runtime_modular &rhs) { return (*this) *= rhs.inverse(); }

  bool zero() const { return value == 0; }
  bool operator == (const runtime_modular &rhs) const { return value == rhs.value; }
  bool operator != (const runtime_modular &rhs) const { return value != rhs.value; }
  friend std::ostream& operator << (std::ostream &stream, const runtime_modular &rhs) {
    return stream << rhs.value;
  }

};

/**
 * @title Modint (runtime mod)
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

