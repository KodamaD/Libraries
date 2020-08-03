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


# :heavy_check_mark: test/ntt.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/ntt.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-03 12:07:15+09:00


* see: <a href="https://judge.yosupo.jp/problem/convolution_mod">https://judge.yosupo.jp/problem/convolution_mod</a>


## Depends on

* :question: <a href="../../library/algebraic/modular.cpp.html">Modint</a>
* :heavy_check_mark: <a href="../../library/algebraic/ntt.cpp.html">Number Theoretic Transform</a>
* :question: <a href="../../library/other/bit_operation.cpp.html">Bit Operations</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp

#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../algebraic/ntt.cpp"

#include <iostream>
#include <vector>

using m32 = mint32_t<998244353>;

int main() {
  size_t N, M;
  std::cin >> N >> M;
  std::vector<m32> A(N), B(M);
  for (auto &x: A) {
    std::cin >> x.extract();
  }
  for (auto &x: B) {
    std::cin >> x.extract();
  }
  using ntt = number_theoretic_transform<m32>;
  auto C = ntt::convolve(A, B);
  for (size_t i = 0; i < C.size(); ++i) {
    std::cout << C[i];
    std::cout << (i + 1 == C.size() ? '\n' : ' ');
  }
  return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/ntt.test.cpp"

#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#line 2 "algebraic/ntt.cpp"

#line 2 "algebraic/modular.cpp"

#include <cstdint>
#include <iostream>

template <class Modulus>
class modular {
public:
  using value_type = uint32_t;
  using cover_type = uint64_t;
  static constexpr value_type mod() { return Modulus::value(); }

  template <class T>
  static constexpr value_type normalize(T value_) noexcept {
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
  constexpr modular() noexcept : value(0) { }
  template <class T>
  explicit constexpr modular(T value_) noexcept : value(normalize(value_)) { }
  template <class T>
  explicit constexpr operator T() const noexcept { return static_cast<T>(value); }

  constexpr value_type get() const noexcept { return value; }
  constexpr modular operator - () const noexcept { return modular(mod() - value); }
  constexpr modular operator ~ () const noexcept { return inverse(); }

  constexpr value_type &extract() noexcept { return value; }
  constexpr modular inverse() const noexcept { return power(mod() - 2); }
  constexpr modular power(cover_type exp) const noexcept {
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
    if ((value += rhs.value) >= mod()) value -= mod(); 
    return *this; 
  }

  constexpr modular operator - (const modular &rhs) const noexcept { return modular(*this) -= rhs; }
  constexpr modular& operator -= (const modular &rhs) noexcept { 
    if ((value += mod() - rhs.value) >= mod()) value -= mod(); 
    return *this; 
  }

  constexpr modular operator * (const modular &rhs) const noexcept { return modular(*this) *= rhs; }
  constexpr modular& operator *= (const modular &rhs) noexcept { 
    value = (cover_type) value * rhs.value % mod();
    return *this;
  }

  constexpr modular operator / (const modular &rhs) const noexcept { return modular(*this) /= rhs; }
  constexpr modular& operator /= (const modular &rhs) noexcept { return (*this) *= rhs.inverse(); }

  constexpr bool zero() const noexcept { return value == 0; }
  constexpr bool operator == (const modular &rhs) const noexcept { return value == rhs.value; }
  constexpr bool operator != (const modular &rhs) const noexcept { return value != rhs.value; }

  friend std::ostream& operator << (std::ostream &stream, const modular &rhs) { return stream << rhs.value; }
  friend constexpr modular power(modular val, cover_type exp) noexcept { return val.power(exp); }
  friend constexpr modular inverse(modular val) noexcept { return val.inverse(); }

};

template <uint32_t Val>
struct modulus { static constexpr uint32_t value() noexcept { return Val; } };
template <uint32_t Val>
using mint32_t = modular<modulus<Val>>;

struct runtime_mod { static uint32_t &value() noexcept { static uint32_t val = 0; return val; } };
using rmint32_t = modular<runtime_mod>;

/**
 * @title Modint
 */
#line 2 "other/bit_operation.cpp"

#include <cstddef>
#line 5 "other/bit_operation.cpp"

constexpr size_t bit_ppc(const uint64_t x) {
  return __builtin_popcountll(x);
}

constexpr size_t bit_ctzr(const uint64_t x) {
  return x == 0 ? 64 : __builtin_ctzll(x);
}

constexpr size_t bit_ctzl(const uint64_t x) {
  return x == 0 ? 64 : __builtin_clzll(x);
}

constexpr size_t bit_width(const uint64_t x) { 
  return 64 - bit_ctzl(x);
}

constexpr uint64_t bit_msb(const uint64_t x) {
  return x == 0 ? 0 : uint64_t(1) << (bit_width(x) - 1);
}

constexpr uint64_t bit_lsb(const uint64_t x) {
  return x & (-x);
}

constexpr uint64_t bit_cover(const uint64_t x) {
  return x == 0 ? 0 : bit_msb(2 * x - 1);
}

constexpr uint64_t bit_rev(uint64_t x) {
  x = ((x >> 1) & 0x5555555555555555) | ((x & 0x5555555555555555) << 1);
  x = ((x >> 2) & 0x3333333333333333) | ((x & 0x3333333333333333) << 2);
  x = ((x >> 4) & 0x0F0F0F0F0F0F0F0F) | ((x & 0x0F0F0F0F0F0F0F0F) << 4);
  x = ((x >> 8) & 0x00FF00FF00FF00FF) | ((x & 0x00FF00FF00FF00FF) << 8);
  x = ((x >> 16) & 0x0000FFFF0000FFFF) | ((x & 0x0000FFFF0000FFFF) << 16);
  x = (x >> 32) | (x << 32);
  return x;
}

/**
 * @title Bit Operations
 */
#line 6 "algebraic/ntt.cpp"
#include <vector>
#include <array>
#include <utility>
#include <algorithm>

namespace ntt_detail {

  constexpr uint32_t primitive_root(uint32_t mod) {
    std::array<uint32_t, 32> exp{};
    uint32_t cur = mod - 1;
    size_t size = 0;
    for (uint32_t i = 2; i * i <= cur; ++i) {
      if (cur % i == 0) {
        exp[size++] = (mod - 1) / i;
        while (cur % i == 0) cur /= i;
      }
    }
    if (cur != 1) {
      exp[size++] = (mod - 1) / cur;
    }
    uint32_t res = 2;
    while (true) {
      bool ok = true;
      for (size_t i = 0; i < size; ++i) {
        uint64_t a = res, e = exp[i], x = 1;
        while (e > 0) {
          if (e & 1) (x *= a) %= mod;
          (a *= a) %= mod;
          e >>= 1;
        }
        if (x == 1) {
          ok = false;
          break;
        }
      }
      if (ok) break;
      ++res;
    }
    return res;
  };

  template <size_t N, class T>
  constexpr std::array<T, N> compute_roots(T omega) {
    std::array<T, N> res;
    res[N - 1] = omega;
    for (size_t i = N - 1; i > 0; --i) {
      res[i - 1] = res[i] * res[i];
    }
    return res;
  }

  /*
    prime numbers for ntt
    [ 1051721729 ]  [ 2^20 ]
    [ 1045430273 ]  [ 2^20 ]
    [ 1007681537 ]  [ 2^20 ]
    [  962592769 ]  [ 2^21 ]
    [  924844033 ]  [ 2^21 ]
    [  985661441 ]  [ 2^22 ]
    [  943718401 ]  [ 2^22 ]
    [  935329793 ]  [ 2^22 ]
    [  998244353 ]  [ 2^23 ]
    [  754974721 ]  [ 2^24 ]
    [  167772161 ]  [ 2^25 ]
    [  469762049 ]  [ 2^26 ]
  */

}

template <class Modular>
class number_theoretic_transform {
public:
  using value_type = Modular;
  static constexpr uint32_t mod = Modular::mod();
  static constexpr uint32_t prim = ntt_detail::primitive_root(mod);

private:
  static constexpr size_t level = bit_ctzr(mod - 1);
  static constexpr value_type unit = value_type(1);
  static constexpr value_type omega = value_type(prim).power((mod - 1) >> level); 
  static constexpr auto roots = ntt_detail::compute_roots<level>(omega);
  static constexpr auto inv_roots = ntt_detail::compute_roots<level>(omega.inverse());

public:
  static void transform(std::vector<value_type> &F) {
    size_t size = F.size();
    size_t logn = bit_ctzr(size);
    for (size_t i = 0; i < size; ++i) {
      size_t j = bit_rev(i) >> (64 - logn);
      if (i < j) {
        std::swap(F[i], F[j]);
      }
    }
    value_type coeff = unit;
    for (size_t s = 0; s < logn; ++s) {
      size_t mh = 1 << s;
      size_t m = mh << 1;
      for (size_t i = 0; i < size; i += m) {
        coeff = unit;
        for (size_t j = i; j < i + mh; ++j) {
          auto a = F[j];
          auto b = F[j + mh] * coeff;
          F[j] = a + b;
          F[j + mh] = a - b;
          coeff *= roots[s];
        }
      }
    }
  }

  static void inv_transform(std::vector<value_type> &F) {
    size_t size = F.size();
    size_t logn = bit_ctzr(size);
    for (size_t i = 0; i < size; ++i) {
      size_t j = bit_rev(i) >> (64 - logn);
      if (i < j) {
        std::swap(F[i], F[j]);
      }
    }
    value_type coeff = unit;
    for (size_t s = 0; s < logn; ++s) {
      size_t mh = 1 << s;
      size_t m = mh << 1;
      for (size_t i = 0; i < size; i += m) {
        coeff = unit;
        for (size_t j = i; j < i + mh; ++j) {
          auto a = F[j];
          auto b = F[j + mh] * coeff;
          F[j] = a + b;
          F[j + mh] = a - b;
          coeff *= inv_roots[s];
        }
      }
    }
    coeff = value_type(size).inverse();
    for (auto &x: F) {
      x *= coeff;
    }
  }

  template <bool Same = false, typename std::enable_if<!Same, void>::type* = nullptr>
  static std::vector<value_type> convolve(
    std::vector<value_type> A, 
    std::vector<value_type> B) {
    if (A.empty() || B.empty()) return { };
    size_t res_size = A.size() + B.size() - 1;
    size_t fix_size = bit_cover(res_size);
    A.resize(fix_size);
    B.resize(fix_size);
    transform(A);
    transform(B);
    for (size_t i = 0; i < fix_size; ++i) {
      A[i] *= B[i];
    }
    inv_transform(A);
    A.resize(res_size);
    return A;
  }

  template <bool Same = false, typename std::enable_if<Same, void>::type* = nullptr>
  static std::vector<value_type> convolve(
    std::vector<value_type> A,
    const std::vector<value_type>&) {
    if (A.empty()) return { };
    size_t res_size = 2 * A.size() - 1;
    size_t fix_size = bit_cover(res_size);
    A.resize(fix_size);
    transform(A);
    for (size_t i = 0; i < fix_size; ++i) {
      A[i] *= A[i];
    }
    inv_transform(A);
    A.resize(res_size);
    return A;
  }

};

/**
 * @title Number Theoretic Transform
 */
#line 5 "test/ntt.test.cpp"

#line 8 "test/ntt.test.cpp"

using m32 = mint32_t<998244353>;

int main() {
  size_t N, M;
  std::cin >> N >> M;
  std::vector<m32> A(N), B(M);
  for (auto &x: A) {
    std::cin >> x.extract();
  }
  for (auto &x: B) {
    std::cin >> x.extract();
  }
  using ntt = number_theoretic_transform<m32>;
  auto C = ntt::convolve(A, B);
  for (size_t i = 0; i < C.size(); ++i) {
    std::cout << C[i];
    std::cout << (i + 1 == C.size() ? '\n' : ' ');
  }
  return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

