---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: other/bit_operation.cpp
    title: Bit Operations
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    document_title: Number Theoretic Transform
    links: []
  bundledCode: "#line 2 \"algebraic/ntt.cpp\"\n\n#line 2 \"other/bit_operation.cpp\"\
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
    \ */\n#line 4 \"algebraic/ntt.cpp\"\n\n#line 6 \"algebraic/ntt.cpp\"\n#include\
    \ <vector>\n#include <array>\n#include <utility>\n#include <algorithm>\n\n// TODO:\
    \ make it better\nnamespace ntt_detail {\n\n  constexpr uint32_t primitive_root(const\
    \ uint32_t mod) {\n    std::array<uint32_t, 32> exp{};\n    uint32_t cur = mod\
    \ - 1;\n    size_t size = 0;\n    for (uint32_t i = 2; i * i <= cur; ++i) {\n\
    \      if (cur % i == 0) {\n        exp[size++] = (mod - 1) / i;\n        while\
    \ (cur % i == 0) cur /= i;\n      }\n    }\n    if (cur != 1) exp[size++] = (mod\
    \ - 1) / cur;\n    for (uint32_t check = 1; check < mod; ++check) {\n      for\
    \ (auto e: exp) {\n        if (e == 0) return check;\n        uint64_t a = check,\
    \ x = 1;\n        while (e > 0) {\n          if (e & 1) (x *= a) %= mod;\n   \
    \       (a *= a) %= mod;\n          e >>= 1;\n        }\n        if (x == 1) break;\n\
    \      }\n    }\n    return mod;\n  }\n\n  template <size_t N, class T>\n  constexpr\
    \ std::array<T, N> compute_roots(T omega) {\n    std::array<T, N> res;\n    res[N\
    \ - 1] = omega;\n    for (size_t i = N - 1; i > 0; --i) {\n      res[i - 1] =\
    \ res[i] * res[i];\n    }\n    return res;\n  }\n\n}\n\ntemplate <class Modular>\n\
    class number_theoretic_transform {\npublic:\n  using value_type = Modular;\n \
    \ static constexpr uint32_t mod = Modular::mod();\n  static constexpr uint32_t\
    \ prim = ntt_detail::primitive_root(mod);\n\nprivate:\n  static constexpr size_t\
    \ level = bit_ctzr(mod - 1);\n  static constexpr value_type omega = power(value_type(prim),\
    \ ((mod - 1) >> level)); \n  static constexpr auto roots = ntt_detail::compute_roots<level>(omega);\n\
    \  static constexpr auto inv_roots = ntt_detail::compute_roots<level>(inverse(omega));\n\
    \npublic:\n  static void transform(std::vector<value_type> &F) {\n    const size_t\
    \ size = F.size();\n    const size_t logn = bit_ctzr(size);\n    for (size_t i\
    \ = 0; i < size; ++i) {\n      const size_t j = bit_rev(i) >> (64 - logn);\n \
    \     if (i < j) std::swap(F[i], F[j]);\n    }\n    value_type coeff(1);\n   \
    \ for (size_t s = 0; s < logn; ++s) {\n      const size_t mh = 1 << s;\n     \
    \ const size_t m = mh << 1;\n      for (size_t i = 0; i < size; i += m) {\n  \
    \      coeff = value_type(1);\n        for (size_t j = i; j < i + mh; ++j) {\n\
    \          const auto a = F[j];\n          const auto b = F[j + mh] * coeff;\n\
    \          F[j] = a + b;\n          F[j + mh] = a - b;\n          coeff *= roots[s];\n\
    \        }\n      }\n    }\n  }\n\n  static void inv_transform(std::vector<value_type>\
    \ &F) {\n    const size_t size = F.size();\n    const size_t logn = bit_ctzr(size);\n\
    \    for (size_t i = 0; i < size; ++i) {\n      const size_t j = bit_rev(i) >>\
    \ (64 - logn);\n      if (i < j) std::swap(F[i], F[j]);\n    }\n    value_type\
    \ coeff(1);\n    for (size_t s = 0; s < logn; ++s) {\n      const size_t mh =\
    \ 1 << s;\n      const size_t m = mh << 1;\n      for (size_t i = 0; i < size;\
    \ i += m) {\n        coeff = value_type(1);\n        for (size_t j = i; j < i\
    \ + mh; ++j) {\n          const auto a = F[j];\n          const auto b = F[j +\
    \ mh] * coeff;\n          F[j] = a + b;\n          F[j + mh] = a - b;\n      \
    \    coeff *= inv_roots[s];\n        }\n      }\n    }\n    coeff = inverse(value_type(size));\n\
    \    for (auto &x: F) x *= coeff;\n  }\n\n};\n\n/**\n * @title Number Theoretic\
    \ Transform\n */\n"
  code: "#pragma once\n\n#include \"../other/bit_operation.cpp\"\n\n#include <cstddef>\n\
    #include <vector>\n#include <array>\n#include <utility>\n#include <algorithm>\n\
    \n// TODO: make it better\nnamespace ntt_detail {\n\n  constexpr uint32_t primitive_root(const\
    \ uint32_t mod) {\n    std::array<uint32_t, 32> exp{};\n    uint32_t cur = mod\
    \ - 1;\n    size_t size = 0;\n    for (uint32_t i = 2; i * i <= cur; ++i) {\n\
    \      if (cur % i == 0) {\n        exp[size++] = (mod - 1) / i;\n        while\
    \ (cur % i == 0) cur /= i;\n      }\n    }\n    if (cur != 1) exp[size++] = (mod\
    \ - 1) / cur;\n    for (uint32_t check = 1; check < mod; ++check) {\n      for\
    \ (auto e: exp) {\n        if (e == 0) return check;\n        uint64_t a = check,\
    \ x = 1;\n        while (e > 0) {\n          if (e & 1) (x *= a) %= mod;\n   \
    \       (a *= a) %= mod;\n          e >>= 1;\n        }\n        if (x == 1) break;\n\
    \      }\n    }\n    return mod;\n  }\n\n  template <size_t N, class T>\n  constexpr\
    \ std::array<T, N> compute_roots(T omega) {\n    std::array<T, N> res;\n    res[N\
    \ - 1] = omega;\n    for (size_t i = N - 1; i > 0; --i) {\n      res[i - 1] =\
    \ res[i] * res[i];\n    }\n    return res;\n  }\n\n}\n\ntemplate <class Modular>\n\
    class number_theoretic_transform {\npublic:\n  using value_type = Modular;\n \
    \ static constexpr uint32_t mod = Modular::mod();\n  static constexpr uint32_t\
    \ prim = ntt_detail::primitive_root(mod);\n\nprivate:\n  static constexpr size_t\
    \ level = bit_ctzr(mod - 1);\n  static constexpr value_type omega = power(value_type(prim),\
    \ ((mod - 1) >> level)); \n  static constexpr auto roots = ntt_detail::compute_roots<level>(omega);\n\
    \  static constexpr auto inv_roots = ntt_detail::compute_roots<level>(inverse(omega));\n\
    \npublic:\n  static void transform(std::vector<value_type> &F) {\n    const size_t\
    \ size = F.size();\n    const size_t logn = bit_ctzr(size);\n    for (size_t i\
    \ = 0; i < size; ++i) {\n      const size_t j = bit_rev(i) >> (64 - logn);\n \
    \     if (i < j) std::swap(F[i], F[j]);\n    }\n    value_type coeff(1);\n   \
    \ for (size_t s = 0; s < logn; ++s) {\n      const size_t mh = 1 << s;\n     \
    \ const size_t m = mh << 1;\n      for (size_t i = 0; i < size; i += m) {\n  \
    \      coeff = value_type(1);\n        for (size_t j = i; j < i + mh; ++j) {\n\
    \          const auto a = F[j];\n          const auto b = F[j + mh] * coeff;\n\
    \          F[j] = a + b;\n          F[j + mh] = a - b;\n          coeff *= roots[s];\n\
    \        }\n      }\n    }\n  }\n\n  static void inv_transform(std::vector<value_type>\
    \ &F) {\n    const size_t size = F.size();\n    const size_t logn = bit_ctzr(size);\n\
    \    for (size_t i = 0; i < size; ++i) {\n      const size_t j = bit_rev(i) >>\
    \ (64 - logn);\n      if (i < j) std::swap(F[i], F[j]);\n    }\n    value_type\
    \ coeff(1);\n    for (size_t s = 0; s < logn; ++s) {\n      const size_t mh =\
    \ 1 << s;\n      const size_t m = mh << 1;\n      for (size_t i = 0; i < size;\
    \ i += m) {\n        coeff = value_type(1);\n        for (size_t j = i; j < i\
    \ + mh; ++j) {\n          const auto a = F[j];\n          const auto b = F[j +\
    \ mh] * coeff;\n          F[j] = a + b;\n          F[j + mh] = a - b;\n      \
    \    coeff *= inv_roots[s];\n        }\n      }\n    }\n    coeff = inverse(value_type(size));\n\
    \    for (auto &x: F) x *= coeff;\n  }\n\n};\n\n/**\n * @title Number Theoretic\
    \ Transform\n */"
  dependsOn:
  - other/bit_operation.cpp
  isVerificationFile: false
  path: algebraic/ntt.cpp
  requiredBy: []
  timestamp: '2020-09-13 16:51:07+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: algebraic/ntt.cpp
layout: document
redirect_from:
- /library/algebraic/ntt.cpp
- /library/algebraic/ntt.cpp.html
title: Number Theoretic Transform
---
