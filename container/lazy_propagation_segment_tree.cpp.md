---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/bit_operation.cpp
    title: Bit Operations
  - icon: ':heavy_check_mark:'
    path: other/monoid.cpp
    title: Monoid Utility
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/lazy_propagation_segment_tree.test.cpp
    title: test/lazy_propagation_segment_tree.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Lazy Propagation Segment Tree
    links: []
  bundledCode: "#line 2 \"container/lazy_propagation_segment_tree.cpp\"\n\n#line 2\
    \ \"other/bit_operation.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\nconstexpr\
    \ size_t bit_ppc(const uint64_t x) { return __builtin_popcountll(x); }\nconstexpr\
    \ size_t bit_ctzr(const uint64_t x) { return x == 0 ? 64 : __builtin_ctzll(x);\
    \ }\nconstexpr size_t bit_ctzl(const uint64_t x) { return x == 0 ? 64 : __builtin_clzll(x);\
    \ }\nconstexpr size_t bit_width(const uint64_t x) { return 64 - bit_ctzl(x); }\n\
    constexpr uint64_t bit_msb(const uint64_t x) { return x == 0 ? 0 : uint64_t(1)\
    \ << (bit_width(x) - 1); }\nconstexpr uint64_t bit_lsb(const uint64_t x) { return\
    \ x & (-x); }\nconstexpr uint64_t bit_cover(const uint64_t x) { return x == 0\
    \ ? 0 : bit_msb(2 * x - 1); }\n\nconstexpr uint64_t bit_rev(uint64_t x) {\n  x\
    \ = ((x >> 1) & 0x5555555555555555) | ((x & 0x5555555555555555) << 1);\n  x =\
    \ ((x >> 2) & 0x3333333333333333) | ((x & 0x3333333333333333) << 2);\n  x = ((x\
    \ >> 4) & 0x0F0F0F0F0F0F0F0F) | ((x & 0x0F0F0F0F0F0F0F0F) << 4);\n  x = ((x >>\
    \ 8) & 0x00FF00FF00FF00FF) | ((x & 0x00FF00FF00FF00FF) << 8);\n  x = ((x >> 16)\
    \ & 0x0000FFFF0000FFFF) | ((x & 0x0000FFFF0000FFFF) << 16);\n  x = (x >> 32) |\
    \ (x << 32);\n  return x;\n}\n\n/**\n * @title Bit Operations\n */\n#line 2 \"\
    other/monoid.cpp\"\n\n#include <type_traits>\n#include <utility>\n#include <stdexcept>\n\
    \ntemplate <class T, class = void>\nclass has_identity: public std::false_type\
    \ { };\n\ntemplate <class T>\nclass has_identity<T, typename std::conditional<false,\
    \ decltype(T::identity()), void>::type>: public std::true_type { };\n\ntemplate\
    \ <class T>\nconstexpr typename std::enable_if<has_identity<T>::value, typename\
    \ T::type>::type empty_exception() {\n  return T::identity();\n}\ntemplate <class\
    \ T>\n[[noreturn]] typename std::enable_if<!has_identity<T>::value, typename T::type>::type\
    \ empty_exception() {\n  throw std::runtime_error(\"type T has no identity\");\n\
    }\n\ntemplate <class T, bool HasIdentity>\nclass fixed_monoid_impl: public T {\n\
    public:\n  using type = typename T::type;\n\n  static constexpr type convert(const\
    \ type &value) { return value; }\n  static constexpr type revert(const type &value)\
    \ { return value; }\n\n  template <class Mapping, class Value, class... Args>\n\
    \  static constexpr void operate(Mapping &&func, Value &value, const type &op,\
    \ Args&&... args) {\n    value = func(value, op, std::forward<Args>(args)...);\n\
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
    \n/**\n * @title Monoid Utility\n */\n#line 5 \"container/lazy_propagation_segment_tree.cpp\"\
    \n\n#line 7 \"container/lazy_propagation_segment_tree.cpp\"\n#include <vector>\n\
    #include <iterator>\n#include <algorithm>\n#include <cassert>\n\ntemplate <class\
    \ CombinedMonoid>\nclass lazy_propagation_segment_tree {\npublic:\n  using structure\
    \       = CombinedMonoid;\n  using value_monoid    = typename CombinedMonoid::value_structure;\n\
    \  using operator_monoid = typename CombinedMonoid::operator_structure;\n  using\
    \ value_type      = typename CombinedMonoid::value_structure::type;\n  using operator_type\
    \   = typename CombinedMonoid::operator_structure::type;\n  using size_type  \
    \     = size_t;\n\nprivate:\n  using fixed_operator_monoid = fixed_monoid<operator_monoid>;\n\
    \  using fixed_operator_type   = typename fixed_operator_monoid::type;\n\n  class\
    \ node_type {\n  public:\n    value_type    value;\n    fixed_operator_type lazy;\n\
    \    node_type(\n      const value_type    &value = value_monoid::identity(),\n\
    \      const fixed_operator_type &lazy = fixed_operator_monoid::identity()\n \
    \   ): value(value), lazy(lazy) { }\n  };\n\n  static void S_apply(node_type &node,\
    \ const fixed_operator_type &op, const size_type length) {\n    fixed_operator_monoid::operate(structure::operation,\
    \ node.value, op, length);\n    node.lazy = fixed_operator_monoid::operation(node.lazy,\
    \ op);\n  }\n\n  void M_propagate(const size_type index, const size_type length)\
    \ {\n    S_apply(M_tree[index << 1 | 0], M_tree[index].lazy, length);\n    S_apply(M_tree[index\
    \ << 1 | 1], M_tree[index].lazy, length);\n    M_tree[index].lazy = fixed_operator_monoid::identity();\n\
    \  }\n  void M_fix_change(const size_type index) {\n    M_tree[index].value =\
    \ \n      value_monoid::operation(M_tree[index << 1 | 0].value, M_tree[index <<\
    \ 1 | 1].value);\n  }\n\n  void M_pushdown(const size_type index) {\n    const\
    \ size_type lsb = bit_ctzr(index);\n    for (size_type story = bit_width(index);\
    \ story != lsb; --story) {\n      M_propagate(index >> story, 1 << (story - 1));\n\
    \    }\n  }\n  void M_pullup(size_type index) {\n    index >>= bit_ctzr(index);\n\
    \    while (index != 1) {\n      index >>= 1;\n      M_fix_change(index);\n  \
    \  }\n  }\n\n  std::vector<node_type> M_tree;\n\npublic:\n  lazy_propagation_segment_tree()\
    \ = default;\n  explicit lazy_propagation_segment_tree(const size_type size) {\
    \ initialize(size); }\n  template <class InputIterator>\n  explicit lazy_propagation_segment_tree(InputIterator\
    \ first, InputIterator last) { construct(first, last); }\n\n  void initialize(const\
    \ size_type size) {\n    clear();\n    M_tree.assign(size << 1, node_type());\n\
    \  }\n\n  template <class InputIterator>\n  void construct(InputIterator first,\
    \ InputIterator last) {\n    clear();\n    const size_type size = std::distance(first,\
    \ last);\n    M_tree.reserve(size << 1);\n    M_tree.assign(size, node_type());\n\
    \    for (; first != last; ++first) {\n      M_tree.emplace_back(*first, fixed_operator_monoid::identity());\n\
    \    }\n    for (size_type index = size - 1; index != 0; --index) {\n      M_fix_change(index);\n\
    \    }\n  }\n\n  value_type fold(size_type first, size_type last) {\n    assert(first\
    \ <= last);\n    assert(last <= size());\n    first += size();\n    last  += size();\n\
    \    M_pushdown(first);\n    M_pushdown(last);\n    value_type fold_l = value_monoid::identity();\n\
    \    value_type fold_r = value_monoid::identity();\n    while (first != last)\
    \ {\n      if (first & 1) {\n        fold_l = value_monoid::operation(fold_l,\
    \ M_tree[first].value);\n        ++first;\n      }\n      if (last & 1) {\n  \
    \      --last;\n        fold_r = value_monoid::operation(M_tree[last].value, fold_r);\n\
    \      }\n      first >>= 1;\n      last  >>= 1;\n    }\n    return value_monoid::operation(fold_l,\
    \ fold_r);\n  }\n\n  void operate(size_type first, size_type last, const operator_type\
    \ &op_) {\n    assert(first <= last);\n    assert(last <= size());\n    const\
    \ auto op = fixed_operator_monoid::convert(op_);\n    first += size();\n    last\
    \  += size();\n    M_pushdown(first);\n    M_pushdown(last);\n    const size_type\
    \ first_c = first;\n    const size_type last_c  = last;\n    for (size_type story\
    \ = 0; first != last; ++story) {\n      if (first & 1) {\n        S_apply(M_tree[first],\
    \ op, 1 << story);\n        ++first;\n      }\n      if (last & 1) {\n       \
    \ --last;\n        S_apply(M_tree[last], op, 1 << story);\n      }\n      first\
    \ >>= 1;\n      last  >>= 1;\n    }\n    M_pullup(first_c);\n    M_pullup(last_c);\n\
    \  }\n\n  void assign(size_type index, const value_type &val) {\n    assert(index\
    \ < size());\n    index += size();\n    for (size_type story = bit_width(index);\
    \ story != 0; --story) {\n      M_propagate(index >> story, 1 << (story - 1));\n\
    \    }\n    M_tree[index].value = val;\n    M_tree[index].lazy  = fixed_operator_monoid::identity();\n\
    \    while (index != 1) {\n      index >>= 1;\n      M_fix_change(index);\n  \
    \  }\n  }\n\n  template <bool ToRight = true, class Constraint, std::enable_if_t<ToRight>*\
    \ = nullptr> \n  size_type satisfies(const size_type left, Constraint &&func)\
    \ {\n    assert(left <= size());\n    if (func(value_monoid::identity())) return\
    \ left;\n    size_type first = left + size();\n    size_type last = 2 * size();\n\
    \    M_pushdown(first);\n    M_pushdown(last);\n    const size_type last_c = last;\n\
    \    value_type fold = value_monoid::identity();\n    const auto try_merge = [&](const\
    \ size_type index) {\n      value_type tmp = value_monoid::operation(fold, M_tree[index].value);\n\
    \      if (func(tmp)) return true;\n      fold = std::move(tmp);\n      return\
    \ false;\n    };\n    const auto subtree = [&](size_type index, size_type story)\
    \ {\n      while (index < size()) {\n        M_propagate(index, 1 << (story -\
    \ 1));\n        index <<= 1;\n        if (!try_merge(index)) ++index;\n      \
    \  --story;\n      }\n      return index - size() + 1;\n    };\n    size_type\
    \ story = 0;\n    while (first < last) {\n      if (first & 1) {\n        if (try_merge(first))\
    \ return subtree(first, story);\n        ++first;\n      }\n      first >>= 1;\n\
    \      last >>= 1;\n      ++story;\n    }\n    while (story--) {\n      last =\
    \ last_c >> story;\n      if (last & 1) {\n        --last;\n        if (try_merge(last))\
    \ return subtree(last, story);\n      }\n    }\n    return size() + 1;\n  }\n\n\
    \  template <bool ToRight = true, class Constraint, std::enable_if_t<!ToRight>*\
    \ = nullptr> \n  size_type satisfies(const size_type right, Constraint &&func)\
    \ {\n    assert(right <= size());\n    if (func(value_monoid::identity())) return\
    \ right;\n    size_type first = size();\n    size_type last = right + size();\n\
    \    M_pushdown(first);\n    M_pushdown(last);\n    const size_type first_c =\
    \ first;\n    value_type fold = value_monoid::identity();\n    const auto try_merge\
    \ = [&](const size_type index) {\n      value_type tmp = value_monoid::operation(M_tree[index].value,\
    \ fold);\n      if (func(tmp)) return true;\n      fold = std::move(tmp);\n  \
    \    return false;\n    };\n    const auto subtree = [&](size_type index, size_type\
    \ story) {\n      while (index < size()) {\n        M_propagate(index, 1 << (story\
    \ - 1));\n        index <<= 1;\n        if (try_merge(index + 1)) ++index;\n \
    \       --story;\n      }\n      return index - size();\n    };\n    size_type\
    \ story = 0;\n    while (first < last) {\n      if (first & 1) ++first;\n    \
    \  if (last & 1) {\n        --last;\n        if (try_merge(last)) return subtree(last,\
    \ story);\n      }\n      first >>= 1;\n      last >>= 1;\n      ++story;\n  \
    \  }\n    const size_type cover = bit_cover(first_c);\n    while (story--) {\n\
    \      first = (cover >> story) - ((cover - first_c) >> story);\n      if (first\
    \ & 1) {\n        if (try_merge(first)) return subtree(first, story);\n      }\n\
    \    }\n    return size_type(-1);\n  }\n\n  void clear() {\n    M_tree.clear();\n\
    \    M_tree.shrink_to_fit();\n  }\n  size_type size() const { \n    return M_tree.size()\
    \ >> 1;\n  }\n};\n\n/**\n * @title Lazy Propagation Segment Tree\n */\n"
  code: "#pragma once\n\n#include \"../other/bit_operation.cpp\"\n#include \"../other/monoid.cpp\"\
    \n\n#include <cstddef>\n#include <vector>\n#include <iterator>\n#include <algorithm>\n\
    #include <cassert>\n\ntemplate <class CombinedMonoid>\nclass lazy_propagation_segment_tree\
    \ {\npublic:\n  using structure       = CombinedMonoid;\n  using value_monoid\
    \    = typename CombinedMonoid::value_structure;\n  using operator_monoid = typename\
    \ CombinedMonoid::operator_structure;\n  using value_type      = typename CombinedMonoid::value_structure::type;\n\
    \  using operator_type   = typename CombinedMonoid::operator_structure::type;\n\
    \  using size_type       = size_t;\n\nprivate:\n  using fixed_operator_monoid\
    \ = fixed_monoid<operator_monoid>;\n  using fixed_operator_type   = typename fixed_operator_monoid::type;\n\
    \n  class node_type {\n  public:\n    value_type    value;\n    fixed_operator_type\
    \ lazy;\n    node_type(\n      const value_type    &value = value_monoid::identity(),\n\
    \      const fixed_operator_type &lazy = fixed_operator_monoid::identity()\n \
    \   ): value(value), lazy(lazy) { }\n  };\n\n  static void S_apply(node_type &node,\
    \ const fixed_operator_type &op, const size_type length) {\n    fixed_operator_monoid::operate(structure::operation,\
    \ node.value, op, length);\n    node.lazy = fixed_operator_monoid::operation(node.lazy,\
    \ op);\n  }\n\n  void M_propagate(const size_type index, const size_type length)\
    \ {\n    S_apply(M_tree[index << 1 | 0], M_tree[index].lazy, length);\n    S_apply(M_tree[index\
    \ << 1 | 1], M_tree[index].lazy, length);\n    M_tree[index].lazy = fixed_operator_monoid::identity();\n\
    \  }\n  void M_fix_change(const size_type index) {\n    M_tree[index].value =\
    \ \n      value_monoid::operation(M_tree[index << 1 | 0].value, M_tree[index <<\
    \ 1 | 1].value);\n  }\n\n  void M_pushdown(const size_type index) {\n    const\
    \ size_type lsb = bit_ctzr(index);\n    for (size_type story = bit_width(index);\
    \ story != lsb; --story) {\n      M_propagate(index >> story, 1 << (story - 1));\n\
    \    }\n  }\n  void M_pullup(size_type index) {\n    index >>= bit_ctzr(index);\n\
    \    while (index != 1) {\n      index >>= 1;\n      M_fix_change(index);\n  \
    \  }\n  }\n\n  std::vector<node_type> M_tree;\n\npublic:\n  lazy_propagation_segment_tree()\
    \ = default;\n  explicit lazy_propagation_segment_tree(const size_type size) {\
    \ initialize(size); }\n  template <class InputIterator>\n  explicit lazy_propagation_segment_tree(InputIterator\
    \ first, InputIterator last) { construct(first, last); }\n\n  void initialize(const\
    \ size_type size) {\n    clear();\n    M_tree.assign(size << 1, node_type());\n\
    \  }\n\n  template <class InputIterator>\n  void construct(InputIterator first,\
    \ InputIterator last) {\n    clear();\n    const size_type size = std::distance(first,\
    \ last);\n    M_tree.reserve(size << 1);\n    M_tree.assign(size, node_type());\n\
    \    for (; first != last; ++first) {\n      M_tree.emplace_back(*first, fixed_operator_monoid::identity());\n\
    \    }\n    for (size_type index = size - 1; index != 0; --index) {\n      M_fix_change(index);\n\
    \    }\n  }\n\n  value_type fold(size_type first, size_type last) {\n    assert(first\
    \ <= last);\n    assert(last <= size());\n    first += size();\n    last  += size();\n\
    \    M_pushdown(first);\n    M_pushdown(last);\n    value_type fold_l = value_monoid::identity();\n\
    \    value_type fold_r = value_monoid::identity();\n    while (first != last)\
    \ {\n      if (first & 1) {\n        fold_l = value_monoid::operation(fold_l,\
    \ M_tree[first].value);\n        ++first;\n      }\n      if (last & 1) {\n  \
    \      --last;\n        fold_r = value_monoid::operation(M_tree[last].value, fold_r);\n\
    \      }\n      first >>= 1;\n      last  >>= 1;\n    }\n    return value_monoid::operation(fold_l,\
    \ fold_r);\n  }\n\n  void operate(size_type first, size_type last, const operator_type\
    \ &op_) {\n    assert(first <= last);\n    assert(last <= size());\n    const\
    \ auto op = fixed_operator_monoid::convert(op_);\n    first += size();\n    last\
    \  += size();\n    M_pushdown(first);\n    M_pushdown(last);\n    const size_type\
    \ first_c = first;\n    const size_type last_c  = last;\n    for (size_type story\
    \ = 0; first != last; ++story) {\n      if (first & 1) {\n        S_apply(M_tree[first],\
    \ op, 1 << story);\n        ++first;\n      }\n      if (last & 1) {\n       \
    \ --last;\n        S_apply(M_tree[last], op, 1 << story);\n      }\n      first\
    \ >>= 1;\n      last  >>= 1;\n    }\n    M_pullup(first_c);\n    M_pullup(last_c);\n\
    \  }\n\n  void assign(size_type index, const value_type &val) {\n    assert(index\
    \ < size());\n    index += size();\n    for (size_type story = bit_width(index);\
    \ story != 0; --story) {\n      M_propagate(index >> story, 1 << (story - 1));\n\
    \    }\n    M_tree[index].value = val;\n    M_tree[index].lazy  = fixed_operator_monoid::identity();\n\
    \    while (index != 1) {\n      index >>= 1;\n      M_fix_change(index);\n  \
    \  }\n  }\n\n  template <bool ToRight = true, class Constraint, std::enable_if_t<ToRight>*\
    \ = nullptr> \n  size_type satisfies(const size_type left, Constraint &&func)\
    \ {\n    assert(left <= size());\n    if (func(value_monoid::identity())) return\
    \ left;\n    size_type first = left + size();\n    size_type last = 2 * size();\n\
    \    M_pushdown(first);\n    M_pushdown(last);\n    const size_type last_c = last;\n\
    \    value_type fold = value_monoid::identity();\n    const auto try_merge = [&](const\
    \ size_type index) {\n      value_type tmp = value_monoid::operation(fold, M_tree[index].value);\n\
    \      if (func(tmp)) return true;\n      fold = std::move(tmp);\n      return\
    \ false;\n    };\n    const auto subtree = [&](size_type index, size_type story)\
    \ {\n      while (index < size()) {\n        M_propagate(index, 1 << (story -\
    \ 1));\n        index <<= 1;\n        if (!try_merge(index)) ++index;\n      \
    \  --story;\n      }\n      return index - size() + 1;\n    };\n    size_type\
    \ story = 0;\n    while (first < last) {\n      if (first & 1) {\n        if (try_merge(first))\
    \ return subtree(first, story);\n        ++first;\n      }\n      first >>= 1;\n\
    \      last >>= 1;\n      ++story;\n    }\n    while (story--) {\n      last =\
    \ last_c >> story;\n      if (last & 1) {\n        --last;\n        if (try_merge(last))\
    \ return subtree(last, story);\n      }\n    }\n    return size() + 1;\n  }\n\n\
    \  template <bool ToRight = true, class Constraint, std::enable_if_t<!ToRight>*\
    \ = nullptr> \n  size_type satisfies(const size_type right, Constraint &&func)\
    \ {\n    assert(right <= size());\n    if (func(value_monoid::identity())) return\
    \ right;\n    size_type first = size();\n    size_type last = right + size();\n\
    \    M_pushdown(first);\n    M_pushdown(last);\n    const size_type first_c =\
    \ first;\n    value_type fold = value_monoid::identity();\n    const auto try_merge\
    \ = [&](const size_type index) {\n      value_type tmp = value_monoid::operation(M_tree[index].value,\
    \ fold);\n      if (func(tmp)) return true;\n      fold = std::move(tmp);\n  \
    \    return false;\n    };\n    const auto subtree = [&](size_type index, size_type\
    \ story) {\n      while (index < size()) {\n        M_propagate(index, 1 << (story\
    \ - 1));\n        index <<= 1;\n        if (try_merge(index + 1)) ++index;\n \
    \       --story;\n      }\n      return index - size();\n    };\n    size_type\
    \ story = 0;\n    while (first < last) {\n      if (first & 1) ++first;\n    \
    \  if (last & 1) {\n        --last;\n        if (try_merge(last)) return subtree(last,\
    \ story);\n      }\n      first >>= 1;\n      last >>= 1;\n      ++story;\n  \
    \  }\n    const size_type cover = bit_cover(first_c);\n    while (story--) {\n\
    \      first = (cover >> story) - ((cover - first_c) >> story);\n      if (first\
    \ & 1) {\n        if (try_merge(first)) return subtree(first, story);\n      }\n\
    \    }\n    return size_type(-1);\n  }\n\n  void clear() {\n    M_tree.clear();\n\
    \    M_tree.shrink_to_fit();\n  }\n  size_type size() const { \n    return M_tree.size()\
    \ >> 1;\n  }\n};\n\n/**\n * @title Lazy Propagation Segment Tree\n */"
  dependsOn:
  - other/bit_operation.cpp
  - other/monoid.cpp
  isVerificationFile: false
  path: container/lazy_propagation_segment_tree.cpp
  requiredBy: []
  timestamp: '2020-09-13 16:51:07+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/lazy_propagation_segment_tree.test.cpp
documentation_of: container/lazy_propagation_segment_tree.cpp
layout: document
redirect_from:
- /library/container/lazy_propagation_segment_tree.cpp
- /library/container/lazy_propagation_segment_tree.cpp.html
title: Lazy Propagation Segment Tree
---
