---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: algebraic/ntt.cpp
    title: Number Theoretic Transform
  - icon: ':heavy_check_mark:'
    path: container/disjoint_sparse_table.cpp
    title: Disjoint Sparse Table
  - icon: ':heavy_check_mark:'
    path: container/dst_tree.cpp
    title: DST Tree
  - icon: ':heavy_check_mark:'
    path: container/dual_segment_tree.cpp
    title: Dual Segment Tree
  - icon: ':heavy_check_mark:'
    path: container/fenwick_tree.cpp
    title: Fenwick Tree
  - icon: ':heavy_check_mark:'
    path: container/lazy_propagation_segment_tree.cpp
    title: Lazy Propagation Segment Tree
  - icon: ':heavy_check_mark:'
    path: container/segment_tree.cpp
    title: Segment Tree
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/dst_tree.test.cpp
    title: test/dst_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/dual_segment_tree.test.cpp
    title: test/dual_segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/fenwick_tree.test.cpp
    title: test/fenwick_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/lazy_propagation_segment_tree.test.cpp
    title: test/lazy_propagation_segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/segment_tree.test.cpp
    title: test/segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/vertex_set_path_sum.test.cpp
    title: test/vertex_set_path_sum.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Bit Operations
    links: []
  bundledCode: "#line 2 \"other/bit_operation.cpp\"\n\n#include <cstddef>\n#include\
    \ <cstdint>\n\nconstexpr size_t bit_ppc(const uint64_t x) { return __builtin_popcountll(x);\
    \ }\nconstexpr size_t bit_ctzr(const uint64_t x) { return x == 0 ? 64 : __builtin_ctzll(x);\
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
    \ (x << 32);\n  return x;\n}\n\n/**\n * @title Bit Operations\n */\n"
  code: "#pragma once\n\n#include <cstddef>\n#include <cstdint>\n\nconstexpr size_t\
    \ bit_ppc(const uint64_t x) { return __builtin_popcountll(x); }\nconstexpr size_t\
    \ bit_ctzr(const uint64_t x) { return x == 0 ? 64 : __builtin_ctzll(x); }\nconstexpr\
    \ size_t bit_ctzl(const uint64_t x) { return x == 0 ? 64 : __builtin_clzll(x);\
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
    \ (x << 32);\n  return x;\n}\n\n/**\n * @title Bit Operations\n */"
  dependsOn: []
  isVerificationFile: false
  path: other/bit_operation.cpp
  requiredBy:
  - algebraic/ntt.cpp
  - container/dst_tree.cpp
  - container/disjoint_sparse_table.cpp
  - container/fenwick_tree.cpp
  - container/segment_tree.cpp
  - container/lazy_propagation_segment_tree.cpp
  - container/dual_segment_tree.cpp
  timestamp: '2020-09-09 18:08:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/dual_segment_tree.test.cpp
  - test/segment_tree.test.cpp
  - test/dst_tree.test.cpp
  - test/fenwick_tree.test.cpp
  - test/vertex_set_path_sum.test.cpp
  - test/lazy_propagation_segment_tree.test.cpp
documentation_of: other/bit_operation.cpp
layout: document
redirect_from:
- /library/other/bit_operation.cpp
- /library/other/bit_operation.cpp.html
title: Bit Operations
---
