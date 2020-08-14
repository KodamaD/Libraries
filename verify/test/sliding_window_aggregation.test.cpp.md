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


# :heavy_check_mark: test/sliding_window_aggregation.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/sliding_window_aggregation.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-11 15:45:19+09:00


* see: <a href="https://judge.yosupo.jp/problem/queue_operate_all_composite">https://judge.yosupo.jp/problem/queue_operate_all_composite</a>


## Depends on

* :heavy_check_mark: <a href="../../library/algebraic/modular.cpp.html">Modint</a>
* :heavy_check_mark: <a href="../../library/container/sliding_window_aggregation.cpp.html">Sliding Window Aggregation</a>
* :heavy_check_mark: <a href="../../library/other/monoid.cpp.html">Monoid Utility</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp

#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"

#include "../container/sliding_window_aggregation.cpp"
#include "../algebraic/modular.cpp"

#include <iostream>
#include <cstddef>
#include <cstdint>
#include <vector>

using m32 = mint32_t<998244353>;

struct st_monoid {
  struct value_structure {
    using type = std::pair<m32, m32>;
    static type identity() { return { m32(1), m32(0) }; }
    static type operation(const type& v1, const type& v2) { 
      return { v2.first * v1.first, v2.first * v1.second + v2.second };
    }
  };
};

int main() {
  size_t Q;
  std::cin >> Q;
  sliding_window_aggregation<st_monoid> que;
  while (Q--) {
    size_t type;
    std::cin >> type;
    if (type == 0) {
      m32 a, b;
      std::cin >> a.extract() >> b.extract();
      que.push({ a, b });
    }
    else if (type == 1) {
      que.pop();
    }
    else {
      m32 x;
      std::cin >> x.extract();
      auto fold = que.fold();
      std::cout << fold.first * x + fold.second << '\n';
    }
  }
  return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/sliding_window_aggregation.test.cpp"

#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"

#line 2 "container/sliding_window_aggregation.cpp"

#line 2 "other/monoid.cpp"

#include <type_traits>
#include <utility>
#include <stdexcept>

template <class T, class = void>
class has_identity: public std::false_type { };

template <class T>
class has_identity<T, typename std::conditional<false, decltype(T::identity()), void>::type>: public std::true_type { };

template <class T>
constexpr typename std::enable_if<has_identity<T>::value, typename T::type>::type empty_exception() {
  return T::identity();
}
template <class T>
[[noreturn]] constexpr typename std::enable_if<!has_identity<T>::value, typename T::type>::type empty_exception() {
  throw std::runtime_error("type T has no identity");
}

template <class T, bool HasIdentity>
class fixed_monoid_impl: public T {
public:
  static constexpr typename T::type convert(const typename T::type &value) { return value; }
  static constexpr typename T::type revert(const typename T::type &value) { return value; }

};

template <class T>
class fixed_monoid_impl<T, false>: private T {
public:
  class type {
  public:
    typename T::type value;
    bool state;
  
    explicit constexpr type(): value(typename T::type { }), state(false) { }
    explicit constexpr type(const typename T::type &value): value(value), state(true) { }

  };

  static constexpr type convert(const typename T::type &value) { return type(value); }
  static constexpr typename T::type revert(const type &value) { 
    if (!value.state) throw std::runtime_error("attempted to revert identity to non-monoid"); 
    return value.value; 
  }

  static constexpr type identity() { return type(); }
  static constexpr type operation(const type &v1, const type &v2) {
    if (!v1.state) return v2;
    if (!v2.state) return v1;
    return type(T::operation(v1.value, v2.value));
  }

};

template <class T>
using fixed_monoid = fixed_monoid_impl<T, has_identity<T>::value>;

template <class T, bool HasIdentity>
class fixed_combined_monoid_impl {
public:
  using value_structure    = typename T::value_structure;
  using operator_structure = fixed_monoid<typename T::operator_structure>;

  template <class... Args>
  static constexpr typename value_structure::type operation(
    const typename value_structure::type    &val,
    const typename operator_structure::type &op,
    Args&&... args) {
    return T::operation(val, op, std::forward<Args>(args)...);
  }

};

template <class T>
class fixed_combined_monoid_impl<T, false> {
public:
  using value_structure    = typename T::value_structure;
  using operator_structure = fixed_monoid<typename T::operator_structure>;

  template <class... Args>
  static constexpr typename value_structure::type operation(
    const typename value_structure::type    &val,
    const typename operator_structure::type &op,
    Args&&... args) {
    if (!op.state) return val;
    return T::operation(val, op.value, std::forward<Args>(args)...);
  }

};

template <class T>
using fixed_combined_monoid = fixed_combined_monoid_impl<T, has_identity<typename T::operator_structure>::value>;

/**
 * @title Monoid Utility
 */
#line 4 "container/sliding_window_aggregation.cpp"

#include <cstddef>
#include <stack>

template <class SemiGroup>
class sliding_window_aggregation {
public:
  using structure       = SemiGroup;
  using value_semigroup = typename SemiGroup::value_structure;
  using value_type      = typename SemiGroup::value_structure::type;
  using size_type       = size_t;

private:
  class node_type {
  public:
    value_type value, sum;
    node_type(const value_type &value, const value_type &sum): value(value), sum(sum) { }
  };

  std::stack<node_type> M_front, M_back;

public:
  sliding_window_aggregation(): M_front(), M_back() { }

  value_type fold() const {
    if (empty()) return empty_exception<value_semigroup>();
    if (M_front.empty()) return M_back.top().sum;
    else if (M_back.empty()) return M_front.top().sum;
    return value_semigroup::operation(M_front.top().sum, M_back.top().sum);
  }

  void push(const value_type &x) {
    if (M_back.empty()) M_back.emplace(x, x);
    else {
      value_type tmp = value_semigroup::operation(M_back.top().sum, x);
      M_back.emplace(x, tmp);
    }
  }
  void pop() {
    if (M_front.empty()) {
      M_front.emplace(M_back.top().value, M_back.top().value);
      M_back.pop();
      while (!M_back.empty()) {
        value_type tmp = value_semigroup::operation(M_back.top().value, M_front.top().sum);
        M_front.emplace(M_back.top().value, tmp);
        M_back.pop();
      }
    }
    M_front.pop();
  }

  size_type size() const {
    return M_front.size() + M_back.size();
  }
  bool empty() const {
    return M_front.empty() && M_back.empty();
  }

};

/**
 * @title Sliding Window Aggregation
 */
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
  constexpr value_type &extract() noexcept { return value; }
  constexpr modular operator - () const noexcept { return modular(mod() - value); }
  constexpr modular operator ~ () const noexcept { return inverse(*this); }

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
  friend constexpr modular inverse(modular val) noexcept { return power(val, mod() - 2); }
  friend constexpr modular power(modular val, cover_type exp) noexcept { 
    modular res(1);
    for (; exp > 0; exp >>= 1, val *= val) if (exp & 1) res *= val;
    return res;
  }

};

