---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/matrix.test.cpp
    title: test/matrix.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Matrix
    links: []
  bundledCode: "#line 2 \"container/matrix.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    #include <vector>\n#include <algorithm>\n#include <iterator>\n#include <initializer_list>\n\
    #include <cassert>\n\ntemplate <class SemiRing>\nclass matrix {\npublic:\n  using\
    \ structure      = SemiRing;\n  using value_semiring = typename SemiRing::value_structure;\n\
    \  using value_type     = typename SemiRing::value_structure::type;\n  using size_type\
    \      = size_t;\n\nprivate:\n  std::vector<std::vector<value_type>> M_matrix;\n\
    \npublic:\n  matrix() = default;\n  explicit matrix(size_type H, size_type W,\
    \ \n    const value_type &value = value_semiring::addition_identity()) { initialize(H,\
    \ W, value); }\n  matrix(const std::vector<std::vector<value_type>> &cont) { construct(cont);\
    \ }\n  matrix(const std::initializer_list<std::initializer_list<value_type>> &cont)\
    \ { construct(cont); }\n\n  void initialize(size_type H, size_type W, const value_type\
    \ &value = value_semiring::addition_identity()) {\n    clear();\n    M_matrix.assign(H,\
    \ std::vector<value_type>(W, value));\n  }\n  void construct(const std::vector<std::vector<value_type>>\
    \ &cont) {\n    clear();\n    M_matrix = cont;\n  }\n  void construct(const std::initializer_list<std::initializer_list<value_type>>\
    \ &cont) {\n    clear();\n    if (cont.size() > 0) {\n      M_matrix.reserve(cont.size());\n\
    \      std::transform(cont.begin(), cont.end(), std::back_inserter(M_matrix),\
    \ [](const auto &vec) {\n        return std::vector<value_type>(vec.begin(), vec.end());\n\
    \      });\n    }\n  }\n  void fill(const value_type &value) {\n    for (auto\
    \ &vec: M_matrix) {\n      std::fill(vec.begin(), vec.end(), value);\n    }\n\
    \  }\n\n  matrix operator + (const matrix &rhs) const { return matrix(*this) +=\
    \ rhs; }\n  matrix& operator += (const matrix &rhs) { \n    assert(height() ==\
    \ rhs.height());\n    assert(width() == rhs.width());\n    for (size_type i =\
    \ 0; i < height(); ++i) {\n      for (size_type j = 0; j < width(); ++j) {\n \
    \       M_matrix[i][j] = value_semiring::addition(M_matrix[i][j], rhs.M_matrix[i][j]);\n\
    \      }\n    }\n    return *this;\n  }\n\n  matrix& operator *= (const matrix\
    \ &rhs) { *this = (*this) * rhs; return *this; }\n  matrix operator * (const matrix\
    \ &rhs) const {\n    assert(width() == rhs.height());\n    matrix res(height(),\
    \ rhs.width());\n    for (size_type i = 0; i < height(); ++i) {\n      for (size_type\
    \ k = 0; k < width(); ++k) {\n        for (size_type j = 0; j < rhs.width(); ++j)\
    \ {\n          res.M_matrix[i][j] = value_semiring::addition(res.M_matrix[i][j],\
    \ \n            value_semiring::multiplication(M_matrix[i][k], rhs.M_matrix[k][j]));\n\
    \        }\n      }\n    }\n    return res;\n  }\n \n  matrix operator * (const\
    \ value_type &rhs) const { return matrix(*this) *= rhs; }\n  matrix& operator\
    \ *= (const value_type &rhs)  { \n    for (auto &vec: M_matrix) {\n      for (auto\
    \ &x: vec) {\n        x = value_semiring::multiplication(x, rhs);\n      }\n \
    \   }\n    return *this;\n  }\n \n  matrix power(uint64_t exp) const {\n    assert(height()\
    \ == width());\n    matrix res(height(), width()), use(*this);\n    for (size_type\
    \ i = 0; i < height(); ++i) {\n      res[i][i] = value_semiring::multiplication_identity();\n\
    \    }\n    while (exp > 0) {\n      if (exp & 1) {\n        res *= use;\n   \
    \   }\n      use *= use;\n      exp >>= 1;\n    }\n    return res;\n  }\n\n  std::vector<value_type>&\
    \ operator [] (size_type index) {\n    return M_matrix[index];\n  }\n  const std::vector<value_type>&\
    \ operator [] (size_type index) const {\n    return M_matrix[index];\n  }\n  size_type\
    \ height() const {\n    return M_matrix.size();\n  }\n  size_type width() const\
    \ {\n    if (M_matrix.empty()) return 0;\n    return M_matrix.front().size();\n\
    \  }\n  void clear() {\n    M_matrix.clear();\n    M_matrix.shrink_to_fit();\n\
    \  }\n};\n\n/**\n * @title Matrix\n */\n"
  code: "#pragma once\n\n#include <cstddef>\n#include <cstdint>\n#include <vector>\n\
    #include <algorithm>\n#include <iterator>\n#include <initializer_list>\n#include\
    \ <cassert>\n\ntemplate <class SemiRing>\nclass matrix {\npublic:\n  using structure\
    \      = SemiRing;\n  using value_semiring = typename SemiRing::value_structure;\n\
    \  using value_type     = typename SemiRing::value_structure::type;\n  using size_type\
    \      = size_t;\n\nprivate:\n  std::vector<std::vector<value_type>> M_matrix;\n\
    \npublic:\n  matrix() = default;\n  explicit matrix(size_type H, size_type W,\
    \ \n    const value_type &value = value_semiring::addition_identity()) { initialize(H,\
    \ W, value); }\n  matrix(const std::vector<std::vector<value_type>> &cont) { construct(cont);\
    \ }\n  matrix(const std::initializer_list<std::initializer_list<value_type>> &cont)\
    \ { construct(cont); }\n\n  void initialize(size_type H, size_type W, const value_type\
    \ &value = value_semiring::addition_identity()) {\n    clear();\n    M_matrix.assign(H,\
    \ std::vector<value_type>(W, value));\n  }\n  void construct(const std::vector<std::vector<value_type>>\
    \ &cont) {\n    clear();\n    M_matrix = cont;\n  }\n  void construct(const std::initializer_list<std::initializer_list<value_type>>\
    \ &cont) {\n    clear();\n    if (cont.size() > 0) {\n      M_matrix.reserve(cont.size());\n\
    \      std::transform(cont.begin(), cont.end(), std::back_inserter(M_matrix),\
    \ [](const auto &vec) {\n        return std::vector<value_type>(vec.begin(), vec.end());\n\
    \      });\n    }\n  }\n  void fill(const value_type &value) {\n    for (auto\
    \ &vec: M_matrix) {\n      std::fill(vec.begin(), vec.end(), value);\n    }\n\
    \  }\n\n  matrix operator + (const matrix &rhs) const { return matrix(*this) +=\
    \ rhs; }\n  matrix& operator += (const matrix &rhs) { \n    assert(height() ==\
    \ rhs.height());\n    assert(width() == rhs.width());\n    for (size_type i =\
    \ 0; i < height(); ++i) {\n      for (size_type j = 0; j < width(); ++j) {\n \
    \       M_matrix[i][j] = value_semiring::addition(M_matrix[i][j], rhs.M_matrix[i][j]);\n\
    \      }\n    }\n    return *this;\n  }\n\n  matrix& operator *= (const matrix\
    \ &rhs) { *this = (*this) * rhs; return *this; }\n  matrix operator * (const matrix\
    \ &rhs) const {\n    assert(width() == rhs.height());\n    matrix res(height(),\
    \ rhs.width());\n    for (size_type i = 0; i < height(); ++i) {\n      for (size_type\
    \ k = 0; k < width(); ++k) {\n        for (size_type j = 0; j < rhs.width(); ++j)\
    \ {\n          res.M_matrix[i][j] = value_semiring::addition(res.M_matrix[i][j],\
    \ \n            value_semiring::multiplication(M_matrix[i][k], rhs.M_matrix[k][j]));\n\
    \        }\n      }\n    }\n    return res;\n  }\n \n  matrix operator * (const\
    \ value_type &rhs) const { return matrix(*this) *= rhs; }\n  matrix& operator\
    \ *= (const value_type &rhs)  { \n    for (auto &vec: M_matrix) {\n      for (auto\
    \ &x: vec) {\n        x = value_semiring::multiplication(x, rhs);\n      }\n \
    \   }\n    return *this;\n  }\n \n  matrix power(uint64_t exp) const {\n    assert(height()\
    \ == width());\n    matrix res(height(), width()), use(*this);\n    for (size_type\
    \ i = 0; i < height(); ++i) {\n      res[i][i] = value_semiring::multiplication_identity();\n\
    \    }\n    while (exp > 0) {\n      if (exp & 1) {\n        res *= use;\n   \
    \   }\n      use *= use;\n      exp >>= 1;\n    }\n    return res;\n  }\n\n  std::vector<value_type>&\
    \ operator [] (size_type index) {\n    return M_matrix[index];\n  }\n  const std::vector<value_type>&\
    \ operator [] (size_type index) const {\n    return M_matrix[index];\n  }\n  size_type\
    \ height() const {\n    return M_matrix.size();\n  }\n  size_type width() const\
    \ {\n    if (M_matrix.empty()) return 0;\n    return M_matrix.front().size();\n\
    \  }\n  void clear() {\n    M_matrix.clear();\n    M_matrix.shrink_to_fit();\n\
    \  }\n};\n\n/**\n * @title Matrix\n */"
  dependsOn: []
  isVerificationFile: false
  path: container/matrix.cpp
  requiredBy: []
  timestamp: '2020-09-09 18:08:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/matrix.test.cpp
documentation_of: container/matrix.cpp
layout: document
redirect_from:
- /library/container/matrix.cpp
- /library/container/matrix.cpp.html
title: Matrix
---
