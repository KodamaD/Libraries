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


# :warning: algebraic/runtime_modular.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c7f6ad568392380a8f4b4cecbaccb64c">algebraic</a>
* <a href="{{ site.github.repository_url }}/blob/master/algebraic/runtime_modular.cpp">View this file on GitHub</a>
    - Last commit date: 2020-06-14 13:42:06+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp

template <class Modulus>
class modular {
public:
  using value_type = uint32_t;
  using max_type = uint64_t;
  
  static value_type mod() { return Modulus::value; } 
  static value_type get_mod() { return Modulus::value;; }

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
  modular(): value(0) { }
  template <class T>
  explicit modular(T value_): value(normalize(value_)) { }
  template <class T>
  explicit operator T() { return static_cast<T>(value); }

  value_type get() const { return value; }
  modular operator - () const { return modular(mod() - value); }
  modular operator ~ () const { return inverse(); }

  value_type &extract() { return value; }
  modular inverse() const { return power(mod() - 2); }
  modular power(max_type exp) const {
    modular res(1), mult(*this);
    while (exp > 0) {
      if (exp & 1) res *= mult;
      mult *= mult;
      exp >>= 1;
    }
    return res;
  }

  modular operator + (const modular &rhs) const { return modular(*this) += rhs; }
  modular& operator += (const modular &rhs) { 
    if ((value += rhs.value) >= mod()) value -= mod(); 
    return *this; 
  }

  modular operator - (const modular &rhs) const { return modular(*this) -= rhs; }
  modular& operator -= (const modular &rhs) { 
    if ((value += mod() - rhs.value) >= mod()) value -= mod(); 
    return *this; 
  }

  modular operator * (const modular &rhs) const { return modular(*this) *= rhs; }
  modular& operator *= (const modular &rhs) { 
    value = (max_type) value * rhs.value % mod();
    return *this;
  }

  modular operator / (const modular &rhs) const { return modular(*this) /= rhs; }
  modular& operator /= (const modular &rhs) { return (*this) *= rhs.inverse(); }

  bool zero() const { return value == 0; }
  bool operator == (const modular &rhs) const { return value == rhs.value; }
  bool operator != (const modular &rhs) const { return value != rhs.value; }
  friend std::ostream& operator << (std::ostream &stream, const modular &rhs) {
    return stream << rhs.value;
  }

};

struct modulus_type { static inline uint32_t value; };
using m32 = modular<modulus_type>;

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "algebraic/runtime_modular.cpp"

template <class Modulus>
class modular {
public:
  using value_type = uint32_t;
  using max_type = uint64_t;
  
  static value_type mod() { return Modulus::value; } 
  static value_type get_mod() { return Modulus::value;; }

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
  modular(): value(0) { }
  template <class T>
  explicit modular(T value_): value(normalize(value_)) { }
  template <class T>
  explicit operator T() { return static_cast<T>(value); }

  value_type get() const { return value; }
  modular operator - () const { return modular(mod() - value); }
  modular operator ~ () const { return inverse(); }

  value_type &extract() { return value; }
  modular inverse() const { return power(mod() - 2); }
  modular power(max_type exp) const {
    modular res(1), mult(*this);
    while (exp > 0) {
      if (exp & 1) res *= mult;
      mult *= mult;
      exp >>= 1;
    }
    return res;
  }

  modular operator + (const modular &rhs) const { return modular(*this) += rhs; }
  modular& operator += (const modular &rhs) { 
    if ((value += rhs.value) >= mod()) value -= mod(); 
    return *this; 
  }

  modular operator - (const modular &rhs) const { return modular(*this) -= rhs; }
  modular& operator -= (const modular &rhs) { 
    if ((value += mod() - rhs.value) >= mod()) value -= mod(); 
    return *this; 
  }

  modular operator * (const modular &rhs) const { return modular(*this) *= rhs; }
  modular& operator *= (const modular &rhs) { 
    value = (max_type) value * rhs.value % mod();
    return *this;
  }

  modular operator / (const modular &rhs) const { return modular(*this) /= rhs; }
  modular& operator /= (const modular &rhs) { return (*this) *= rhs.inverse(); }

  bool zero() const { return value == 0; }
  bool operator == (const modular &rhs) const { return value == rhs.value; }
  bool operator != (const modular &rhs) const { return value != rhs.value; }
  friend std::ostream& operator << (std::ostream &stream, const modular &rhs) {
    return stream << rhs.value;
  }

};

struct modulus_type { static inline uint32_t value; };
using m32 = modular<modulus_type>;

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