template <uint32_t Val>
struct modulus_impl { static constexpr uint32_t value() noexcept { return Val; } };
template <uint32_t Val>
using mint32_t = modular<modulus_impl<Val>>;

struct runtime_mod { static uint32_t &value() noexcept { static uint32_t val = 0; return val; } };
using rmint32_t = modular<runtime_mod>;

/**
 * @title Modint
 */
#line 6 "test/sliding_window_aggregation.test.cpp"

#line 10 "test/sliding_window_aggregation.test.cpp"
#include <vector>

using m32 = mint32_t<998244353>;

struct st_monoid {
  struct value_structure {
    using type = std::pair<m32, m32>;
    static type identity() { return { m32(1), m32(0) }; }
    static type operation(const type& v1, const type& v2) { 
      return { v2.first * v1.first, v2.first * v1.second + v2.second };
    }
  };
};

int main() {
  size_t Q;
  std::cin >> Q;
  sliding_window_aggregation<st_monoid> que;
  while (Q--) {
    size_t type;
    std::cin >> type;
    if (type == 0) {
      m32 a, b;
      std::cin >> a.extract() >> b.extract();
      que.push({ a, b });
    }
    else if (type == 1) {
      que.pop();
    }
    else {
      m32 x;
      std::cin >> x.extract();
      auto fold = que.fold();
      std::cout << fold.first * x + fold.second << '\n';
    }
  }
  return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

