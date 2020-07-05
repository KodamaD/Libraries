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


# :heavy_check_mark: test/enumerate_divisors.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/enumerate_divisors.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-05 10:24:52+09:00


* see: <a href="https://yukicoder.me/problems/no/888">https://yukicoder.me/problems/no/888</a>


## Depends on

* :heavy_check_mark: <a href="../../library/algebraic/number_theory.cpp.html">algebraic/number_theory.cpp</a>
* :heavy_check_mark: <a href="../../library/other/fix_point.cpp.html">other/fix_point.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp

#define PROBLEM "https://yukicoder.me/problems/no/888"

#include "../algebraic/number_theory.cpp"

#include <cstdint>
#include <iostream>

int main() {
  uint64_t N;
  std::cin >> N;
  uint64_t ans = 0;
  for (auto x: enumerate_divisors(N, false)) {
    ans += x;
  }
  std::cout << ans << '\n';
  return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/enumerate_divisors.test.cpp"

#define PROBLEM "https://yukicoder.me/problems/no/888"

#line 2 "algebraic/number_theory.cpp"

#line 2 "other/fix_point.cpp"

#include <utility>

template <class Func>
struct fix_point: private Func {
  explicit constexpr fix_point(Func &&func): Func(std::forward<Func>(func)) { }
  template <class... Args>
  constexpr decltype(auto) operator () (Args &&... args) const {
    return Func::operator()(*this, std::forward<Args>(args)...);
  }
};

template <class Func>
constexpr decltype(auto) make_fix_point(Func &&func) {
  return fix_point<Func>(std::forward<Func>(func));
}
#line 4 "algebraic/number_theory.cpp"
#include <cstddef>
#include <cstdint>
#line 7 "algebraic/number_theory.cpp"
#include <vector>
#include <algorithm>

namespace number_theory_detail {

  using u32 = uint32_t;
  using u64 = uint64_t;
  using u128 = __uint128_t;

  class m64 {
  public:
    static inline u64 mod;

    static void set_mod(u64 x) {
      mod = x;
      encode = -u128(mod) % mod;
      decode = [] {
        u64 res = 0, cur = 0;
        for (size_t i = 0; i < 64; ++i) {
          if (!(cur & 1)) { res += u64(1) << i; cur += mod; }
          cur >>= 1;
        }
        return res;
      }();
    }

  private:
    static inline u64 encode;
    static inline u64 decode;

    static u64 reduce(u128 x) {
      u64 res = u64((u128(u64(x) * decode) * mod + x) >> 64);
      return res >= mod ? res - mod : res;
    }

    u64 value;

  public:
    m64(): value(0) { }
    explicit m64(u64 x): value(reduce((u128) x * encode)) { }

    u64 get() const {
      u64 res = reduce(value);
      return res >= mod ? res - mod : res;
    }

    m64 power(u64 exp) const {
      m64 res(1), mult(*this);
      while (exp > 0) {
        if (exp & 1) res *= mult;
        mult *= mult;
        exp >>= 1;
      }
      return res;
    }

    m64 operator + (const m64 &rhs) const { return m64(*this) += rhs; }
    m64& operator += (const m64 &rhs) { 
      if ((value += rhs.value) >= mod) value -= mod;
      return *this; 
    }
    m64 operator * (const m64 &rhs) const { return m64(*this) *= rhs; }
    m64& operator *= (const m64 &rhs) { 
      value = reduce((u128) value * rhs.value);
      return *this;
    }
    bool operator == (const m64 &rhs) const { return value == rhs.value; }
    bool operator != (const m64 &rhs) const { return value != rhs.value; }

  };

  u64 gcd64(u64 a, u64 b) {
    if (a == 0) return b;
    if (b == 0) return a;
    if (a < b) std::swap(a, b);
    while (u64 r = a % b) a = b, b = r;
    return b;
  }

  bool test_prime(u64 a, u64 s, u64 d, u64 n) {
    m64::set_mod(n);
    m64 cur = m64(a).power(d);
    if (cur == m64(1)) return true;
    m64 bad(n - 1);
    for (size_t i = 0; i < s; ++i) {
      if (cur == bad) return true;
      cur *= cur;
    }
    return false;
  }

  template <class T>
  bool miller_rabin(T n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (!(n & 1)) return false;
    u64 d = n - 1, s = 0;
    while (!(d & 1)) { d >>= 1; ++s; }
    if (n < 4759123141) {
      for (auto p: { 2, 7, 61 }) {
        if (p >= n) break;
        if (!test_prime(p, s, d, n)) return false;
      }
    } 
    else {
      for (auto p: { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 }) {
        if (p >= n) break;
        if (!test_prime(p, s, d, n)) return false;
      }
    }
    return true;
  }

  template <class T>
  T pollard_rho(T n) {
    if (!(n & 1)) return 2;
    m64::set_mod(n);
    m64 add(1);
    auto transit = [&add](m64 m) { return m * m + add; };
    auto dif_abs = [](u64 x, u64 y) { return x > y ? x - y : y - x; };
    u64 initial = 0;
    while (true) {
      ++initial;
      m64 x(initial);
      m64 y = transit(x);
      while (true) {
        u64 g = number_theory_detail::gcd64(dif_abs(x.get(), y.get()), n);
        if (g == 1) {
          x = transit(x);
          y = transit(transit(y));
          continue;
        }
        if (g == n) break;
        return g;
      }
    }
  }

};

template <class T>
bool is_prime(T x) {
  return number_theory_detail::miller_rabin(x);
}

template <class T>
std::vector<T> enumerate_factors(T n, bool sort = true) {
  if (n == 1) return { };
  if (is_prime(n)) return { n };
  T d = number_theory_detail::pollard_rho(n);
  auto res = enumerate_factors(d);
  auto add = enumerate_factors(n / d);
  size_t size = res.size();
  res.resize(size + add.size());
  std::copy(add.cbegin(), add.cend(), res.begin() + size);
  if (sort) std::inplace_merge(res.begin(), res.begin() + size, res.end());
  return res;
}

template <class T>
std::vector<std::pair<T, size_t>> factorize(T n) {
  std::vector<std::pair<T, size_t>> res;
  T cur = 0;
  for (auto p: enumerate_factors(n)) {
    if (p != cur) {
      cur = p;
      res.emplace_back(p, 0);
    }
    ++res.back().second;
  }
  return res;
}

template <class T>
std::vector<T> enumerate_divisors(T n, bool sort = true) {
  auto factors = factorize(n);
  std::vector<T> res;
  size_t size = 1;
  for (auto [p, e]: factors) {
    size *= (e + 1);
  }
  res.reserve(size);
  make_fix_point([&](auto dfs, size_t i, T x) -> void {
    if (i == factors.size()) {
      res.push_back(x);
      return;
    }
    dfs(i + 1, x);
    auto [p, e] = factors[i];
    for (size_t j = 1; j <= e; ++j) {
      x *= p;
      dfs(i + 1, x);
    }
  })(0, 1);
  if (sort) std::sort(res.begin(), res.end());
  return res;
}
#line 5 "test/enumerate_divisors.test.cpp"

#line 7 "test/enumerate_divisors.test.cpp"
#include <iostream>

int main() {
  uint64_t N;
  std::cin >> N;
  uint64_t ans = 0;
  for (auto x: enumerate_divisors(N, false)) {
    ans += x;
  }
  std::cout << ans << '\n';
  return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

