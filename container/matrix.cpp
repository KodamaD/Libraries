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