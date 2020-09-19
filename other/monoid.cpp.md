---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: container/dual_segment_tree.cpp
    title: Dual Segment Tree
  - icon: ':x:'
    path: container/sliding_window_aggregation.cpp
    title: Sliding Window Aggregation
  - icon: ':heavy_check_mark:'
    path: container/disjoint_sparse_table.cpp
    title: Disjoint Sparse Table
  - icon: ':heavy_check_mark:'
    path: container/dst_tree.cpp
    title: DST Tree
  - icon: ':x:'
    path: container/lazy_propagation_segment_tree.cpp
    title: Lazy Propagation Segment Tree
  - icon: ':x:'
    path: container/segment_tree.cpp
    title: Segment Tree
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/dst_tree.test.cpp
    title: test/dst_tree.test.cpp
  - icon: ':x:'
    path: test/lazy_propagation_segment_tree.test.cpp
    title: test/lazy_propagation_segment_tree.test.cpp
  - icon: ':x:'
    path: test/sliding_window_aggregation.test.cpp
    title: test/sliding_window_aggregation.test.cpp
  - icon: ':x:'
    path: test/segment_tree.test.cpp
    title: test/segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/dual_segment_tree.test.cpp
    title: test/dual_segment_tree.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':question:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    document_title: Monoid Utility
    links: []
  bundledCode: "#line 2 \"other/monoid.cpp\"\n\n#include <type_traits>\n#include <utility>\n\
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
    \n/**\n * @title Monoid Utility\n */\n"
  code: "#pragma once\n\n#include <type_traits>\n#include <utility>\n#include <stdexcept>\n\
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
    \n/**\n * @title Monoid Utility\n */"
  dependsOn: []
  isVerificationFile: false
  path: other/monoid.cpp
  requiredBy:
  - container/dual_segment_tree.cpp
  - container/sliding_window_aggregation.cpp
  - container/disjoint_sparse_table.cpp
  - container/dst_tree.cpp
  - container/lazy_propagation_segment_tree.cpp
  - container/segment_tree.cpp
  timestamp: '2020-09-13 16:51:07+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/dst_tree.test.cpp
  - test/lazy_propagation_segment_tree.test.cpp
  - test/sliding_window_aggregation.test.cpp
  - test/segment_tree.test.cpp
  - test/dual_segment_tree.test.cpp
documentation_of: other/monoid.cpp
layout: document
redirect_from:
- /library/other/monoid.cpp
- /library/other/monoid.cpp.html
title: Monoid Utility
---
