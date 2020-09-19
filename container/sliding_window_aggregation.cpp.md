---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/monoid.cpp
    title: Monoid Utility
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/sliding_window_aggregation.test.cpp
    title: test/sliding_window_aggregation.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    document_title: Sliding Window Aggregation
    links: []
  bundledCode: "#line 2 \"container/sliding_window_aggregation.cpp\"\n\n#line 2 \"\
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
    \ M_back.empty();\n  }\n};\n\n/**\n * @title Sliding Window Aggregation\n */\n"
  code: "#pragma once\n\n#include \"../other/monoid.cpp\"\n\n#include <cstddef>\n\
    #include <stack>\n#include <cassert>\n\ntemplate <class SemiGroup>\nclass sliding_window_aggregation\
    \ {\npublic:\n  using structure       = SemiGroup;\n  using value_semigroup =\
    \ typename SemiGroup::value_structure;\n  using value_type      = typename SemiGroup::value_structure::type;\n\
    \  using size_type       = size_t;\n\nprivate:\n  class node_type {\n  public:\n\
    \    value_type value, sum;\n    node_type(const value_type &value, const value_type\
    \ &sum): value(value), sum(sum) { }\n  };\n\n  std::stack<node_type> M_front,\
    \ M_back;\n\npublic:\n  sliding_window_aggregation(): M_front(), M_back() { }\n\
    \n  value_type fold() const {\n    if (empty()) return empty_exception<value_semigroup>();\n\
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
    \ M_back.empty();\n  }\n};\n\n/**\n * @title Sliding Window Aggregation\n */"
  dependsOn:
  - other/monoid.cpp
  isVerificationFile: false
  path: container/sliding_window_aggregation.cpp
  requiredBy: []
  timestamp: '2020-09-13 16:51:07+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/sliding_window_aggregation.test.cpp
documentation_of: container/sliding_window_aggregation.cpp
layout: document
redirect_from:
- /library/container/sliding_window_aggregation.cpp
- /library/container/sliding_window_aggregation.cpp.html
title: Sliding Window Aggregation
---
