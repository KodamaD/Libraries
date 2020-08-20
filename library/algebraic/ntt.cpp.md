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


# :warning: Number Theoretic Transform

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c7f6ad568392380a8f4b4cecbaccb64c">algebraic</a>
* <a href="{{ site.github.repository_url }}/blob/master/algebraic/ntt.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-16 21:16:25+09:00




## Depends on

* :heavy_check_mark: <a href="../other/bit_operation.cpp.html">Bit Operations</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "../other/bit_operation.cpp"

#include <cstddef>
#include <vector>
#include <array>
#include <utility>
#include <algorithm>

namespace ntt_detail {

  constexpr uint32_t primitive_root(const uint32_t mod) {
    std::array<uint32_t, 32> exp{};
    uint32_t cur = mod - 1;
    size_t size = 0;
    for (uint32_t i = 2; i * i <= cur; ++i) {
      if (cur % i == 0) {
        exp[size++] = (mod - 1) / i;
        while (cur % i == 0) cur /= i;
      }
    }
    if (cur != 1) exp[size++] = (mod - 1) / cur;
    for (uint32_t check = 1; check < mod; ++check) {
      for (auto e: exp) {
        if (e == 0) return check;
        uint64_t a = check, x = 1;
        while (e > 0) {
          if (e & 1) (x *= a) %= mod;
          (a *= a) %= mod;
          e >>= 1;
        }
        if (x == 1) break;
      }
    }
    return mod;
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

}

template <class Modular>
class number_theoretic_transform {
public:
  using value_type = Modular;
  static constexpr uint32_t mod = Modular::mod();
  static constexpr uint32_t prim = ntt_detail::primitive_root(mod);

private:
  static constexpr size_t level = bit_ctzr(mod - 1);
  static constexpr value_type omega = power(value_type(prim), ((mod - 1) >> level)); 
  static constexpr auto roots = ntt_detail::compute_roots<level>(omega);
  static constexpr auto inv_roots = ntt_detail::compute_roots<level>(inverse(omega));

public:
  static void transform(std::vector<value_type> &F) {
    const size_t size = F.size();
    const size_t logn = bit_ctzr(size);
    for (size_t i = 0; i < size; ++i) {
      const size_t j = bit_rev(i) >> (64 - logn);
      if (i < j) std::swap(F[i], F[j]);
    }
    value_type coeff(1);
    for (size_t s = 0; s < logn; ++s) {
      const size_t mh = 1 << s;
      const size_t m = mh << 1;
      for (size_t i = 0; i < size; i += m) {
        coeff = value_type(1);
        for (size_t j = i; j < i + mh; ++j) {
          const auto a = F[j];
          const auto b = F[j + mh] * coeff;
          F[j] = a + b;
          F[j + mh] = a - b;
          coeff *= roots[s];
        }
      }
    }
  }

