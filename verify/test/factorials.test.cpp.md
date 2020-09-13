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
    - Last commit date: 2020-09-13 16:51:07+09:00


* see: <a href="https://yukicoder.me/problems/no/117">https://yukicoder.me/problems/no/117</a>


## Depends on

* :heavy_check_mark: <a href="../../library/algebraic/factorials.cpp.html">Factorial</a>
* :heavy_check_mark: <a href="../../library/algebraic/modular.cpp.html">Static Modint</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp

#define PROBLEM "https://yukicoder.me/problems/no/117"

#include "../algebraic/factorials.cpp"
#include "../algebraic/modular.cpp"

#include <cstddef>
#include <iostream>

using m32 = mint32_t<1000000007>;
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
#include <cassert>

template <class T, size_t N>
class factorials {
public:
  using value_type = T;

public:
  std::array<value_type, N + 1> fact{};
  std::array<value_type, N + 1> fact_inv{};

  factorials() {
    fact.front() = value_type(1);
    for (size_t i = 1; i <= N; ++i) {
      fact[i] = fact[i - 1] * value_type(i);
    }
    fact_inv.back() = ~fact.back();
    for (size_t i = N; i > 0; --i) {
      fact_inv[i - 1] = fact_inv[i] * value_type(i);
    }
  }

  value_type operator () (size_t n, size_t r) const {
    assert(n <= N);
    assert(n >= r);
    return fact[n] * fact_inv[n - r] * fact_inv[r];
  }
};

/**
 * @title Factorial
 */
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
#line 6 "test/factorials.test.cpp"

#line 9 "test/factorials.test.cpp"

using m32 = mint32_t<1000000007>;
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

