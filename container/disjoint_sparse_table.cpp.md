---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/bit_operation.cpp
    title: Bit Operations
  - icon: ':heavy_check_mark:'
    path: other/monoid.cpp
    title: Monoid Utility
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: container/dst_tree.cpp
    title: DST Tree
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/dst_tree.test.cpp
    title: test/dst_tree.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    document_title: Disjoint Sparse Table
    links: []
  bundledCode: "#line 2 \"container/disjoint_sparse_table.cpp\"\n\n#line 2 \"other/bit_operation.cpp\"\
    \n\n#include <cstddef>\n#include <cstdint>\n\nconstexpr size_t bit_ppc(const uint64_t\
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
    \ */\n#line 2 \"other/monoid.cpp\"\n\n#include <type_traits>\n#include <utility>\n\
    #include <stdexcept>\n\ntemplate <class T, class = void>\nclass has_identity:\
    \ public std::false_type { };\n\ntemplate <class T>\nclass has_identity<T, typename\
    \ std::conditional<false, decltype(T::identity()), void>::type>: public std::true_type\
    \ { };\n\ntemplate <class T>\nconstexpr typename std::enable_if<has_identity<T>::value,\
    \ typename T::type>::type empty_exception() {\n  return T::identity();\n}\ntemplate\
    \ <class T>\n[[noreturn]] typename std::enable_if<!has_identity<T>::value, typename\
    \ T::type>::type empty_exception() {\n  throw std::runtime_error(\"type T has\
    \ no identity\");\n}\n\ntemplate <class T, bool HasIdentity>\nclass fixed_monoid_impl:\
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
    \n/**\n * @title Monoid Utility\n */\n#line 5 \"container/disjoint_sparse_table.cpp\"\
    \n\n#line 7 \"container/disjoint_sparse_table.cpp\"\n#include <vector>\n#include\
    \ <cassert>\n\ntemplate <class SemiGroup>\nclass disjoint_sparse_table {\npublic:\n\
    \  using structure       = SemiGroup;\n  using value_semigroup = typename SemiGroup::value_structure;\n\
    \  using value_type      = typename SemiGroup::value_structure::type;\n  using\
    \ size_type       = size_t;\n\nprivate:\n  std::vector<std::vector<value_type>>\
    \ M_table;\n\npublic:\n  disjoint_sparse_table() = default;\n  template <class\
    \ InputIterator>\n  explicit disjoint_sparse_table(InputIterator first, InputIterator\
    \ last) { construct(first, last); }\n\n  template <class InputIterator>\n  void\
    \ construct(InputIterator first, InputIterator last) {\n    clear();\n    const\
    \ size_type size = std::distance(first, last);\n    const size_type height = bit_width(size);\n\
    \    M_table.resize(height, std::vector<value_type>(size));\n    M_table.front()\
    \ = std::vector<value_type>(first, last);\n    for (size_type story = 1; story\
    \ < height; ++story) {\n      const size_type bit = (1 << story);\n      for (size_type\
    \ left = 0; left < size; left += (bit << 1)) {\n        const size_type mid =\
    \ (left + bit < size ? left + bit : size);\n        M_table[story][mid - 1] =\
    \ M_table[0][mid - 1];\n        for (size_type i = mid - 1; i-- != left;) {\n\
    \          M_table[story][i] = value_semigroup::operation(M_table[0][i], M_table[story][i\
    \ + 1]);\n        }\n        if (mid >= size) continue;\n        const size_type\
    \ right = (mid + bit < size ? mid + bit : size);\n        M_table[story][mid]\
    \ = M_table[0][mid];\n        for (size_type i = mid + 1; i != right; ++i) {\n\
    \          M_table[story][i] = value_semigroup::operation(M_table[story][i - 1],\
    \ M_table[0][i]);\n        }\n      }\n    }\n  }\n\n  value_type fold(const size_type\
    \ first, size_type last) const {\n    assert(first <= last);\n    assert(last\
    \ <= size());\n    if (first == last) return empty_exception<value_semigroup>();\n\
    \    if (first == --last) return M_table[0][first];\n    const size_type height\
    \ = bit_width(first ^ last) - 1;\n    return value_semigroup::operation(M_table[height][first],\
    \ M_table[height][last]);\n  }\n\n  void clear() {\n    M_table.clear();\n   \
    \ M_table.shrink_to_fit();\n  }\n  size_type size() const {\n    if (M_table.empty())\
    \ return 0;\n    return M_table.front().size();\n  }\n};\n\n/**\n * @title Disjoint\
    \ Sparse Table\n */\n"
  code: "#pragma once\n\n#include \"../other/bit_operation.cpp\"\n#include \"../other/monoid.cpp\"\
    \n\n#include <cstddef>\n#include <vector>\n#include <cassert>\n\ntemplate <class\
    \ SemiGroup>\nclass disjoint_sparse_table {\npublic:\n  using structure      \
    \ = SemiGroup;\n  using value_semigroup = typename SemiGroup::value_structure;\n\
    \  using value_type      = typename SemiGroup::value_structure::type;\n  using\
    \ size_type       = size_t;\n\nprivate:\n  std::vector<std::vector<value_type>>\
    \ M_table;\n\npublic:\n  disjoint_sparse_table() = default;\n  template <class\
    \ InputIterator>\n  explicit disjoint_sparse_table(InputIterator first, InputIterator\
    \ last) { construct(first, last); }\n\n  template <class InputIterator>\n  void\
    \ construct(InputIterator first, InputIterator last) {\n    clear();\n    const\
    \ size_type size = std::distance(first, last);\n    const size_type height = bit_width(size);\n\
    \    M_table.resize(height, std::vector<value_type>(size));\n    M_table.front()\
    \ = std::vector<value_type>(first, last);\n    for (size_type story = 1; story\
    \ < height; ++story) {\n      const size_type bit = (1 << story);\n      for (size_type\
    \ left = 0; left < size; left += (bit << 1)) {\n        const size_type mid =\
    \ (left + bit < size ? left + bit : size);\n        M_table[story][mid - 1] =\
    \ M_table[0][mid - 1];\n        for (size_type i = mid - 1; i-- != left;) {\n\
    \          M_table[story][i] = value_semigroup::operation(M_table[0][i], M_table[story][i\
    \ + 1]);\n        }\n        if (mid >= size) continue;\n        const size_type\
    \ right = (mid + bit < size ? mid + bit : size);\n        M_table[story][mid]\
    \ = M_table[0][mid];\n        for (size_type i = mid + 1; i != right; ++i) {\n\
    \          M_table[story][i] = value_semigroup::operation(M_table[story][i - 1],\
    \ M_table[0][i]);\n        }\n      }\n    }\n  }\n\n  value_type fold(const size_type\
    \ first, size_type last) const {\n    assert(first <= last);\n    assert(last\
    \ <= size());\n    if (first == last) return empty_exception<value_semigroup>();\n\
    \    if (first == --last) return M_table[0][first];\n    const size_type height\
    \ = bit_width(first ^ last) - 1;\n    return value_semigroup::operation(M_table[height][first],\
    \ M_table[height][last]);\n  }\n\n  void clear() {\n    M_table.clear();\n   \
    \ M_table.shrink_to_fit();\n  }\n  size_type size() const {\n    if (M_table.empty())\
    \ return 0;\n    return M_table.front().size();\n  }\n};\n\n/**\n * @title Disjoint\
    \ Sparse Table\n */"
  dependsOn:
  - other/bit_operation.cpp
  - other/monoid.cpp
  isVerificationFile: false
  path: container/disjoint_sparse_table.cpp
  requiredBy:
  - container/dst_tree.cpp
  timestamp: '2020-09-13 16:51:07+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/dst_tree.test.cpp
documentation_of: container/disjoint_sparse_table.cpp
layout: document
redirect_from:
- /library/container/disjoint_sparse_table.cpp
- /library/container/disjoint_sparse_table.cpp.html
title: Disjoint Sparse Table
---