  static void inv_transform(std::vector<value_type> &F) {
    const size_t size = F.size();
    const size_t logn = bit_ctzr(size);
    for (size_t i = 0; i < size; ++i) {
      const size_t j = bit_rev(i) >> (64 - logn);
      if (i < j) std::swap(F[i], F[j]);
    }
    value_type coeff(1);
    for (size_t s = 0; s < logn; ++s) {
      const size_t mh = 1 << s;
      const size_t m = mh << 1;
      for (size_t i = 0; i < size; i += m) {
        coeff = value_type(1);
        for (size_t j = i; j < i + mh; ++j) {
          const auto a = F[j];
          const auto b = F[j + mh] * coeff;
          F[j] = a + b;
          F[j + mh] = a - b;
          coeff *= inv_roots[s];
        }
      }
    }
    coeff = inverse(value_type(size));
    for (auto &x: F) x *= coeff;
  }

};

/**
 * @title Number Theoretic Transform
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "algebraic/ntt.cpp"

#line 2 "other/bit_operation.cpp"

#include <cstddef>
#include <cstdint>

constexpr size_t   bit_ppc(const uint64_t x)   { return __builtin_popcountll(x); }
constexpr size_t   bit_ctzr(const uint64_t x)  { return x == 0 ? 64 : __builtin_ctzll(x); }
constexpr size_t   bit_ctzl(const uint64_t x)  { return x == 0 ? 64 : __builtin_clzll(x); }
constexpr size_t   bit_width(const uint64_t x) { return 64 - bit_ctzl(x); }
constexpr uint64_t bit_msb(const uint64_t x)   { return x == 0 ? 0 : uint64_t(1) << (bit_width(x) - 1); }
constexpr uint64_t bit_lsb(const uint64_t x)   { return x & (-x); }
constexpr uint64_t bit_cover(const uint64_t x) { return x == 0 ? 0 : bit_msb(2 * x - 1); }

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
#line 4 "algebraic/ntt.cpp"

#line 6 "algebraic/ntt.cpp"
#include <vector>
#include <array>
#include <utility>
#include <algorithm>

namespace ntt_detail {

  constexpr uint32_t primitive_root(const uint32_t mod) {
    std::array<uint32_t, 32> exp{};
    uint32_t cur = mod - 1;
    size_t size = 0;
    for (uint32_t i = 2; i * i <= cur; ++i) {
      if (cur % i == 0) {
        exp[size++] = (mod - 1) / i;
        while (cur % i == 0) cur /= i;
      }
    }
    if (cur != 1) exp[size++] = (mod - 1) / cur;
    for (uint32_t check = 1; check < mod; ++check) {
      for (auto e: exp) {
        if (e == 0) return check;
        uint64_t a = check, x = 1;
        while (e > 0) {
          if (e & 1) (x *= a) %= mod;
          (a *= a) %= mod;
          e >>= 1;
        }
        if (x == 1) break;
      }
    }
    return mod;
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

}

template <class Modular>
class number_theoretic_transform {
public:
  using value_type = Modular;
  static constexpr uint32_t mod = Modular::mod();
  static constexpr uint32_t prim = ntt_detail::primitive_root(mod);

private:
  static constexpr size_t level = bit_ctzr(mod - 1);
  static constexpr value_type omega = power(value_type(prim), ((mod - 1) >> level)); 
  static constexpr auto roots = ntt_detail::compute_roots<level>(omega);
  static constexpr auto inv_roots = ntt_detail::compute_roots<level>(inverse(omega));

public:
  static void transform(std::vector<value_type> &F) {
    const size_t size = F.size();
    const size_t logn = bit_ctzr(size);
    for (size_t i = 0; i < size; ++i) {
      const size_t j = bit_rev(i) >> (64 - logn);
      if (i < j) std::swap(F[i], F[j]);
    }
    value_type coeff(1);
    for (size_t s = 0; s < logn; ++s) {
      const size_t mh = 1 << s;
      const size_t m = mh << 1;
      for (size_t i = 0; i < size; i += m) {
        coeff = value_type(1);
        for (size_t j = i; j < i + mh; ++j) {
          const auto a = F[j];
          const auto b = F[j + mh] * coeff;
          F[j] = a + b;
          F[j + mh] = a - b;
          coeff *= roots[s];
        }
      }
    }
  }

  static void inv_transform(std::vector<value_type> &F) {
    const size_t size = F.size();
    const size_t logn = bit_ctzr(size);
    for (size_t i = 0; i < size; ++i) {
      const size_t j = bit_rev(i) >> (64 - logn);
      if (i < j) std::swap(F[i], F[j]);
    }
    value_type coeff(1);
    for (size_t s = 0; s < logn; ++s) {
      const size_t mh = 1 << s;
      const size_t m = mh << 1;
      for (size_t i = 0; i < size; i += m) {
        coeff = value_type(1);
        for (size_t j = i; j < i + mh; ++j) {
          const auto a = F[j];
          const auto b = F[j + mh] * coeff;
          F[j] = a + b;
          F[j + mh] = a - b;
          coeff *= inv_roots[s];
        }
      }
    }
    coeff = inverse(value_type(size));
    for (auto &x: F) x *= coeff;
  }

};

/**
 * @title Number Theoretic Transform
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

