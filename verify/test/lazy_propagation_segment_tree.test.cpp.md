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


# :heavy_check_mark: test/lazy_propagation_segment_tree.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/lazy_propagation_segment_tree.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-03 17:09:36+09:00


* see: <a href="https://judge.yosupo.jp/problem/range_affine_range_sum">https://judge.yosupo.jp/problem/range_affine_range_sum</a>


## Depends on

* :heavy_check_mark: <a href="../../library/algebraic/modular.cpp.html">Modint</a>
* :heavy_check_mark: <a href="../../library/container/lazy_propagation_segment_tree.cpp.html">Lazy Propagation Segment Tree</a>
* :heavy_check_mark: <a href="../../library/other/bit_operation.cpp.html">Bit Operations</a>
* :heavy_check_mark: <a href="../../library/other/monoid.cpp.html">other/monoid.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp

#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include "../container/lazy_propagation_segment_tree.cpp"
#include "../algebraic/modular.cpp"

#include <utility>
#include <iostream>
#include <cstddef>
#include <vector>

using m32 = mint32_t<998244353>;

struct lst_monoid {
  struct value_structure {
    using type = m32;
    static type identity() { return m32(0); }
    static type operation(const type& v1, const type& v2) { 
      return v1 + v2;
    }
  };
  struct operator_structure {
    using type = std::pair<m32, m32>;
    static type identity() { return { m32(1), m32(0) }; }
    static type operation(const type& v1, const type& v2) { 
      return { v2.first * v1.first, v2.first * v1.second + v2.second };
    }
  };
  static typename value_structure::type operation(
    const typename value_structure::type    &val,
    const typename operator_structure::type &op,
    const size_t length = 1) {
    return op.first * val + op.second * m32(length);
  }
};

