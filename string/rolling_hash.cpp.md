---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/random_number.cpp
    title: Random Number
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    document_title: Rolling Hash
    links: []
  bundledCode: "#line 2 \"string/rolling_hash.cpp\"\n\n#line 2 \"other/random_number.cpp\"\
    \n\n#include <cstdint>\n#include <random>\n#include <chrono>\n#include <array>\n\
    #include <type_traits>\n\nuint64_t engine() {\n  static const auto rotate = [](const\
    \ uint64_t x, const size_t k) {\n    return (x << k) | (x >> (64 - k));\n  };\n\
    \  static auto array = [] {\n    uint64_t seed = static_cast<uint64_t>(std::chrono::system_clock::now().time_since_epoch().count());\n\
    \    std::array<uint64_t, 4> res{};\n    for (size_t index = 0; index < 4; index++)\
    \ {\n      uint64_t value = (seed += 0x9e3779b97f4a7c15);\n      value = (value\
    \ ^ (value >> 30)) * 0xbf58476d1ce4e5b9;\n      value = (value ^ (value >> 27))\
    \ * 0x94d049bb133111eb;\n      res[index] = value ^ (value >> 31);\n    }\n  \
    \  return res;\n  }();\n  const uint64_t result = rotate(array[1] * 5, 7) * 9;\n\
    \  const uint64_t old_value = array[1] << 17;\n  array[2] ^= array[0];\n  array[3]\
    \ ^= array[1];\n  array[1] ^= array[2];\n  array[0] ^= array[3];\n  array[2] ^=\
    \ old_value;\n  array[3] = rotate(array[3], 45);\n  return result;\n}\n\ntemplate\
    \ <class Integer>\ntypename std::enable_if<std::is_integral<Integer>::value, Integer>::type\
    \ random_number(Integer lower, Integer upper) {\n  static std::default_random_engine\
    \ gen(engine());\n  return std::uniform_int_distribution<Integer>(lower, upper)(gen);\n\
    }\n\ntemplate <class Real>\ntypename std::enable_if<!std::is_integral<Real>::value,\
    \ Real>::type random_number(Real lower, Real upper) {\n  static std::default_random_engine\
    \ gen(engine());\n  return std::uniform_real_distribution<Real>(lower, upper)(gen);\n\
    }\n\n/** \n * @title Random Number\n */\n#line 4 \"string/rolling_hash.cpp\"\n\
    \n#include <cstddef>\n#line 7 \"string/rolling_hash.cpp\"\n#include <vector>\n\
    #include <string>\n#include <cassert>\n\nnamespace rolling_hash_detail {\n\nclass\
    \ hash61_t {\npublic:\n\n  static constexpr uint64_t mod() {\n    return (static_cast<uint64_t>(1)\
    \ << 61) - 1;\n  }\n  static uint32_t base() {\n    static const uint32_t value\
    \ = static_cast<uint32_t>(engine());\n    return value;\n  }\n\n  static constexpr\
    \ uint64_t add(uint64_t a, uint64_t b) {\n    a += b;\n    if (a >= mod()) a -=\
    \ mod();\n    return a;\n  }\n  static constexpr uint64_t sub(uint64_t a, uint64_t\
    \ b) {\n    a += mod() - b;\n    if (a >= mod()) a -= mod();\n    return a;\n\
    \  }\n  static constexpr uint64_t mul(uint64_t a, uint64_t b) {\n    uint64_t\
    \ l1 = (uint32_t) a, h1 = a >> 32, l2 = (uint32_t) b, h2 = b >> 32;\n    uint64_t\
    \ l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;\n    uint64_t res = (l & mod())\
    \ + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;\n    res = (res & mod())\
    \ + (res >> 61);\n    res = (res & mod()) + (res >> 61);\n    return res - 1;\n\
    \  }\n\n  static std::vector<uint64_t> reserve;\n  static uint64_t power(const\
    \ size_t index) {\n    if (index >= reserve.size()) {\n      size_t cur = reserve.size();\n\
    \      reserve.resize(index + 1);\n      for (; cur <= index; ++cur) {\n     \
    \   reserve[cur] = mul(reserve[cur - 1], base());\n      }\n    }\n    return\
    \ reserve[index];\n  }\n\n};\n\nstd::vector<uint64_t> hash61_t::reserve = std::vector<uint64_t>(1,\
    \ 1);\n\n};\n\nclass rolling_hash {\npublic:\n  using hash_type = uint64_t;\n\
    \  using size_type = size_t;\n\nprivate:\n  using op_t = rolling_hash_detail::hash61_t;\n\
    \n  std::string M_string;\n  std::vector<hash_type> M_hash;\n\npublic:\n  rolling_hash()\
    \ { initialize(); }\n  rolling_hash(const std::string &initial_) { construct(initial_);\
    \ }\n\n  void initialize() {\n    clear();\n    M_string = \"\";\n    M_hash.assign(1,\
    \ 0);\n  }\n  void construct(const std::string &initial_) {\n    initialize();\n\
    \    add_string(initial_);\n  }\n\n  void add_string(const std::string &str) {\n\
    \    size_type cur_size = M_string.size();\n    size_type next_size = M_string.size()\
    \ + str.size();\n    M_string += str;\n    M_hash.resize(next_size + 1);\n   \
    \ for (size_type i = cur_size; i < next_size; ++i) {\n      M_hash[i + 1] = op_t::add(op_t::mul(M_hash[i],\
    \ op_t::base()), M_string[i]);\n    }\n  }\n\n  hash_type hash(size_type l, size_type\
    \ r) const {\n    assert(l <= r);\n    assert(r <= size());\n    return op_t::sub(M_hash[r],\
    \ op_t::mul(op_t::power(r - l), M_hash[l]));\n  }\n  size_type lcp(size_type l,\
    \ size_type r) const {\n    assert(l < size());\n    assert(r < size());\n   \
    \ size_type ok = 0, ng = std::min(M_string.size() - l, M_string.size() - r) +\
    \ 1;\n    while (ng - ok > 1) {\n      size_type md = (ok + ng) >> 1;\n      (hash(l,\
    \ l + md) == hash(r, r + md) ? ok : ng) = md;\n    }\n    return ok;\n  }\n\n\
    \  const std::string &get() const {\n    return M_string;\n  }\n  size_type size()\
    \ const {\n    return M_string.size();\n  }\n  bool empty() const {\n    return\
    \ M_string.empty();\n  }\n  void clear() {\n    M_string.clear();\n    M_string.shrink_to_fit();\n\
    \    M_hash.clear();\n    M_hash.shrink_to_fit();\n  }\n};\n\n/**\n * @title Rolling\
    \ Hash\n */\n"
  code: "#pragma once\n\n#include \"../other/random_number.cpp\"\n\n#include <cstddef>\n\
    #include <cstdint>\n#include <vector>\n#include <string>\n#include <cassert>\n\
    \nnamespace rolling_hash_detail {\n\nclass hash61_t {\npublic:\n\n  static constexpr\
    \ uint64_t mod() {\n    return (static_cast<uint64_t>(1) << 61) - 1;\n  }\n  static\
    \ uint32_t base() {\n    static const uint32_t value = static_cast<uint32_t>(engine());\n\
    \    return value;\n  }\n\n  static constexpr uint64_t add(uint64_t a, uint64_t\
    \ b) {\n    a += b;\n    if (a >= mod()) a -= mod();\n    return a;\n  }\n  static\
    \ constexpr uint64_t sub(uint64_t a, uint64_t b) {\n    a += mod() - b;\n    if\
    \ (a >= mod()) a -= mod();\n    return a;\n  }\n  static constexpr uint64_t mul(uint64_t\
    \ a, uint64_t b) {\n    uint64_t l1 = (uint32_t) a, h1 = a >> 32, l2 = (uint32_t)\
    \ b, h2 = b >> 32;\n    uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 *\
    \ h2;\n    uint64_t res = (l & mod()) + (l >> 61) + (h << 3) + (m >> 29) + (m\
    \ << 35 >> 3) + 1;\n    res = (res & mod()) + (res >> 61);\n    res = (res & mod())\
    \ + (res >> 61);\n    return res - 1;\n  }\n\n  static std::vector<uint64_t> reserve;\n\
    \  static uint64_t power(const size_t index) {\n    if (index >= reserve.size())\
    \ {\n      size_t cur = reserve.size();\n      reserve.resize(index + 1);\n  \
    \    for (; cur <= index; ++cur) {\n        reserve[cur] = mul(reserve[cur - 1],\
    \ base());\n      }\n    }\n    return reserve[index];\n  }\n\n};\n\nstd::vector<uint64_t>\
    \ hash61_t::reserve = std::vector<uint64_t>(1, 1);\n\n};\n\nclass rolling_hash\
    \ {\npublic:\n  using hash_type = uint64_t;\n  using size_type = size_t;\n\nprivate:\n\
    \  using op_t = rolling_hash_detail::hash61_t;\n\n  std::string M_string;\n  std::vector<hash_type>\
    \ M_hash;\n\npublic:\n  rolling_hash() { initialize(); }\n  rolling_hash(const\
    \ std::string &initial_) { construct(initial_); }\n\n  void initialize() {\n \
    \   clear();\n    M_string = \"\";\n    M_hash.assign(1, 0);\n  }\n  void construct(const\
    \ std::string &initial_) {\n    initialize();\n    add_string(initial_);\n  }\n\
    \n  void add_string(const std::string &str) {\n    size_type cur_size = M_string.size();\n\
    \    size_type next_size = M_string.size() + str.size();\n    M_string += str;\n\
    \    M_hash.resize(next_size + 1);\n    for (size_type i = cur_size; i < next_size;\
    \ ++i) {\n      M_hash[i + 1] = op_t::add(op_t::mul(M_hash[i], op_t::base()),\
    \ M_string[i]);\n    }\n  }\n\n  hash_type hash(size_type l, size_type r) const\
    \ {\n    assert(l <= r);\n    assert(r <= size());\n    return op_t::sub(M_hash[r],\
    \ op_t::mul(op_t::power(r - l), M_hash[l]));\n  }\n  size_type lcp(size_type l,\
    \ size_type r) const {\n    assert(l < size());\n    assert(r < size());\n   \
    \ size_type ok = 0, ng = std::min(M_string.size() - l, M_string.size() - r) +\
    \ 1;\n    while (ng - ok > 1) {\n      size_type md = (ok + ng) >> 1;\n      (hash(l,\
    \ l + md) == hash(r, r + md) ? ok : ng) = md;\n    }\n    return ok;\n  }\n\n\
    \  const std::string &get() const {\n    return M_string;\n  }\n  size_type size()\
    \ const {\n    return M_string.size();\n  }\n  bool empty() const {\n    return\
    \ M_string.empty();\n  }\n  void clear() {\n    M_string.clear();\n    M_string.shrink_to_fit();\n\
    \    M_hash.clear();\n    M_hash.shrink_to_fit();\n  }\n};\n\n/**\n * @title Rolling\
    \ Hash\n */"
  dependsOn:
  - other/random_number.cpp
  isVerificationFile: false
  path: string/rolling_hash.cpp
  requiredBy: []
  timestamp: '2020-09-09 18:08:09+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: string/rolling_hash.cpp
layout: document
redirect_from:
- /library/string/rolling_hash.cpp
- /library/string/rolling_hash.cpp.html
title: Rolling Hash
---
