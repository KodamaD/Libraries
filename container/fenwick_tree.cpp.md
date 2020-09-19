---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: other/bit_operation.cpp
    title: Bit Operations
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/fenwick_tree.test.cpp
    title: test/fenwick_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/vertex_set_path_sum.test.cpp
    title: test/vertex_set_path_sum.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    document_title: Fenwick Tree
    links: []
  bundledCode: "#line 2 \"container/fenwick_tree.cpp\"\n\n#line 2 \"other/bit_operation.cpp\"\
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
    \ */\n#line 4 \"container/fenwick_tree.cpp\"\n\n#line 6 \"container/fenwick_tree.cpp\"\
    \n#include <vector>\n#include <cassert>\n#include <type_traits>\n\ntemplate <class\
    \ T>\nclass fenwick_tree {\npublic:\n  using value_type = T;\n  using size_type\
    \ = size_t;\n\nprivate:\n  std::vector<value_type> M_tree;\n\npublic:\n  fenwick_tree()\
    \ = default;\n  explicit fenwick_tree(size_type size) { initialize(size); }\n\n\
    \  void initialize(size_type size) {\n    M_tree.assign(size + 1, value_type {\
    \ });\n  }\n\n  void add(size_type index, const value_type& x) {\n    assert(index\
    \ < size());\n    ++index;\n    while (index <= size()) {\n      M_tree[index]\
    \ += x;\n      index += bit_lsb(index);\n    }\n  }\n\n  template <size_type Indexed\
    \ = 1>\n  value_type get(size_type index) const {\n    assert(index < size());\n\
    \    index += Indexed;\n    value_type res{ };\n    while (index > 0) {\n    \
    \  res += M_tree[index];\n      index -= bit_lsb(index);\n    }\n    return res;\n\
    \  }\n  value_type fold(size_type first, size_type last) const {\n    assert(first\
    \ <= last);\n    assert(last <= size());\n    value_type res{};\n    while (first\
    \ < last) {\n      res += M_tree[last];\n      last -= bit_lsb(last);\n    }\n\
    \    while (last < first) {\n      res -= M_tree[first];\n      first -= bit_lsb(first);\n\
    \    }\n    return res;\n  }\n\n  template <class Func>\n  size_type satisfies(const\
    \ size_type left, Func &&func) const {\n    assert(left <= size());\n    if (func(value_type\
    \ { })) return left;\n    value_type val = -get<0>(left);\n    size_type res =\
    \ 0;\n    for (size_type cur = bit_cover(size() + 1) >> 1; cur > 0; cur >>= 1)\
    \ {\n      if ((res + cur <= left) || (res + cur <= size() && !func(val + M_tree[res\
    \ + cur]))) {\n        val += M_tree[res + cur];\n        res += cur;\n      }\n\
    \    }\n    return res + 1;\n  }\n\n  void clear() {\n    M_tree.clear();\n  \
    \  M_tree.shrink_to_fit();\n  }\n  size_type size() const {\n    return M_tree.size()\
    \ - 1;\n  }\n};\n\n/**\n * @title Fenwick Tree\n */\n"
  code: "#pragma once\n\n#include \"../other/bit_operation.cpp\"\n\n#include <cstddef>\n\
    #include <vector>\n#include <cassert>\n#include <type_traits>\n\ntemplate <class\
    \ T>\nclass fenwick_tree {\npublic:\n  using value_type = T;\n  using size_type\
    \ = size_t;\n\nprivate:\n  std::vector<value_type> M_tree;\n\npublic:\n  fenwick_tree()\
    \ = default;\n  explicit fenwick_tree(size_type size) { initialize(size); }\n\n\
    \  void initialize(size_type size) {\n    M_tree.assign(size + 1, value_type {\
    \ });\n  }\n\n  void add(size_type index, const value_type& x) {\n    assert(index\
    \ < size());\n    ++index;\n    while (index <= size()) {\n      M_tree[index]\
    \ += x;\n      index += bit_lsb(index);\n    }\n  }\n\n  template <size_type Indexed\
    \ = 1>\n  value_type get(size_type index) const {\n    assert(index < size());\n\
    \    index += Indexed;\n    value_type res{ };\n    while (index > 0) {\n    \
    \  res += M_tree[index];\n      index -= bit_lsb(index);\n    }\n    return res;\n\
    \  }\n  value_type fold(size_type first, size_type last) const {\n    assert(first\
    \ <= last);\n    assert(last <= size());\n    value_type res{};\n    while (first\
    \ < last) {\n      res += M_tree[last];\n      last -= bit_lsb(last);\n    }\n\
    \    while (last < first) {\n      res -= M_tree[first];\n      first -= bit_lsb(first);\n\
    \    }\n    return res;\n  }\n\n  template <class Func>\n  size_type satisfies(const\
    \ size_type left, Func &&func) const {\n    assert(left <= size());\n    if (func(value_type\
    \ { })) return left;\n    value_type val = -get<0>(left);\n    size_type res =\
    \ 0;\n    for (size_type cur = bit_cover(size() + 1) >> 1; cur > 0; cur >>= 1)\
    \ {\n      if ((res + cur <= left) || (res + cur <= size() && !func(val + M_tree[res\
    \ + cur]))) {\n        val += M_tree[res + cur];\n        res += cur;\n      }\n\
    \    }\n    return res + 1;\n  }\n\n  void clear() {\n    M_tree.clear();\n  \
    \  M_tree.shrink_to_fit();\n  }\n  size_type size() const {\n    return M_tree.size()\
    \ - 1;\n  }\n};\n\n/**\n * @title Fenwick Tree\n */"
  dependsOn:
  - other/bit_operation.cpp
  isVerificationFile: false
  path: container/fenwick_tree.cpp
  requiredBy: []
  timestamp: '2020-09-09 22:02:05+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/fenwick_tree.test.cpp
  - test/vertex_set_path_sum.test.cpp
documentation_of: container/fenwick_tree.cpp
layout: document
redirect_from:
- /library/container/fenwick_tree.cpp
- /library/container/fenwick_tree.cpp.html
title: Fenwick Tree
---
