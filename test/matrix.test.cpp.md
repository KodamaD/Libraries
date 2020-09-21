---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algebraic/modular.cpp
    title: Modint
  - icon: ':heavy_check_mark:'
    path: algebraic/mod_inv.cpp
    title: Extended GCD
  - icon: ':heavy_check_mark:'
    path: container/matrix.cpp
    title: Matrix
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/1105
    links:
    - https://yukicoder.me/problems/no/1105
  bundledCode: "#line 1 \"test/matrix.test.cpp\"\n\n#define PROBLEM \"https://yukicoder.me/problems/no/1105\"\
    \n\n#line 2 \"algebraic/modular.cpp\"\n\n#line 2 \"algebraic/mod_inv.cpp\"\n\n\
    #include <utility>\n#include <cstdint>\n\nconstexpr std::pair<int64_t, int64_t>\
    \ mod_inv(int64_t a, int64_t b) {\n  if ((a %= b) == 0) return { b, 0 };\n  int64_t\
    \ s = b, t = (a < 0 ? a + b : a);\n  int64_t m0 = 0, m1 = 1, tmp = 0;\n  while\
    \ (t > 0) {\n    const auto u = s / t;\n    s -= t * u; m0 -= m1 * u;\n    tmp\
    \ = s; s = t; t = tmp; tmp = m0; m0 = m1; m1 = tmp;\n  }\n  return { s, (m0 <\
    \ 0 ? m0 + b / s : m0) };\n}\n\n/**\n * @title Extended GCD\n */\n#line 4 \"algebraic/modular.cpp\"\
    \n\n#line 6 \"algebraic/modular.cpp\"\n#include <iostream>\n#include <cassert>\n\
    #include <type_traits>\n\ntemplate <class Modulus>\nclass modular {\npublic:\n\
    \  using value_type = uint32_t;\n  using cover_type = uint64_t;\n \n  template\
    \ <class T>\n  static constexpr value_type normalize(T value_) noexcept {\n  \
    \  if (value_ < 0) {\n      value_ = -value_;\n      value_ %= Modulus::mod();\n\
    \      if (value_ == 0) return 0;\n      return Modulus::mod() - value_;\n   \
    \ }\n    return value_ % Modulus::mod();\n  }\n\nprivate:\n  value_type value;\n\
    \n  template <bool IsPrime, std::enable_if_t<IsPrime>* = nullptr>\n  constexpr\
    \ modular inverse_helper() const noexcept { return power(*this, Modulus::mod()\
    \ - 2); }\n  template <bool IsPrime, std::enable_if_t<!IsPrime>* = nullptr>\n\
    \  constexpr modular inverse_helper() const noexcept {\n    const auto tmp = mod_inv(value,\
    \ Modulus::mod());\n    assert(tmp.first == 1);\n    return modular(tmp.second);\n\
    \  }\n\npublic:\n  constexpr modular() noexcept : value(0) { }\n  template <class\
    \ T>\n  explicit constexpr modular(T value_) noexcept : value(normalize(value_))\
    \ { }\n  template <class T>\n  explicit constexpr operator T() const noexcept\
    \ { return static_cast<T>(value); }\n \n  constexpr value_type get() const noexcept\
    \ { return value; }\n  constexpr value_type &extract() noexcept { return value;\
    \ }\n  constexpr modular operator - () const noexcept { return modular(Modulus::mod()\
    \ - value); }\n  constexpr modular operator ~ () const noexcept { return inverse(*this);\
    \ }\n \n  constexpr modular operator + (const modular &rhs) const noexcept { return\
    \ modular(*this) += rhs; }\n  constexpr modular& operator += (const modular &rhs)\
    \ noexcept { \n    if ((value += rhs.value) >= Modulus::mod()) value -= Modulus::mod();\
    \ \n    return *this; \n  }\n \n  constexpr modular operator - (const modular\
    \ &rhs) const noexcept { return modular(*this) -= rhs; }\n  constexpr modular&\
    \ operator -= (const modular &rhs) noexcept { \n    if ((value += Modulus::mod()\
    \ - rhs.value) >= Modulus::mod()) value -= Modulus::mod(); \n    return *this;\
    \ \n  }\n \n  constexpr modular operator * (const modular &rhs) const noexcept\
    \ { return modular(*this) *= rhs; }\n  constexpr modular& operator *= (const modular\
    \ &rhs) noexcept { \n    value = (cover_type) value * rhs.value % Modulus::mod();\n\
    \    return *this;\n  }\n \n  constexpr modular operator / (const modular &rhs)\
    \ const noexcept { return modular(*this) /= rhs; }\n  constexpr modular& operator\
    \ /= (const modular &rhs) noexcept { return (*this) *= inverse(rhs); }\n \n  constexpr\
    \ bool zero() const noexcept { return value == 0; }\n  constexpr bool operator\
    \ == (const modular &rhs) const noexcept { return value == rhs.value; }\n  constexpr\
    \ bool operator != (const modular &rhs) const noexcept { return value != rhs.value;\
    \ }\n \n  friend std::ostream& operator << (std::ostream &stream, const modular\
    \ &rhs) { return stream << rhs.value; }\n  friend constexpr modular inverse(const\
    \ modular &val) noexcept { return val.inverse_helper<Modulus::is_prime>(); }\n\
    \  friend constexpr modular power(modular val, cover_type exp) noexcept { \n \
    \   modular res(1);\n    for (; exp > 0; exp >>= 1, val *= val) if (exp & 1) res\
    \ *= val;\n    return res;\n  }\n \n};\n \ntemplate <uint32_t Mod, bool IsPrime\
    \ = true>\nstruct static_modulus { \n  static constexpr uint32_t mod() noexcept\
    \ { return Mod; } \n  static constexpr bool is_prime = IsPrime;\n};\n\ntemplate\
    \ <uint32_t Id = 0, bool IsPrime = false>\nstruct dynamic_modulus {\n  static\
    \ uint32_t &mod() noexcept { static uint32_t val = 0; return val; }\n  static\
    \ constexpr bool is_prime = IsPrime;\n};\n\ntemplate <uint32_t Mod>\nusing mint32_t\
    \ = modular<static_modulus<Mod>>;\nusing rmint32_t = modular<dynamic_modulus<>>;\n\
    \n/*\n * @title Modint\n */\n#line 2 \"container/matrix.cpp\"\n\n#include <cstddef>\n\
    #line 5 \"container/matrix.cpp\"\n#include <vector>\n#include <algorithm>\n#include\
    \ <iterator>\n#include <initializer_list>\n#line 10 \"container/matrix.cpp\"\n\
    \ntemplate <class SemiRing>\nclass matrix {\npublic:\n  using structure      =\
    \ SemiRing;\n  using value_semiring = typename SemiRing::value_structure;\n  using\
    \ value_type     = typename SemiRing::value_structure::type;\n  using size_type\
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
    \  }\n};\n\n/**\n * @title Matrix\n */\n#line 6 \"test/matrix.test.cpp\"\n\n#line\
    \ 9 \"test/matrix.test.cpp\"\n\nusing m32 = mint32_t<1000000007>;\n\nstruct semiring\
    \ {\n  struct value_structure {\n    using type = m32;\n    static type addition_identity()\
    \ { return m32(0); }\n    static type addition(const type& v1, const type& v2)\
    \ { \n      return v1 + v2;\n    }\n    static type multiplication_identity()\
    \ { return m32(1); }\n    static type multiplication(const type& v1, const type&\
    \ v2) { \n      return v1 * v2;\n    }\n  };\n};\n\nint main() {\n  int64_t N;\n\
    \  std::cin >> N;\n  int32_t a, b, c;\n  std::cin >> a >> b >> c;\n  using matrix_t\
    \ = matrix<semiring>;\n  matrix_t mult({ \n    { m32(1), m32(0), m32(-1) },\n\
    \    { m32(-1), m32(1), m32(0) },\n    { m32(0), m32(-1), m32(1) },\n  });\n \
    \ matrix_t start({\n    { m32(a), m32(b), m32(c) }\n  });\n  start *= mult.power(N\
    \ - 1);\n  std::cout << start[0][0] << ' ' << start[0][1] << ' ' << start[0][2]\
    \ << '\\n';\n  return 0;\n}\n"
  code: "\n#define PROBLEM \"https://yukicoder.me/problems/no/1105\"\n\n#include \"\
    ../algebraic/modular.cpp\"\n#include \"../container/matrix.cpp\"\n\n#include <iostream>\n\
    #include <cstdint>\n\nusing m32 = mint32_t<1000000007>;\n\nstruct semiring {\n\
    \  struct value_structure {\n    using type = m32;\n    static type addition_identity()\
    \ { return m32(0); }\n    static type addition(const type& v1, const type& v2)\
    \ { \n      return v1 + v2;\n    }\n    static type multiplication_identity()\
    \ { return m32(1); }\n    static type multiplication(const type& v1, const type&\
    \ v2) { \n      return v1 * v2;\n    }\n  };\n};\n\nint main() {\n  int64_t N;\n\
    \  std::cin >> N;\n  int32_t a, b, c;\n  std::cin >> a >> b >> c;\n  using matrix_t\
    \ = matrix<semiring>;\n  matrix_t mult({ \n    { m32(1), m32(0), m32(-1) },\n\
    \    { m32(-1), m32(1), m32(0) },\n    { m32(0), m32(-1), m32(1) },\n  });\n \
    \ matrix_t start({\n    { m32(a), m32(b), m32(c) }\n  });\n  start *= mult.power(N\
    \ - 1);\n  std::cout << start[0][0] << ' ' << start[0][1] << ' ' << start[0][2]\
    \ << '\\n';\n  return 0;\n}\n"
  dependsOn:
  - algebraic/modular.cpp
  - algebraic/mod_inv.cpp
  - container/matrix.cpp
  isVerificationFile: true
  path: test/matrix.test.cpp
  requiredBy: []
  timestamp: '2020-09-21 19:57:57+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/matrix.test.cpp
layout: document
redirect_from:
- /verify/test/matrix.test.cpp
- /verify/test/matrix.test.cpp.html
title: test/matrix.test.cpp
---
