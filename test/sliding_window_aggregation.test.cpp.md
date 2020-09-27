---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: container/sliding_window_aggregation.cpp
    title: Sliding Window Aggregation
  - icon: ':heavy_check_mark:'
    path: other/monoid.cpp
    title: Monoid Utility
  - icon: ':heavy_check_mark:'
    path: algebraic/modular.cpp
    title: Modint
  - icon: ':heavy_check_mark:'
    path: algebraic/mod_inv.cpp
    title: Extended GCD
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/queue_operate_all_composite
    links:
    - https://judge.yosupo.jp/problem/queue_operate_all_composite
  bundledCode: "#line 1 \"test/sliding_window_aggregation.test.cpp\"\n\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/queue_operate_all_composite\"\n\n#line 2 \"\
    container/sliding_window_aggregation.cpp\"\n\n#line 2 \"other/monoid.cpp\"\n\n\
    #include <type_traits>\n#include <utility>\n#include <stdexcept>\n\ntemplate <class\
    \ T, class = void>\nclass has_identity: public std::false_type { };\n\ntemplate\
    \ <class T>\nclass has_identity<T, typename std::conditional<false, decltype(T::identity()),\
    \ void>::type>: public std::true_type { };\n\ntemplate <class T>\nconstexpr typename\
    \ std::enable_if<has_identity<T>::value, typename T::type>::type empty_exception()\
    \ {\n  return T::identity();\n}\ntemplate <class T>\n[[noreturn]] typename std::enable_if<!has_identity<T>::value,\
    \ typename T::type>::type empty_exception() {\n  throw std::runtime_error(\"type\
    \ T has no identity\");\n}\n\ntemplate <class T, bool HasIdentity>\nclass fixed_monoid_impl:\
    \ public T {\npublic:\n  using type = typename T::type;\n\n  static constexpr\
    \ type convert(const type &value) { return value; }\n  static constexpr type revert(const\
    \ type &value) { return value; }\n\n  template <class Mapping, class Value, class...\
    \ Args>\n  static constexpr void operate(Mapping &&func, Value &value, const type\
    \ &op, Args&&... args) {\n    value = func(value, op, std::forward<Args>(args)...);\n\
    \  }\n  template <class Constraint>\n  static constexpr bool satisfies(Constraint\
    \ &&func, const type &value) {\n    return func(value);\n  }\n};\n\ntemplate <class\
    \ T>\nclass fixed_monoid_impl<T, false> {\npublic:\n  class type {\n  public:\n\
    \    typename T::type value;\n    bool state;\n  \n    explicit constexpr type():\
    \ value(typename T::type { }), state(false) { }\n    explicit constexpr type(const\
    \ typename T::type &value): value(value), state(true) { }\n  };\n\n  static constexpr\
    \ type convert(const typename T::type &value) { return type(value); }\n  static\
    \ constexpr typename T::type revert(const type &value) { \n    if (!value.state)\
    \ throw std::runtime_error(\"attempted to revert identity to non-monoid\"); \n\
    \    return value.value; \n  }\n\n  static constexpr type identity() { return\
    \ type(); }\n  static constexpr type operation(const type &v1, const type &v2)\
    \ {\n    if (!v1.state) return v2;\n    if (!v2.state) return v1;\n    return\
    \ type(T::operation(v1.value, v2.value));\n  }\n\n  template <class Mapping, class\
    \ Value, class... Args>\n  static constexpr void operate(Mapping &&func, Value\
    \ &value, const type &op, Args&&... args) {\n    if (!op.state) return;\n    value\
    \ = func(value, op.value, std::forward<Args>(args)...);\n  }\n  template <class\
    \ Constraint>\n  static constexpr bool satisfies(Constraint &&func, const type\
    \ &value) {\n    if (!value.state) return false;\n    return func(value.value);\n\
    \  }\n};\n\ntemplate <class T>\nusing fixed_monoid = fixed_monoid_impl<T, has_identity<T>::value>;\n\
    \n/**\n * @title Monoid Utility\n */\n#line 4 \"container/sliding_window_aggregation.cpp\"\
    \n\n#include <cstddef>\n#include <stack>\n#include <cassert>\n\ntemplate <class\
    \ SemiGroup>\nclass sliding_window_aggregation {\npublic:\n  using structure \
    \      = SemiGroup;\n  using value_semigroup = typename SemiGroup::value_structure;\n\
    \  using value_type      = typename SemiGroup::value_structure::type;\n  using\
    \ size_type       = size_t;\n\nprivate:\n  class node_type {\n  public:\n    value_type\
    \ value, sum;\n    node_type(const value_type &value, const value_type &sum):\
    \ value(value), sum(sum) { }\n  };\n\n  std::stack<node_type> M_front, M_back;\n\
    \npublic:\n  sliding_window_aggregation(): M_front(), M_back() { }\n\n  value_type\
    \ fold() const {\n    if (empty()) return empty_exception<value_semigroup>();\n\
    \    if (M_front.empty()) return M_back.top().sum;\n    else if (M_back.empty())\
    \ return M_front.top().sum;\n    return value_semigroup::operation(M_front.top().sum,\
    \ M_back.top().sum);\n  }\n\n  void push(const value_type &x) {\n    if (M_back.empty())\
    \ M_back.emplace(x, x);\n    else {\n      value_type tmp = value_semigroup::operation(M_back.top().sum,\
    \ x);\n      M_back.emplace(x, tmp);\n    }\n  }\n  void pop() {\n    assert(!empty());\n\
    \    if (M_front.empty()) {\n      M_front.emplace(M_back.top().value, M_back.top().value);\n\
    \      M_back.pop();\n      while (!M_back.empty()) {\n        value_type tmp\
    \ = value_semigroup::operation(M_back.top().value, M_front.top().sum);\n     \
    \   M_front.emplace(M_back.top().value, tmp);\n        M_back.pop();\n      }\n\
    \    }\n    M_front.pop();\n  }\n\n  size_type size() const {\n    return M_front.size()\
    \ + M_back.size();\n  }\n  bool empty() const {\n    return M_front.empty() &&\
    \ M_back.empty();\n  }\n};\n\n/**\n * @title Sliding Window Aggregation\n */\n\
    #line 2 \"algebraic/modular.cpp\"\n\n#line 2 \"algebraic/mod_inv.cpp\"\n\n#line\
    \ 4 \"algebraic/mod_inv.cpp\"\n#include <cstdint>\n\nconstexpr std::pair<int64_t,\
    \ int64_t> mod_inv(int64_t a, int64_t b) {\n  if ((a %= b) == 0) return { b, 0\
    \ };\n  int64_t s = b, t = (a < 0 ? a + b : a);\n  int64_t m0 = 0, m1 = 1, tmp\
    \ = 0;\n  while (t > 0) {\n    const auto u = s / t;\n    s -= t * u; m0 -= m1\
    \ * u;\n    tmp = s; s = t; t = tmp; tmp = m0; m0 = m1; m1 = tmp;\n  }\n  return\
    \ { s, (m0 < 0 ? m0 + b / s : m0) };\n}\n\n/**\n * @title Extended GCD\n */\n\
    #line 4 \"algebraic/modular.cpp\"\n\n#line 6 \"algebraic/modular.cpp\"\n#include\
    \ <iostream>\n#line 9 \"algebraic/modular.cpp\"\n\ntemplate <class Modulus>\n\
    class modular {\npublic:\n  using value_type = uint32_t;\n  using cover_type =\
    \ uint64_t;\n \n  static constexpr uint32_t mod() { return Modulus::mod(); }\n\
    \  template <class T>\n  static constexpr value_type normalize(T value_) noexcept\
    \ {\n    if (value_ < 0) {\n      value_ = -value_;\n      value_ %= mod();\n\
    \      if (value_ == 0) return 0;\n      return mod() - value_;\n    }\n    return\
    \ value_ % mod();\n  }\n\nprivate:\n  value_type value;\n\n  template <bool IsPrime,\
    \ std::enable_if_t<IsPrime>* = nullptr>\n  constexpr modular inverse_helper()\
    \ const noexcept { return power(*this, mod() - 2); }\n  template <bool IsPrime,\
    \ std::enable_if_t<!IsPrime>* = nullptr>\n  constexpr modular inverse_helper()\
    \ const noexcept {\n    const auto tmp = mod_inv(value, mod());\n    assert(tmp.first\
    \ == 1);\n    return modular(tmp.second);\n  }\n\npublic:\n  constexpr modular()\
    \ noexcept : value(0) { }\n  template <class T>\n  explicit constexpr modular(T\
    \ value_) noexcept : value(normalize(value_)) { }\n  template <class T>\n  explicit\
    \ constexpr operator T() const noexcept { return static_cast<T>(value); }\n \n\
    \  constexpr value_type get() const noexcept { return value; }\n  constexpr value_type\
    \ &extract() noexcept { return value; }\n  constexpr modular operator - () const\
    \ noexcept { return modular(mod() - value); }\n  constexpr modular operator ~\
    \ () const noexcept { return inverse(*this); }\n \n  constexpr modular operator\
    \ + (const modular &rhs) const noexcept { return modular(*this) += rhs; }\n  constexpr\
    \ modular& operator += (const modular &rhs) noexcept { \n    if ((value += rhs.value)\
    \ >= mod()) value -= mod(); \n    return *this; \n  }\n \n  constexpr modular\
    \ operator - (const modular &rhs) const noexcept { return modular(*this) -= rhs;\
    \ }\n  constexpr modular& operator -= (const modular &rhs) noexcept { \n    if\
    \ ((value += mod() - rhs.value) >= mod()) value -= mod(); \n    return *this;\
    \ \n  }\n \n  constexpr modular operator * (const modular &rhs) const noexcept\
    \ { return modular(*this) *= rhs; }\n  constexpr modular& operator *= (const modular\
    \ &rhs) noexcept { \n    value = (cover_type) value * rhs.value % mod();\n   \
    \ return *this;\n  }\n \n  constexpr modular operator / (const modular &rhs) const\
    \ noexcept { return modular(*this) /= rhs; }\n  constexpr modular& operator /=\
    \ (const modular &rhs) noexcept { return (*this) *= inverse(rhs); }\n \n  constexpr\
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
    \ constexpr bool is_prime = IsPrime;\n};\n\ntemplate <uint32_t Mod, bool IsPrime\
    \ = true>\nusing mint32_t = modular<static_modulus<Mod, IsPrime>>;\nusing rmint32_t\
    \ = modular<dynamic_modulus<>>;\n\n/*\n * @title Modint\n */\n#line 6 \"test/sliding_window_aggregation.test.cpp\"\
    \n\n#line 10 \"test/sliding_window_aggregation.test.cpp\"\n#include <vector>\n\
    \nusing m32 = mint32_t<998244353>;\n\nstruct st_monoid {\n  struct value_structure\
    \ {\n    using type = std::pair<m32, m32>;\n    static type identity() { return\
    \ { m32(1), m32(0) }; }\n    static type operation(const type& v1, const type&\
    \ v2) { \n      return { v2.first * v1.first, v2.first * v1.second + v2.second\
    \ };\n    }\n  };\n};\n\nint main() {\n  size_t Q;\n  std::cin >> Q;\n  sliding_window_aggregation<st_monoid>\
    \ que;\n  while (Q--) {\n    size_t type;\n    std::cin >> type;\n    if (type\
    \ == 0) {\n      m32 a, b;\n      std::cin >> a.extract() >> b.extract();\n  \
    \    que.push({ a, b });\n    }\n    else if (type == 1) {\n      que.pop();\n\
    \    }\n    else {\n      m32 x;\n      std::cin >> x.extract();\n      auto fold\
    \ = que.fold();\n      std::cout << fold.first * x + fold.second << '\\n';\n \
    \   }\n  }\n  return 0;\n}\n"
  code: "\n#define PROBLEM \"https://judge.yosupo.jp/problem/queue_operate_all_composite\"\
    \n\n#include \"../container/sliding_window_aggregation.cpp\"\n#include \"../algebraic/modular.cpp\"\
    \n\n#include <iostream>\n#include <cstddef>\n#include <cstdint>\n#include <vector>\n\
    \nusing m32 = mint32_t<998244353>;\n\nstruct st_monoid {\n  struct value_structure\
    \ {\n    using type = std::pair<m32, m32>;\n    static type identity() { return\
    \ { m32(1), m32(0) }; }\n    static type operation(const type& v1, const type&\
    \ v2) { \n      return { v2.first * v1.first, v2.first * v1.second + v2.second\
    \ };\n    }\n  };\n};\n\nint main() {\n  size_t Q;\n  std::cin >> Q;\n  sliding_window_aggregation<st_monoid>\
    \ que;\n  while (Q--) {\n    size_t type;\n    std::cin >> type;\n    if (type\
    \ == 0) {\n      m32 a, b;\n      std::cin >> a.extract() >> b.extract();\n  \
    \    que.push({ a, b });\n    }\n    else if (type == 1) {\n      que.pop();\n\
    \    }\n    else {\n      m32 x;\n      std::cin >> x.extract();\n      auto fold\
    \ = que.fold();\n      std::cout << fold.first * x + fold.second << '\\n';\n \
    \   }\n  }\n  return 0;\n}\n"
  dependsOn:
  - container/sliding_window_aggregation.cpp
  - other/monoid.cpp
  - algebraic/modular.cpp
  - algebraic/mod_inv.cpp
  isVerificationFile: true
  path: test/sliding_window_aggregation.test.cpp
  requiredBy: []
  timestamp: '2020-09-27 11:10:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/sliding_window_aggregation.test.cpp
layout: document
redirect_from:
- /verify/test/sliding_window_aggregation.test.cpp
- /verify/test/sliding_window_aggregation.test.cpp.html
title: test/sliding_window_aggregation.test.cpp
---
