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
    - Last commit date: 2020-09-13 16:51:07+09:00


* see: <a href="https://judge.yosupo.jp/problem/queue_operate_all_composite">https://judge.yosupo.jp/problem/queue_operate_all_composite</a>


## Depends on

* :heavy_check_mark: <a href="../../library/algebraic/modular.cpp.html">Static Modint</a>
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
[[noreturn]] typename std::enable_if<!has_identity<T>::value, typename T::type>::type empty_exception() {
  throw std::runtime_error("type T has no identity");
}

template <class T, bool HasIdentity>
class fixed_monoid_impl: public T {
public:
  using type = typename T::type;

  static constexpr type convert(const type &value) { return value; }
  static constexpr type revert(const type &value) { return value; }

  template <class Mapping, class Value, class... Args>
  static constexpr void operate(Mapping &&func, Value &value, const type &op, Args&&... args) {
    value = func(value, op, std::forward<Args>(args)...);
  }
  template <class Constraint>
  static constexpr bool satisfies(Constraint &&func, const type &value) {
    return func(value);
  }
};

template <class T>
class fixed_monoid_impl<T, false> {
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

  template <class Mapping, class Value, class... Args>
  static constexpr void operate(Mapping &&func, Value &value, const type &op, Args&&... args) {
    if (!op.state) return;
    value = func(value, op.value, std::forward<Args>(args)...);
  }
  template <class Constraint>
  static constexpr bool satisfies(Constraint &&func, const type &value) {
    if (!value.state) return false;
    return func(value.value);
  }
};

template <class T>
using fixed_monoid = fixed_monoid_impl<T, has_identity<T>::value>;

/**
 * @title Monoid Utility
 */
#line 4 "container/sliding_window_aggregation.cpp"

#include <cstddef>
#include <stack>
#include <cassert>

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
    assert(!empty());
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

