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
    - Last commit date: 2020-07-04 17:17:38+09:00


* see: <a href="https://judge.yosupo.jp/problem/range_affine_range_sum">https://judge.yosupo.jp/problem/range_affine_range_sum</a>


## Depends on

* :question: <a href="../../library/algebraic/modular.cpp.html">algebraic/modular.cpp</a>
* :heavy_check_mark: <a href="../../library/container/lazy_propagation_segment_tree.cpp.html">container/lazy_propagation_segment_tree.cpp</a>
* :question: <a href="../../library/other/bit_operation.cpp.html">other/bit_operation.cpp</a>


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

using m32 = modular<998244353>;

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

constexpr size_t count_zero_right(const uint64_t x) {
  return x == 0 ? 64 : __builtin_ctzll(x);
}

constexpr size_t count_zero_left(const uint64_t x) {
  return x == 0 ? 64 : __builtin_clzll(x);
}

constexpr size_t bit_width(const uint64_t x) { 
  return 64 - count_zero_left(x);
}

constexpr uint64_t most_significant_bit(const uint64_t x) {
  return x == 0 ? 0 : uint64_t(1) << (bit_width(x) - 1);
}

constexpr uint64_t least_significant_bit(const uint64_t x) {
  return x & (-x);
}

constexpr uint64_t next_power_of_two(const uint64_t x) {
  return x == 0 ? 0 : most_significant_bit(2 * x - 1);
}

constexpr uint32_t bit_reverse_32(uint32_t x) {
  constexpr uint32_t b16 = 0b00000000000000001111111111111111;
  constexpr uint32_t  b8 = 0b00000000111111110000000011111111;
  constexpr uint32_t  b4 = 0b00001111000011110000111100001111;
  constexpr uint32_t  b2 = 0b00110011001100110011001100110011;
  constexpr uint32_t  b1 = 0b01010101010101010101010101010101;
  x = ((x >> 16) & b16) | ((x & b16) << 16);
  x = ((x >>  8) &  b8) | ((x &  b8) <<  8);
  x = ((x >>  4) &  b4) | ((x &  b4) <<  4);
  x = ((x >>  2) &  b2) | ((x &  b2) <<  2);
  x = ((x >>  1) &  b1) | ((x &  b1) <<  1);
  return x;
}
#line 5 "container/lazy_propagation_segment_tree.cpp"
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
  class node_type {
  public:
    value_type    value;
    operator_type lazy;
    node_type(
      const value_type    &value = value_monoid::identity(),
      const operator_type &lazy  = operator_monoid::identity()
    ): value(value), lazy(lazy) { }
  };

  static void S_apply(node_type &node, const operator_type &op, const size_type length) {
    node.value = structure::operation(node.value, op, length);
    node.lazy  = operator_monoid::operation(node.lazy, op);
  }

  void M_propagate(const size_type index, const size_type length) {
    S_apply(M_tree[index << 1 | 0], M_tree[index].lazy, length);
    S_apply(M_tree[index << 1 | 1], M_tree[index].lazy, length);
    M_tree[index].lazy = operator_monoid::identity();
  }
  void M_fix_change(const size_type index) {
    M_tree[index].value = 
      value_monoid::operation(M_tree[index << 1 | 0].value, M_tree[index << 1 | 1].value);
  }

  void M_pushdown(const size_type index) {
    const size_type lsb = count_zero_right(index);
    for (size_type story = bit_width(index); story != lsb; --story) {
      M_propagate(index >> story, 1 << (story - 1));
    }
  }
  void M_pullup(size_type index) {
    index >>= count_zero_right(index);
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
      M_tree.emplace_back(*first, operator_monoid::identity());
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

  void operate(size_type first, size_type last, const operator_type &op) {
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
    M_tree[index].lazy  = operator_monoid::identity();
  }

  void clear() {
    M_tree.clear();
    M_tree.shrink_to_fit();
  }

  size_type size() const { 
    return M_tree.size() >> 1;
  }

};
#line 2 "algebraic/modular.cpp"

#line 4 "algebraic/modular.cpp"
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
#line 6 "test/lazy_propagation_segment_tree.test.cpp"

#include <utility>
#line 11 "test/lazy_propagation_segment_tree.test.cpp"

using m32 = modular<998244353>;

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

