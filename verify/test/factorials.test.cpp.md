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


# :heavy_check_mark: test/factorials.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/factorials.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-05 19:22:30+09:00


* see: <a href="https://yukicoder.me/problems/no/117">https://yukicoder.me/problems/no/117</a>


## Depends on

* :heavy_check_mark: <a href="../../library/algebraic/factorials.cpp.html">Factorial</a>
* :heavy_check_mark: <a href="../../library/algebraic/modular.cpp.html">Modint</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp

#define PROBLEM "https://yukicoder.me/problems/no/117"

#include "../algebraic/factorials.cpp"
#include "../algebraic/modular.cpp"

#include <cstddef>
#include <iostream>

using m32 = modular<1000000007>;
factorials<m32, 2000000> fact;

m32 comb(size_t N, size_t K) {
  if (N < K) return m32(0);
  return fact(N, K);
}

m32 perm(size_t N, size_t K) {
  if (N < K) return m32(0);
  return fact.fact[N] * fact.fact_inv[N - K];
}

m32 homo(size_t N, size_t K) {
  if (N == 0 && K == 0) return m32(1);
  if (N == 0) return m32(0);
  return fact(N + K - 1, K);
}

int main() {
  size_t T;
  std::cin >> T;
  while (T--) {
    char type, dust;
    size_t N, K;
    std::cin >> type >> dust >> N >> dust >> K >> dust;
    if (type == 'C') std::cout << comb(N, K) << '\n';
    if (type == 'P') std::cout << perm(N, K) << '\n';
    if (type == 'H') std::cout << homo(N, K) << '\n';
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/factorials.test.cpp"

#define PROBLEM "https://yukicoder.me/problems/no/117"

#line 2 "algebraic/factorials.cpp"

#include <cstddef>
#include <array>

template <class T, size_t N>
class factorials {
public:
  using value_type = T;
  static constexpr size_t size = N;

public:
  std::array<value_type, size + 1> fact{};
  std::array<value_type, size + 1> fact_inv{};

  factorials() {
    fact.front() = value_type(1);
    for (size_t i = 1; i <= size; ++i) {
      fact[i] = fact[i - 1] * value_type(i);
    }
    fact_inv.back() = ~fact.back();
    for (size_t i = size; i > 0; --i) {
      fact_inv[i - 1] = fact_inv[i] * value_type(i);
    }
  }

  value_type operator () (size_t n, size_t r) const {
    return fact[n] * fact_inv[n - r] * fact_inv[r];
  }

};

/**
 * @title Factorial
 */
#line 2 "algebraic/modular.cpp"

#include <cstdint>
#include <iostream>

template <uint32_t Modulus>
class modular {
public:
  using value_type = uint32_t;
  using max_type = uint64_t;

  static constexpr value_type mod = Modulus;
  static constexpr value_type get_mod() noexcept { return mod; }
  static_assert(mod >= 2, "invalid mod :: smaller than 2");
  static_assert(mod < (value_type(1) << 31), "invalid mod :: over 2^31");

  template <class T>
  static constexpr value_type normalize(T value_) noexcept {
    if (value_ < 0) {
      value_ = -value_;
      value_ %= mod;
      if (value_ == 0) return 0;
      return mod - value_;
    }
    return value_ % mod;
  }

private:
  value_type value;

public:
  constexpr modular() noexcept : value(0) { }
  template <class T>
  explicit constexpr modular(T value_) noexcept : value(normalize(value_)) { }
  template <class T>
  explicit constexpr operator T() const noexcept { return static_cast<T>(value); }

  constexpr value_type get() const noexcept { return value; }
  constexpr modular operator - () const noexcept { return modular(mod - value); }
  constexpr modular operator ~ () const noexcept { return inverse(); }

  constexpr value_type &extract() noexcept { return value; }
  constexpr modular inverse() const noexcept { return power(mod - 2); }
  constexpr modular power(max_type exp) const noexcept {
    modular res(1), mult(*this);
    while (exp > 0) {
      if (exp & 1) res *= mult;
      mult *= mult;
      exp >>= 1;
    }
    return res;
  }

  constexpr modular operator + (const modular &rhs) const noexcept { return modular(*this) += rhs; }
  constexpr modular& operator += (const modular &rhs) noexcept { 
    if ((value += rhs.value) >= mod) value -= mod; 
    return *this; 
  }

  constexpr modular operator - (const modular &rhs) const noexcept { return modular(*this) -= rhs; }
  constexpr modular& operator -= (const modular &rhs) noexcept { 
    if ((value += mod - rhs.value) >= mod) value -= mod; 
    return *this; 
  }

  constexpr modular operator * (const modular &rhs) const noexcept { return modular(*this) *= rhs; }
  constexpr modular& operator *= (const modular &rhs) noexcept { 
    value = (max_type) value * rhs.value % mod;
    return *this;
  }

  constexpr modular operator / (const modular &rhs) const noexcept { return modular(*this) /= rhs; }
  constexpr modular& operator /= (const modular &rhs) noexcept { return (*this) *= rhs.inverse(); }

  constexpr bool zero() const noexcept { return value == 0; }
  constexpr bool operator == (const modular &rhs) const noexcept { return value == rhs.value; }
  constexpr bool operator != (const modular &rhs) const noexcept { return value != rhs.value; }
  friend std::ostream& operator << (std::ostream &stream, const modular &rhs) {
    return stream << rhs.value;
  }

};

/**
 * @title Modint
 */
#line 6 "test/factorials.test.cpp"

#line 9 "test/factorials.test.cpp"

using m32 = modular<1000000007>;
factorials<m32, 2000000> fact;

m32 comb(size_t N, size_t K) {
  if (N < K) return m32(0);
  return fact(N, K);
}

m32 perm(size_t N, size_t K) {
  if (N < K) return m32(0);
  return fact.fact[N] * fact.fact_inv[N - K];
}

m32 homo(size_t N, size_t K) {
  if (N == 0 && K == 0) return m32(1);
  if (N == 0) return m32(0);
  return fact(N + K - 1, K);
}

int main() {
  size_t T;
  std::cin >> T;
  while (T--) {
    char type, dust;
    size_t N, K;
    std::cin >> type >> dust >> N >> dust >> K >> dust;
    if (type == 'C') std::cout << comb(N, K) << '\n';
    if (type == 'P') std::cout << perm(N, K) << '\n';
    if (type == 'H') std::cout << homo(N, K) << '\n';
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

