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


# :heavy_check_mark: test/matrix.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/matrix.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-11 15:45:19+09:00


* see: <a href="https://yukicoder.me/problems/no/1105">https://yukicoder.me/problems/no/1105</a>


## Depends on

* :question: <a href="../../library/algebraic/modular.cpp.html">Modint</a>
* :heavy_check_mark: <a href="../../library/container/matrix.cpp.html">Matrix</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp

#define PROBLEM "https://yukicoder.me/problems/no/1105"

#include "../algebraic/modular.cpp"
#include "../container/matrix.cpp"

#include <iostream>
#include <cstdint>

using m32 = mint32_t<1000000007>;

struct semiring {
  struct value_structure {
    using type = m32;
    static type addition_identity() { return m32(0); }
    static type addition(const type& v1, const type& v2) { 
      return v1 + v2;
    }
    static type multiplication_identity() { return m32(1); }
    static type multiplication(const type& v1, const type& v2) { 
      return v1 * v2;
    }
  };
};

int main() {
  int64_t N;
  std::cin >> N;
  int32_t a, b, c;
  std::cin >> a >> b >> c;
  using matrix_t = matrix<semiring>;
  matrix_t mult({ 
    { m32(1), m32(0), m32(-1) },
    { m32(-1), m32(1), m32(0) },
    { m32(0), m32(-1), m32(1) },
  });
  matrix_t start({
    { m32(a), m32(b), m32(c) }
  });
  start *= mult.power(N - 1);
  std::cout << start[0][0] << ' ' << start[0][1] << ' ' << start[0][2] << '\n';
  return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/matrix.test.cpp"

#define PROBLEM "https://yukicoder.me/problems/no/1105"

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
#line 2 "container/matrix.cpp"

#include <cstddef>
#line 5 "container/matrix.cpp"
#include <vector>
#include <algorithm>
#include <iterator>
#include <initializer_list>

template <class SemiRing>
class matrix {
public:
  using structure      = SemiRing;
  using value_semiring = typename SemiRing::value_structure;
  using value_type     = typename SemiRing::value_structure::type;
  using size_type      = size_t;

private:
  std::vector<std::vector<value_type>> M_matrix;

public:
  matrix() = default;
  explicit matrix(size_type H, size_type W, 
    const value_type &value = value_semiring::addition_identity()) { initialize(H, W, value); }
  explicit matrix(const std::vector<std::vector<value_type>> &cont) { construct(cont); }
  explicit matrix(const std::initializer_list<std::initializer_list<value_type>> &cont) { construct(cont); }

  void initialize(size_type H, size_type W, const value_type &value = value_semiring::addition_identity()) {
    clear();
    M_matrix.assign(H, std::vector<value_type>(W, value));
  }
  void construct(const std::vector<std::vector<value_type>> &cont) {
    clear();
    M_matrix = cont;
  }
  void construct(const std::initializer_list<std::initializer_list<value_type>> &cont) {
    clear();
    if (cont.size() > 0) {
      M_matrix.reserve(cont.size());
      std::transform(cont.begin(), cont.end(), std::back_inserter(M_matrix), [](const auto &vec) {
        return std::vector<value_type>(vec.begin(), vec.end());
      });
    }
  }
  void fill(const value_type &value) {
    for (auto &vec: M_matrix) {
      std::fill(vec.begin(), vec.end(), value);
    }
  }

  matrix operator + (const matrix &rhs) const { return matrix(*this) += rhs; }
  matrix& operator += (const matrix &rhs) { 
    for (size_type i = 0; i < height(); ++i) {
      for (size_type j = 0; j < width(); ++j) {
        M_matrix[i][j] = value_semiring::addition(M_matrix[i][j], rhs.M_matrix[i][j]);
      }
    }
    return *this;
  }

  matrix& operator *= (const matrix &rhs) { *this = (*this) * rhs; return *this; }
  matrix operator * (const matrix &rhs) const {
    matrix res(height(), rhs.width());
    for (size_type i = 0; i < height(); ++i) {
      for (size_type k = 0; k < width(); ++k) {
        for (size_type j = 0; j < rhs.width(); ++j) {
          res.M_matrix[i][j] = value_semiring::addition(res.M_matrix[i][j], 
            value_semiring::multiplication(M_matrix[i][k], rhs.M_matrix[k][j]));
        }
      }
    }
    return res;
  }
 
  matrix operator * (const value_type &rhs) const { return matrix(*this) *= rhs; }
  matrix& operator *= (const value_type &rhs)  { 
    for (auto &vec: M_matrix) {
      for (auto &x: vec) {
        x = value_semiring::multiplication(x, rhs);
      }
    }
    return *this;
  }
 
  matrix power(uint64_t exp) const {
    matrix res(height(), width()), use(*this);
    for (size_type i = 0; i < height(); ++i) {
      res[i][i] = value_semiring::multiplication_identity();
    }
    while (exp > 0) {
      if (exp & 1) {
        res *= use;
      }
      use *= use;
      exp >>= 1;
    }
    return res;
  }

  std::vector<value_type>& operator [] (size_type index) {
    return M_matrix[index];
  }
  size_type height() const {
    return M_matrix.size();
  }
  size_type width() const {
    if (M_matrix.empty()) return 0;
    return M_matrix.front().size();
  }
  bool empty() const {
    return M_matrix.empty();
  }
  void clear() {
    M_matrix.clear();
    M_matrix.shrink_to_fit();
  }

};

/**
 * @title Matrix
 */
#line 6 "test/matrix.test.cpp"

#line 9 "test/matrix.test.cpp"

using m32 = mint32_t<1000000007>;

struct semiring {
  struct value_structure {
    using type = m32;
    static type addition_identity() { return m32(0); }
    static type addition(const type& v1, const type& v2) { 
      return v1 + v2;
    }
    static type multiplication_identity() { return m32(1); }
    static type multiplication(const type& v1, const type& v2) { 
      return v1 * v2;
    }
  };
};

int main() {
  int64_t N;
  std::cin >> N;
  int32_t a, b, c;
  std::cin >> a >> b >> c;
  using matrix_t = matrix<semiring>;
  matrix_t mult({ 
    { m32(1), m32(0), m32(-1) },
    { m32(-1), m32(1), m32(0) },
    { m32(0), m32(-1), m32(1) },
  });
  matrix_t start({
    { m32(a), m32(b), m32(c) }
  });
  start *= mult.power(N - 1);
  std::cout << start[0][0] << ' ' << start[0][1] << ' ' << start[0][2] << '\n';
  return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

