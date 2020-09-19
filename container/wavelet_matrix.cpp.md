---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: container/bit_vector.cpp
    title: Succinct Bit Vector
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/wavelet_matrix_quantile.test.cpp
    title: test/wavelet_matrix_quantile.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    document_title: Wavelet Matrix
    links: []
  bundledCode: "#line 2 \"container/wavelet_matrix.cpp\"\n\n#line 2 \"container/bit_vector.cpp\"\
    \n\n#include <cstddef>\n#include <cstdint>\n#include <vector>\n#include <iterator>\n\
    #include <cassert>\n\nclass bit_vector {\npublic:\n  using size_type = size_t;\n\
    \  using bit_type = uint64_t;\n  using count_type = uint32_t;\n\nprivate:\n  size_type\
    \ M_size;\n  std::vector<bit_type> M_block;\n  std::vector<count_type> M_accum;\n\
    \npublic:\n  bit_vector() = default;\n  template <class InputIterator>\n  explicit\
    \ bit_vector(InputIterator first, InputIterator last) { construct(first, last);\
    \ }\n\n  template <class InputIterator>\n  void construct(InputIterator first,\
    \ InputIterator last) { \n    M_size = std::distance(first, last);\n    size_type\
    \ fixed_size = (M_size >> 6) + 1;\n    M_block.assign(fixed_size, 0);\n    M_accum.assign(fixed_size,\
    \ 0);\n    for (size_type i = 0; i < M_size; ++i) {\n      M_block[i >> 6] |=\
    \ (bit_type(*first) & 1) << (i & 63);\n      ++first;\n    }\n    for (size_type\
    \ i = 1; i < fixed_size; ++i) {\n      M_accum[i] = M_accum[i - 1] + __builtin_popcountll(M_block[i\
    \ - 1]);\n    }\n  }\n\n  bool access(size_type idx) const {\n    assert(idx <\
    \ M_size);\n    return M_block[idx >> 6] >> (idx & 63) & 1;\n  }\n  size_type\
    \ rank(bool value, size_type idx) const {\n    assert(idx <= M_size);\n    bit_type\
    \ mask = (bit_type(1) << (idx & 63)) - 1;\n    size_type res = M_accum[idx >>\
    \ 6] + __builtin_popcountll(M_block[idx >> 6] & mask);\n    return value ? res\
    \ : idx - res;\n  }\n  size_type select(bool value, size_type idx) const {\n \
    \   if (idx >= rank(value, M_size)) {\n      return M_size;\n    }\n    size_type\
    \ ok = 0, ng = M_size;\n    while (ng - ok > 1) {\n      size_type md = (ok +\
    \ ng) >> 1;\n      (rank(value, md) <= idx ? ok : ng) = md;\n    }\n    return\
    \ ok;\n  }\n  size_type select(bool value, size_type idx, size_type l) const {\n\
    \    assert(l <= M_size);\n    return select(value, idx + rank(value, l));\n \
    \ }\n};\n\n/**\n * @title Succinct Bit Vector\n */\n#line 4 \"container/wavelet_matrix.cpp\"\
    \n\n#include <array>\n#include <algorithm>\n#line 8 \"container/wavelet_matrix.cpp\"\
    \n\ntemplate <class T, size_t W>\nclass wavelet_matrix {\npublic:\n  using value_type\
    \ = T;\n  using size_type = size_t;\n\nprivate:\n  size_type M_size;\n  std::array<bit_vector,\
    \ W> M_fid;\n  std::array<size_type, W> M_zero;\n\npublic:\n  wavelet_matrix()\
    \ = default;\n  template <class InputIterator>\n  explicit wavelet_matrix(InputIterator\
    \ first, InputIterator last) { construct(first, last); }\n\n  template <class\
    \ InputIterator>\n  void construct(InputIterator first, InputIterator last) {\
    \ \n    M_size = std::distance(first, last);\n    std::vector<bool> bit(M_size);\n\
    \    std::vector<value_type> current(first, last);\n    std::vector<value_type>\
    \ next(M_size);\n    for (size_type k = W; k--;) {\n      auto l = next.begin();\n\
    \      auto r = next.rbegin();\n      for (size_type i = 0; i < M_size; ++i) {\n\
    \        bit[i] = current[i] >> k & 1;\n        (bit[i] ? *(r++) : *(l++)) = current[i];\n\
    \      }\n      M_fid[k].construct(bit.begin(), bit.end());\n      M_zero[k] =\
    \ l - next.begin();\n      std::reverse(next.rbegin(), r);\n      current.swap(next);\n\
    \    }\n  }\n\n  size_type rank(value_type value, size_type l, size_type r) const\
    \ {\n    assert(l <= r);\n    assert(r <= M_size);\n    for (size_type k = W;\
    \ k--;) {\n      bool p = value >> k & 1;\n      l = M_fid[k].rank(p, l) + p *\
    \ M_zero[k];\n      r = M_fid[k].rank(p, r) + p * M_zero[k];\n    }\n    return\
    \ r - l;\n  }\n\n  size_type select(value_type value, size_type index) const {\n\
    \    std::array<size_type, W + 1> l, r;\n    l[W] = 0;\n    r[W] = M_size;\n \
    \   for (size_type k = W; k--;) {\n      bool p = value >> k & 1;\n      l[k]\
    \ = M_fid[k].rank(p, l[k + 1]) + p * M_zero[k];\n      r[k] = M_fid[k].rank(p,\
    \ r[k + 1]) + p * M_zero[k];\n    }\n    if (r[0] - l[0] <= index) {\n      return\
    \ M_size;\n    }\n    for (size_type k = 0; k < W; ++k) {\n      bool p = value\
    \ >> k & 1;\n      index = M_fid[k].select(p, index, l[k + 1]) - l[k + 1];\n \
    \   }\n    return index;\n  }\n\n  value_type access(size_type index) const {\n\
    \    assert(index < M_size);\n    value_type res = 0;\n    for (size_type k =\
    \ W; k--;) {\n      bool p = M_fid[k].access(index);\n      res |= value_type(p)\
    \ << k;\n      index = M_fid[k].rank(p, index) + p * M_zero[k];\n    }\n    return\
    \ res;\n  }\n\n  value_type quantile(size_type index, size_type l, size_type r)\
    \ const {\n    assert(l <= r);\n    assert(r <= M_size);\n    value_type res =\
    \ 0;\n    for (size_type k = W; k--;) {\n      size_type lc = M_fid[k].rank(1,\
    \ l);\n      size_type rc = M_fid[k].rank(1, r);\n      size_type zc = (r - l)\
    \ - (rc - lc);\n      bool p = (index >= zc);\n      res |= value_type(p) << k;\n\
    \      if (p) {\n        l = lc + M_zero[k];\n        r = rc + M_zero[k];\n  \
    \      index -= zc;\n      }\n      else {\n        l -= lc;\n        r -= rc;\n\
    \      }\n    }\n    return res;\n  }\n\n  size_type count(size_type l, size_type\
    \ r, value_type value) const {\n    assert(l <= r);\n    assert(r <= M_size);\n\
    \    size_type res = 0;\n    for (size_type k = W; k--;) {\n      size_type lc\
    \ = M_fid[k].rank(1, l);\n      size_type rc = M_fid[k].rank(1, r);\n      if\
    \ (value >> (k) & 1) {\n        l = lc + M_zero[k];\n        r = rc + M_zero[k];\n\
    \      }\n      else {\n        l -= lc;\n        r -= rc;\n        res += (rc\
    \ - lc);\n      }\n    }\n    return res + (r - l);\n  }\n  size_type count(size_type\
    \ l, size_type r, value_type lb, value_type ub) const {\n    assert(l <= r);\n\
    \    assert(r <= M_size);\n    return count(l, r, lb) - count(l, r, ub);\n  }\n\
    };\n\n/**\n * @title Wavelet Matrix\n */\n"
  code: "#pragma once\n\n#include \"../container/bit_vector.cpp\"\n\n#include <array>\n\
    #include <algorithm>\n#include <cassert>\n\ntemplate <class T, size_t W>\nclass\
    \ wavelet_matrix {\npublic:\n  using value_type = T;\n  using size_type = size_t;\n\
    \nprivate:\n  size_type M_size;\n  std::array<bit_vector, W> M_fid;\n  std::array<size_type,\
    \ W> M_zero;\n\npublic:\n  wavelet_matrix() = default;\n  template <class InputIterator>\n\
    \  explicit wavelet_matrix(InputIterator first, InputIterator last) { construct(first,\
    \ last); }\n\n  template <class InputIterator>\n  void construct(InputIterator\
    \ first, InputIterator last) { \n    M_size = std::distance(first, last);\n  \
    \  std::vector<bool> bit(M_size);\n    std::vector<value_type> current(first,\
    \ last);\n    std::vector<value_type> next(M_size);\n    for (size_type k = W;\
    \ k--;) {\n      auto l = next.begin();\n      auto r = next.rbegin();\n     \
    \ for (size_type i = 0; i < M_size; ++i) {\n        bit[i] = current[i] >> k &\
    \ 1;\n        (bit[i] ? *(r++) : *(l++)) = current[i];\n      }\n      M_fid[k].construct(bit.begin(),\
    \ bit.end());\n      M_zero[k] = l - next.begin();\n      std::reverse(next.rbegin(),\
    \ r);\n      current.swap(next);\n    }\n  }\n\n  size_type rank(value_type value,\
    \ size_type l, size_type r) const {\n    assert(l <= r);\n    assert(r <= M_size);\n\
    \    for (size_type k = W; k--;) {\n      bool p = value >> k & 1;\n      l =\
    \ M_fid[k].rank(p, l) + p * M_zero[k];\n      r = M_fid[k].rank(p, r) + p * M_zero[k];\n\
    \    }\n    return r - l;\n  }\n\n  size_type select(value_type value, size_type\
    \ index) const {\n    std::array<size_type, W + 1> l, r;\n    l[W] = 0;\n    r[W]\
    \ = M_size;\n    for (size_type k = W; k--;) {\n      bool p = value >> k & 1;\n\
    \      l[k] = M_fid[k].rank(p, l[k + 1]) + p * M_zero[k];\n      r[k] = M_fid[k].rank(p,\
    \ r[k + 1]) + p * M_zero[k];\n    }\n    if (r[0] - l[0] <= index) {\n      return\
    \ M_size;\n    }\n    for (size_type k = 0; k < W; ++k) {\n      bool p = value\
    \ >> k & 1;\n      index = M_fid[k].select(p, index, l[k + 1]) - l[k + 1];\n \
    \   }\n    return index;\n  }\n\n  value_type access(size_type index) const {\n\
    \    assert(index < M_size);\n    value_type res = 0;\n    for (size_type k =\
    \ W; k--;) {\n      bool p = M_fid[k].access(index);\n      res |= value_type(p)\
    \ << k;\n      index = M_fid[k].rank(p, index) + p * M_zero[k];\n    }\n    return\
    \ res;\n  }\n\n  value_type quantile(size_type index, size_type l, size_type r)\
    \ const {\n    assert(l <= r);\n    assert(r <= M_size);\n    value_type res =\
    \ 0;\n    for (size_type k = W; k--;) {\n      size_type lc = M_fid[k].rank(1,\
    \ l);\n      size_type rc = M_fid[k].rank(1, r);\n      size_type zc = (r - l)\
    \ - (rc - lc);\n      bool p = (index >= zc);\n      res |= value_type(p) << k;\n\
    \      if (p) {\n        l = lc + M_zero[k];\n        r = rc + M_zero[k];\n  \
    \      index -= zc;\n      }\n      else {\n        l -= lc;\n        r -= rc;\n\
    \      }\n    }\n    return res;\n  }\n\n  size_type count(size_type l, size_type\
    \ r, value_type value) const {\n    assert(l <= r);\n    assert(r <= M_size);\n\
    \    size_type res = 0;\n    for (size_type k = W; k--;) {\n      size_type lc\
    \ = M_fid[k].rank(1, l);\n      size_type rc = M_fid[k].rank(1, r);\n      if\
    \ (value >> (k) & 1) {\n        l = lc + M_zero[k];\n        r = rc + M_zero[k];\n\
    \      }\n      else {\n        l -= lc;\n        r -= rc;\n        res += (rc\
    \ - lc);\n      }\n    }\n    return res + (r - l);\n  }\n  size_type count(size_type\
    \ l, size_type r, value_type lb, value_type ub) const {\n    assert(l <= r);\n\
    \    assert(r <= M_size);\n    return count(l, r, lb) - count(l, r, ub);\n  }\n\
    };\n\n/**\n * @title Wavelet Matrix\n */"
  dependsOn:
  - container/bit_vector.cpp
  isVerificationFile: false
  path: container/wavelet_matrix.cpp
  requiredBy: []
  timestamp: '2020-09-09 18:08:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/wavelet_matrix_quantile.test.cpp
documentation_of: container/wavelet_matrix.cpp
layout: document
redirect_from:
- /library/container/wavelet_matrix.cpp
- /library/container/wavelet_matrix.cpp.html
title: Wavelet Matrix
---
