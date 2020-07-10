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


# :heavy_check_mark: Matrix

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5f0b6ebc4bea10285ba2b8a6ce78b863">container</a>
* <a href="{{ site.github.repository_url }}/blob/master/container/matrix.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-10 23:59:47+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/matrix.test.cpp.html">test/matrix.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <iterator>
#include <initializer_list>

template <class SemiRing>
class matrix {
public:
  using structure       = SemiRing;
  using value_structure = typename SemiRing::value_structure;
  using value_type      = typename SemiRing::value_structure::type;
  using size_type       = size_t;

private:
  std::vector<std::vector<value_type>> M_matrix;

public:
  matrix() = default;
  explicit matrix(size_type H, size_type W, 
    const value_type &value = value_structure::addition_identity()) { initialize(H, W, value); }
  explicit matrix(const std::vector<std::vector<value_type>> &cont) { construct(cont); }
  explicit matrix(const std::initializer_list<std::initializer_list<value_type>> &cont) { construct(cont); }

  void initialize(size_type H, size_type W, const value_type &value = value_structure::addition_identity()) {
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
        M_matrix[i][j] = value_structure::addition(M_matrix[i][j], rhs.M_matrix[i][j]);
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
          res.M_matrix[i][j] = value_structure::addition(res.M_matrix[i][j], 
            value_structure::multiplication(M_matrix[i][k], rhs.M_matrix[k][j]));
        }
      }
    }
    return res;
  }
 
  matrix operator * (const value_type &rhs) const { return matrix(*this) *= rhs; }
  matrix& operator *= (const value_type &rhs)  { 
    for (auto &vec: M_matrix) {
      for (auto &x: vec) {
        x = value_structure::multiplication(x, rhs);
      }
    }
    return *this;
  }
 
  matrix power(uint64_t exp) const {
    matrix res(height(), width()), use(*this);
    for (size_type i = 0; i < height(); ++i) {
      res[i][i] = value_structure::multiplication_identity();
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
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "container/matrix.cpp"

#include <cstddef>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <iterator>
#include <initializer_list>

template <class SemiRing>
class matrix {
public:
  using structure       = SemiRing;
  using value_structure = typename SemiRing::value_structure;
  using value_type      = typename SemiRing::value_structure::type;
  using size_type       = size_t;

private:
  std::vector<std::vector<value_type>> M_matrix;

public:
  matrix() = default;
  explicit matrix(size_type H, size_type W, 
    const value_type &value = value_structure::addition_identity()) { initialize(H, W, value); }
  explicit matrix(const std::vector<std::vector<value_type>> &cont) { construct(cont); }
  explicit matrix(const std::initializer_list<std::initializer_list<value_type>> &cont) { construct(cont); }

  void initialize(size_type H, size_type W, const value_type &value = value_structure::addition_identity()) {
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
        M_matrix[i][j] = value_structure::addition(M_matrix[i][j], rhs.M_matrix[i][j]);
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
          res.M_matrix[i][j] = value_structure::addition(res.M_matrix[i][j], 
            value_structure::multiplication(M_matrix[i][k], rhs.M_matrix[k][j]));
        }
      }
    }
    return res;
  }
 
  matrix operator * (const value_type &rhs) const { return matrix(*this) *= rhs; }
  matrix& operator *= (const value_type &rhs)  { 
    for (auto &vec: M_matrix) {
      for (auto &x: vec) {
        x = value_structure::multiplication(x, rhs);
      }
    }
    return *this;
  }
 
  matrix power(uint64_t exp) const {
    matrix res(height(), width()), use(*this);
    for (size_type i = 0; i < height(); ++i) {
      res[i][i] = value_structure::multiplication_identity();
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

