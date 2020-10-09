---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algebraic/mod_inv.cpp
    title: Extended GCD
  - icon: ':heavy_check_mark:'
    path: algebraic/modular.cpp
    title: Modint
  - icon: ':heavy_check_mark:'
    path: container/segment_tree.cpp
    title: Segment Tree
  - icon: ':heavy_check_mark:'
    path: other/bit_operation.cpp
    title: Bit Operations
  - icon: ':heavy_check_mark:'
    path: other/monoid.cpp
    title: Monoid Utility
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_set_range_composite
    links:
    - https://judge.yosupo.jp/problem/point_set_range_composite
  bundledCode: "#line 1 \"test/segment_tree.test.cpp\"\n\n#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\
    \n\n#line 2 \"container/segment_tree.cpp\"\n\n#line 2 \"other/monoid.cpp\"\n\n\
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
    \n/**\n * @title Monoid Utility\n */\n#line 2 \"other/bit_operation.cpp\"\n\n\
    #include <cstddef>\n#include <cstdint>\n\nconstexpr size_t bit_ppc(const uint64_t\
    \ x) { return __builtin_popcountll(x); }\nconstexpr size_t bit_ctzr(const uint64_t\
    \ x) { return x == 0 ? 64 : __builtin_ctzll(x); }\nconstexpr size_t bit_ctzl(const\
    \ uint64_t x) { return x == 0 ? 64 : __builtin_clzll(x); }\nconstexpr size_t bit_width(const\
    \ uint64_t x) { return 64 - bit_ctzl(x); }\nconstexpr uint64_t bit_msb(const uint64_t\
    \ x) { return x == 0 ? 0 : uint64_t(1) << (bit_width(x) - 1); }\nconstexpr uint64_t\
    \ bit_lsb(const uint64_t x) { return x & (-x); }\nconstexpr uint64_t bit_cover(const\
    \ uint64_t x) { return x == 0 ? 0 : bit_msb(2 * x - 1); }\n\nconstexpr uint64_t\
    \ bit_rev(uint64_t x) {\n  x = ((x >> 1) & 0x5555555555555555) | ((x & 0x5555555555555555)\
    \ << 1);\n  x = ((x >> 2) & 0x3333333333333333) | ((x & 0x3333333333333333) <<\
    \ 2);\n  x = ((x >> 4) & 0x0F0F0F0F0F0F0F0F) | ((x & 0x0F0F0F0F0F0F0F0F) << 4);\n\
    \  x = ((x >> 8) & 0x00FF00FF00FF00FF) | ((x & 0x00FF00FF00FF00FF) << 8);\n  x\
    \ = ((x >> 16) & 0x0000FFFF0000FFFF) | ((x & 0x0000FFFF0000FFFF) << 16);\n  x\
    \ = (x >> 32) | (x << 32);\n  return x;\n}\n\n/**\n * @title Bit Operations\n\
    \ */\n#line 5 \"container/segment_tree.cpp\"\n\n#line 7 \"container/segment_tree.cpp\"\
    \n#include <vector>\n#include <iterator>\n#include <algorithm>\n#line 12 \"container/segment_tree.cpp\"\
    \n#include <cassert>\n\ntemplate <class Monoid>\nclass segment_tree {\npublic:\n\
    \  using structure    = Monoid;\n  using value_monoid = typename Monoid::value_structure;\n\
    \  using value_type   = typename Monoid::value_structure::type;\n  using size_type\
    \    = size_t;\n\nprivate:\n  using fixed_value_monoid = fixed_monoid<value_monoid>;\n\
    \  using fixed_value_type   = typename fixed_value_monoid::type;\n\n  std::vector<fixed_value_type>\
    \ M_tree;\n\n  void M_fix_change(const size_type index) {\n    M_tree[index] =\
    \ fixed_value_monoid::operation(M_tree[index << 1 | 0], M_tree[index << 1 | 1]);\n\
    \  }\n\npublic:\n  segment_tree() = default;\n  explicit segment_tree(const size_type\
    \ size) { initialize(size); }\n  template <class InputIterator>\n  explicit segment_tree(InputIterator\
    \ first, InputIterator last) { construct(first, last); }\n\n  void initialize(const\
    \ size_type size) {\n    clear();\n    M_tree.assign(size << 1, fixed_value_monoid::identity());\n\
    \  }\n\n  template <class InputIterator>\n  void construct(InputIterator first,\
    \ InputIterator last) {\n    clear();\n    const size_type size = std::distance(first,\
    \ last);\n    M_tree.reserve(size << 1);\n    M_tree.assign(size, fixed_value_monoid::identity());\n\
    \    std::transform(first, last, std::back_inserter(M_tree), [&](const value_type\
    \ &value) {\n      return fixed_value_monoid::convert(value);\n    });\n    for\
    \ (size_type index = size - 1; index != 0; --index) {\n      M_fix_change(index);\n\
    \    }\n  }\n\n  void assign(size_type index, const value_type &value) {\n   \
    \ assert(index < size());\n    index += size();\n    M_tree[index] = fixed_value_monoid::convert(value);\n\
    \    while (index != 1) {\n      index >>= 1;\n      M_fix_change(index);\n  \
    \  } \n  }\n\n  value_type at(const size_type index) const { \n    assert(index\
    \ < size());\n    return fixed_value_monoid::revert(M_tree[index + size()]);\n\
    \  }\n\n  value_type fold(size_type first, size_type last) const {\n    assert(first\
    \ <= last);\n    assert(last <= size());\n    first += size();\n    last += size();\n\
    \    fixed_value_type fold_l = fixed_value_monoid::identity();\n    fixed_value_type\
    \ fold_r = fixed_value_monoid::identity();\n    while (first != last) {\n    \
    \  if (first & 1) {\n        fold_l = fixed_value_monoid::operation(fold_l, M_tree[first]);\n\
    \        ++first;\n      }\n      if (last & 1) {\n        --last;\n        fold_r\
    \ = fixed_value_monoid::operation(M_tree[last], fold_r);      \n      }\n    \
    \  first >>= 1;\n      last >>= 1;\n    }\n    return fixed_value_monoid::revert(fixed_value_monoid::operation(fold_l,\
    \ fold_r));\n  }\n\n  template <bool ToRight = true, class Constraint, std::enable_if_t<ToRight>*\
    \ = nullptr> \n  size_type satisfies(const size_type left, Constraint &&func)\
    \ const {\n    assert(left <= size());\n    if (fixed_value_monoid::satisfies(std::forward<Constraint>(func),\
    \ \n      fixed_value_monoid::identity())) return left;\n    size_type first =\
    \ left + size();\n    size_type last = 2 * size();\n    const size_type last_c\
    \ = last;\n    fixed_value_type fold = fixed_value_monoid::identity();\n    const\
    \ auto try_merge = [&](const size_type index) {\n      fixed_value_type tmp =\
    \ fixed_value_monoid::operation(fold, M_tree[index]);\n      if (fixed_value_monoid::satisfies(std::forward<Constraint>(func),\
    \ tmp)) return true;\n      fold = std::move(tmp);\n      return false;\n    };\n\
    \    const auto subtree = [&](size_type index) {\n      while (index < size())\
    \ {\n        index <<= 1;\n        if (!try_merge(index)) ++index;\n      }\n\
    \      return index - size() + 1;\n    };\n    size_type story = 0;\n    while\
    \ (first < last) {\n      if (first & 1) {\n        if (try_merge(first)) return\
    \ subtree(first);\n        ++first;\n      }\n      first >>= 1;\n      last >>=\
    \ 1;\n      ++story;\n    }\n    while (story--) {\n      last = last_c >> story;\n\
    \      if (last & 1) {\n        --last;\n        if (try_merge(last)) return subtree(last);\n\
    \      }\n    }\n    return size() + 1;\n  }\n\n  template <bool ToRight = true,\
    \ class Constraint, std::enable_if_t<!ToRight>* = nullptr> \n  size_type satisfies(const\
    \ size_type right, Constraint &&func) const {\n    assert(right <= size());\n\
    \    if (fixed_value_monoid::satisfies(std::forward<Constraint>(func), \n    \
    \  fixed_value_monoid::identity())) return right;\n    size_type first = size();\n\
    \    size_type last = right + size();\n    const size_type first_c = first;\n\
    \    fixed_value_type fold = fixed_value_monoid::identity();\n    const auto try_merge\
    \ = [&](const size_type index) {\n      fixed_value_type tmp = fixed_value_monoid::operation(M_tree[index],\
    \ fold);\n      if (fixed_value_monoid::satisfies(std::forward<Constraint>(func),\
    \ tmp)) return true;\n      fold = std::move(tmp);\n      return false;\n    };\n\
    \    const auto subtree = [&](size_type index) {\n      while (index < size())\
    \ {\n        index <<= 1;\n        if (try_merge(index + 1)) ++index;\n      }\n\
    \      return index - size();\n    };\n    size_type story = 0;\n    while (first\
    \ < last) {\n      if (first & 1) ++first;\n      if (last & 1) {\n        --last;\n\
    \        if (try_merge(last)) return subtree(last);\n      }\n      first >>=\
    \ 1;\n      last >>= 1;\n      ++story;\n    }\n    const size_type cover = bit_cover(first_c);\n\
    \    while (story--) {\n      first = (cover >> story) - ((cover - first_c) >>\
    \ story);\n      if (first & 1) {\n        if (try_merge(first)) return subtree(first);\n\
    \      }\n    }\n    return size_type(-1);\n  }\n\n  void clear() {\n    M_tree.clear();\n\
    \    M_tree.shrink_to_fit();\n  }\n  size_type size() const { \n    return M_tree.size()\
    \ >> 1;\n  }\n};\n\n/**\n * @title Segment Tree\n */\n#line 2 \"algebraic/modular.cpp\"\
    \n\n#line 2 \"algebraic/mod_inv.cpp\"\n\n#line 5 \"algebraic/mod_inv.cpp\"\n\n\
    constexpr std::pair<int64_t, int64_t> mod_inv(int64_t a, int64_t b) {\n  if ((a\
    \ %= b) == 0) return { b, 0 };\n  int64_t s = b, t = (a < 0 ? a + b : a);\n  int64_t\
    \ m0 = 0, m1 = 1, tmp = 0;\n  while (t > 0) {\n    const auto u = s / t;\n   \
    \ s -= t * u; m0 -= m1 * u;\n    tmp = s; s = t; t = tmp; tmp = m0; m0 = m1; m1\
    \ = tmp;\n  }\n  return { s, (m0 < 0 ? m0 + b / s : m0) };\n}\n\n/**\n * @title\
    \ Extended GCD\n */\n#line 4 \"algebraic/modular.cpp\"\n\n#line 6 \"algebraic/modular.cpp\"\
    \n#include <iostream>\n#line 9 \"algebraic/modular.cpp\"\n\ntemplate <class Modulus>\n\
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
    \ = modular<dynamic_modulus<>>;\n\n/*\n * @title Modint\n */\n#line 6 \"test/segment_tree.test.cpp\"\
    \n\n#line 11 \"test/segment_tree.test.cpp\"\n\nusing m32 = mint32_t<998244353>;\n\
    \nstruct st_monoid {\n  struct value_structure {\n    using type = std::pair<m32,\
    \ m32>;\n    static type identity() { return { m32(1), m32(0) }; }\n    static\
    \ type operation(const type& v1, const type& v2) { \n      return { v2.first *\
    \ v1.first, v2.first * v1.second + v2.second };\n    }\n  };\n};\n\nint main()\
    \ {\n  size_t N, Q;\n  std::cin >> N >> Q;\n  std::vector<std::pair<m32, m32>>\
    \ F(N);\n  for (auto &[p, q]: F) {\n    std::cin >> p.extract() >> q.extract();\n\
    \  }\n  segment_tree<st_monoid> seg(F.begin(), F.end());\n  while (Q--) {\n  \
    \  size_t t;\n    std::cin >> t;\n    if (t == 0) {\n      size_t i;\n      m32\
    \ a, b;\n      std::cin >> i >> a.extract() >> b.extract();\n      seg.assign(i,\
    \ { a, b });\n    }\n    else {\n      size_t l, r;\n      m32 x;\n      std::cin\
    \ >> l >> r >> x.extract();\n      auto p = seg.fold(l, r);\n      std::cout <<\
    \ p.first * x + p.second << '\\n';\n    }\n  }\n  return 0;\n}\n"
  code: "\n#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\
    \n\n#include \"../container/segment_tree.cpp\"\n#include \"../algebraic/modular.cpp\"\
    \n\n#include <utility>\n#include <iostream>\n#include <cstddef>\n#include <vector>\n\
    \nusing m32 = mint32_t<998244353>;\n\nstruct st_monoid {\n  struct value_structure\
    \ {\n    using type = std::pair<m32, m32>;\n    static type identity() { return\
    \ { m32(1), m32(0) }; }\n    static type operation(const type& v1, const type&\
    \ v2) { \n      return { v2.first * v1.first, v2.first * v1.second + v2.second\
    \ };\n    }\n  };\n};\n\nint main() {\n  size_t N, Q;\n  std::cin >> N >> Q;\n\
    \  std::vector<std::pair<m32, m32>> F(N);\n  for (auto &[p, q]: F) {\n    std::cin\
    \ >> p.extract() >> q.extract();\n  }\n  segment_tree<st_monoid> seg(F.begin(),\
    \ F.end());\n  while (Q--) {\n    size_t t;\n    std::cin >> t;\n    if (t ==\
    \ 0) {\n      size_t i;\n      m32 a, b;\n      std::cin >> i >> a.extract() >>\
    \ b.extract();\n      seg.assign(i, { a, b });\n    }\n    else {\n      size_t\
    \ l, r;\n      m32 x;\n      std::cin >> l >> r >> x.extract();\n      auto p\
    \ = seg.fold(l, r);\n      std::cout << p.first * x + p.second << '\\n';\n   \
    \ }\n  }\n  return 0;\n}\n"
  dependsOn:
  - container/segment_tree.cpp
  - other/monoid.cpp
  - other/bit_operation.cpp
  - algebraic/modular.cpp
  - algebraic/mod_inv.cpp
  isVerificationFile: true
  path: test/segment_tree.test.cpp
  requiredBy: []
  timestamp: '2020-09-27 11:10:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/segment_tree.test.cpp
layout: document
redirect_from:
- /verify/test/segment_tree.test.cpp
- /verify/test/segment_tree.test.cpp.html
title: test/segment_tree.test.cpp
---
