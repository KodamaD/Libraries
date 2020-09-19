---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: container/wavelet_matrix.cpp
    title: Wavelet Matrix
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/wavelet_matrix_quantile.test.cpp
    title: test/wavelet_matrix_quantile.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    document_title: Succinct Bit Vector
    links: []
  bundledCode: "#line 2 \"container/bit_vector.cpp\"\n\n#include <cstddef>\n#include\
    \ <cstdint>\n#include <vector>\n#include <iterator>\n#include <cassert>\n\nclass\
    \ bit_vector {\npublic:\n  using size_type = size_t;\n  using bit_type = uint64_t;\n\
    \  using count_type = uint32_t;\n\nprivate:\n  size_type M_size;\n  std::vector<bit_type>\
    \ M_block;\n  std::vector<count_type> M_accum;\n\npublic:\n  bit_vector() = default;\n\
    \  template <class InputIterator>\n  explicit bit_vector(InputIterator first,\
    \ InputIterator last) { construct(first, last); }\n\n  template <class InputIterator>\n\
    \  void construct(InputIterator first, InputIterator last) { \n    M_size = std::distance(first,\
    \ last);\n    size_type fixed_size = (M_size >> 6) + 1;\n    M_block.assign(fixed_size,\
    \ 0);\n    M_accum.assign(fixed_size, 0);\n    for (size_type i = 0; i < M_size;\
    \ ++i) {\n      M_block[i >> 6] |= (bit_type(*first) & 1) << (i & 63);\n     \
    \ ++first;\n    }\n    for (size_type i = 1; i < fixed_size; ++i) {\n      M_accum[i]\
    \ = M_accum[i - 1] + __builtin_popcountll(M_block[i - 1]);\n    }\n  }\n\n  bool\
    \ access(size_type idx) const {\n    assert(idx < M_size);\n    return M_block[idx\
    \ >> 6] >> (idx & 63) & 1;\n  }\n  size_type rank(bool value, size_type idx) const\
    \ {\n    assert(idx <= M_size);\n    bit_type mask = (bit_type(1) << (idx & 63))\
    \ - 1;\n    size_type res = M_accum[idx >> 6] + __builtin_popcountll(M_block[idx\
    \ >> 6] & mask);\n    return value ? res : idx - res;\n  }\n  size_type select(bool\
    \ value, size_type idx) const {\n    if (idx >= rank(value, M_size)) {\n     \
    \ return M_size;\n    }\n    size_type ok = 0, ng = M_size;\n    while (ng - ok\
    \ > 1) {\n      size_type md = (ok + ng) >> 1;\n      (rank(value, md) <= idx\
    \ ? ok : ng) = md;\n    }\n    return ok;\n  }\n  size_type select(bool value,\
    \ size_type idx, size_type l) const {\n    assert(l <= M_size);\n    return select(value,\
    \ idx + rank(value, l));\n  }\n};\n\n/**\n * @title Succinct Bit Vector\n */\n"
  code: "#pragma once\n\n#include <cstddef>\n#include <cstdint>\n#include <vector>\n\
    #include <iterator>\n#include <cassert>\n\nclass bit_vector {\npublic:\n  using\
    \ size_type = size_t;\n  using bit_type = uint64_t;\n  using count_type = uint32_t;\n\
    \nprivate:\n  size_type M_size;\n  std::vector<bit_type> M_block;\n  std::vector<count_type>\
    \ M_accum;\n\npublic:\n  bit_vector() = default;\n  template <class InputIterator>\n\
    \  explicit bit_vector(InputIterator first, InputIterator last) { construct(first,\
    \ last); }\n\n  template <class InputIterator>\n  void construct(InputIterator\
    \ first, InputIterator last) { \n    M_size = std::distance(first, last);\n  \
    \  size_type fixed_size = (M_size >> 6) + 1;\n    M_block.assign(fixed_size, 0);\n\
    \    M_accum.assign(fixed_size, 0);\n    for (size_type i = 0; i < M_size; ++i)\
    \ {\n      M_block[i >> 6] |= (bit_type(*first) & 1) << (i & 63);\n      ++first;\n\
    \    }\n    for (size_type i = 1; i < fixed_size; ++i) {\n      M_accum[i] = M_accum[i\
    \ - 1] + __builtin_popcountll(M_block[i - 1]);\n    }\n  }\n\n  bool access(size_type\
    \ idx) const {\n    assert(idx < M_size);\n    return M_block[idx >> 6] >> (idx\
    \ & 63) & 1;\n  }\n  size_type rank(bool value, size_type idx) const {\n    assert(idx\
    \ <= M_size);\n    bit_type mask = (bit_type(1) << (idx & 63)) - 1;\n    size_type\
    \ res = M_accum[idx >> 6] + __builtin_popcountll(M_block[idx >> 6] & mask);\n\
    \    return value ? res : idx - res;\n  }\n  size_type select(bool value, size_type\
    \ idx) const {\n    if (idx >= rank(value, M_size)) {\n      return M_size;\n\
    \    }\n    size_type ok = 0, ng = M_size;\n    while (ng - ok > 1) {\n      size_type\
    \ md = (ok + ng) >> 1;\n      (rank(value, md) <= idx ? ok : ng) = md;\n    }\n\
    \    return ok;\n  }\n  size_type select(bool value, size_type idx, size_type\
    \ l) const {\n    assert(l <= M_size);\n    return select(value, idx + rank(value,\
    \ l));\n  }\n};\n\n/**\n * @title Succinct Bit Vector\n */"
  dependsOn: []
  isVerificationFile: false
  path: container/bit_vector.cpp
  requiredBy:
  - container/wavelet_matrix.cpp
  timestamp: '2020-09-09 18:08:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/wavelet_matrix_quantile.test.cpp
documentation_of: container/bit_vector.cpp
layout: document
redirect_from:
- /library/container/bit_vector.cpp
- /library/container/bit_vector.cpp.html
title: Succinct Bit Vector
---