int main() {
  size_t N, Q;
  std::cin >> N >> Q;
  std::vector<m32> A(N);
  for (auto &x: A) {
    std::cin >> x.extract();
  }
  lazy_propagation_segment_tree<lst_monoid> seg(A.begin(), A.end());
  while (Q--) {
    size_t t;
    std::cin >> t;
    if (t == 0) {
      size_t l, r;
      m32 b, c;
      std::cin >> l >> r >> b.extract() >> c.extract();
      seg.operate(l, r, { b, c });
    }
    else {
      size_t l, r;
      std::cin >> l >> r;
      std::cout << seg.fold(l, r).get() << '\n';
    }
  }
  return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/lazy_propagation_segment_tree.test.cpp"

#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#line 2 "container/lazy_propagation_segment_tree.cpp"

#line 2 "other/bit_operation.cpp"

#include <cstddef>
#include <cstdint>

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
#line 1 "other/monoid.cpp"

#include <type_traits>
#include <utility>
#include <stdexcept>

template <class T, class = void>
class has_identity: public std::false_type { };

template <class T>
class has_identity<T, typename std::conditional<false, decltype(T::identity()), void>::type>: public std::true_type { };

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
 * Monoid Utility
 */
#line 6 "container/lazy_propagation_segment_tree.cpp"
#include <vector>
#include <iterator>
#include <algorithm>

template <class CombinedMonoid>
class lazy_propagation_segment_tree {
public:
  using structure       = CombinedMonoid;
  using value_monoid    = typename CombinedMonoid::value_structure;
  using operator_monoid = typename CombinedMonoid::operator_structure;
  using value_type      = typename CombinedMonoid::value_structure::type;
  using operator_type   = typename CombinedMonoid::operator_structure::type;
  using size_type       = size_t;

private:
  using fixed_structure       = fixed_combined_monoid<structure>;
  using fixed_operator_monoid = typename fixed_structure::operator_structure;
  using fixed_operator_type   = typename fixed_operator_monoid::type;

  class node_type {
  public:
    value_type    value;
    fixed_operator_type lazy;
    node_type(
      const value_type    &value = value_monoid::identity(),
      const fixed_operator_type &lazy  = fixed_operator_monoid::identity()
    ): value(value), lazy(lazy) { }
  };

  static void S_apply(node_type &node, const fixed_operator_type &op, const size_type length) {
    node.value = fixed_structure::operation(node.value, op, length);
    node.lazy  = fixed_operator_monoid::operation(node.lazy, op);
  }

  void M_propagate(const size_type index, const size_type length) {
    S_apply(M_tree[index << 1 | 0], M_tree[index].lazy, length);
    S_apply(M_tree[index << 1 | 1], M_tree[index].lazy, length);
    M_tree[index].lazy = fixed_operator_monoid::identity();
  }
  void M_fix_change(const size_type index) {
    M_tree[index].value = 
      value_monoid::operation(M_tree[index << 1 | 0].value, M_tree[index << 1 | 1].value);
  }

  void M_pushdown(const size_type index) {
    const size_type lsb = bit_ctzr(index);
    for (size_type story = bit_width(index); story != lsb; --story) {
      M_propagate(index >> story, 1 << (story - 1));
    }
  }
  void M_pullup(size_type index) {
    index >>= bit_ctzr(index);
    while (index != 1) {
      index >>= 1;
      M_fix_change(index);
    }
  }

  std::vector<node_type> M_tree;

public:
  lazy_propagation_segment_tree() = default;
  explicit lazy_propagation_segment_tree(const size_type size) { initialize(size); }
  template <class InputIterator>
  explicit lazy_propagation_segment_tree(InputIterator first, InputIterator last) { construct(first, last); }

  void initialize(const size_type size) {
    clear();
    M_tree.assign(size << 1, node_type());
  }

  template <class InputIterator>
  void construct(InputIterator first, InputIterator last) {
    clear();
    const size_type size = std::distance(first, last);
    M_tree.reserve(size << 1);
    M_tree.assign(size, node_type());
    for (; first != last; ++first) {
      M_tree.emplace_back(*first, fixed_operator_monoid::identity());
    }
    for (size_type index = size - 1; index != 0; --index) {
      M_fix_change(index);
    }
  }

  value_type fold(size_type first, size_type last) {
    first += size();
    last  += size();
    M_pushdown(first);
    M_pushdown(last);
    value_type fold_l = value_monoid::identity();
    value_type fold_r = value_monoid::identity();
    while (first != last) {
      if (first & 1) {
        fold_l = value_monoid::operation(fold_l, M_tree[first].value);
        ++first;
      }
      if (last & 1) {
        --last;
        fold_r = value_monoid::operation(M_tree[last].value, fold_r);
      }
      first >>= 1;
      last  >>= 1;
    }
    return value_monoid::operation(fold_l, fold_r);
  }

  void operate(size_type first, size_type last, const operator_type &op_) {
    const auto op = fixed_operator_monoid::convert(op_);
    first += size();
    last  += size();
    M_pushdown(first);
    M_pushdown(last);
    const size_type first_c = first;
    const size_type last_c  = last;
    for (size_type story = 0; first != last; ++story) {
      if (first & 1) {
        S_apply(M_tree[first], op, 1 << story);
        ++first;
      }
      if (last & 1) {
        --last;
        S_apply(M_tree[last], op, 1 << story);
      }
      first >>= 1;
      last  >>= 1;
    }
    M_pullup(first_c);
    M_pullup(last_c);
  }

  void assign(size_type index, const value_type &val) {
    index += size();
    for (size_type story = bit_width(index); story != 0; --story) {
      M_propagate(index >> story, 1 << (story - 1));
    }
    M_tree[index].value = val;
    M_tree[index].lazy  = fixed_operator_monoid::identity();
  }

  void clear() {
    M_tree.clear();
    M_tree.shrink_to_fit();
  }

  size_type size() const { 
    return M_tree.size() >> 1;
  }

};

/**
 * @title Lazy Propagation Segment Tree
 */
#line 2 "algebraic/modular.cpp"

#line 4 "algebraic/modular.cpp"
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
#line 6 "test/lazy_propagation_segment_tree.test.cpp"

#line 11 "test/lazy_propagation_segment_tree.test.cpp"

using m32 = mint32_t<998244353>;

struct lst_monoid {
  struct value_structure {
    using type = m32;
    static type identity() { return m32(0); }
    static type operation(const type& v1, const type& v2) { 
      return v1 + v2;
    }
  };
  struct operator_structure {
    using type = std::pair<m32, m32>;
    static type identity() { return { m32(1), m32(0) }; }
    static type operation(const type& v1, const type& v2) { 
      return { v2.first * v1.first, v2.first * v1.second + v2.second };
    }
  };
  static typename value_structure::type operation(
    const typename value_structure::type    &val,
    const typename operator_structure::type &op,
    const size_t length = 1) {
    return op.first * val + op.second * m32(length);
  }
};

int main() {
  size_t N, Q;
  std::cin >> N >> Q;
  std::vector<m32> A(N);
  for (auto &x: A) {
    std::cin >> x.extract();
  }
  lazy_propagation_segment_tree<lst_monoid> seg(A.begin(), A.end());
  while (Q--) {
    size_t t;
    std::cin >> t;
    if (t == 0) {
      size_t l, r;
      m32 b, c;
      std::cin >> l >> r >> b.extract() >> c.extract();
      seg.operate(l, r, { b, c });
    }
    else {
      size_t l, r;
      std::cin >> l >> r;
      std::cout << seg.fold(l, r).get() << '\n';
    }
  }
  return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

