---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: container/fenwick_tree.cpp
    title: Fenwick Tree
  - icon: ':heavy_check_mark:'
    path: graph/heavy_light_decomposition.cpp
    title: Heavy-Light Decomposition
  - icon: ':heavy_check_mark:'
    path: other/bit_operation.cpp
    title: Bit Operations
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/vertex_add_path_sum
    links:
    - https://judge.yosupo.jp/problem/vertex_add_path_sum
  bundledCode: "#line 1 \"test/vertex_set_path_sum.test.cpp\"\n\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/vertex_add_path_sum\"\n\n#line 2 \"graph/heavy_light_decomposition.cpp\"\
    \n\n#include <cstddef>\n#include <vector>\n#include <utility>\n#include <cassert>\n\
    \nclass heavy_light_decomposition {\npublic:\n  using size_type = size_t;\n\n\
    private:\n  std::vector<std::vector<size_type>> M_graph;\n  std::vector<size_type>\
    \ M_size, M_parent, M_head;\n  size_type M_index;\n\n  void M_calc_subtree(size_type\
    \ u, size_type p) {\n    M_size[u] = 1;\n    for (auto v: M_graph[u]) {\n    \
    \  if (v != p) {\n        M_calc_subtree(v, u);\n        M_size[u] += M_size[v];\n\
    \      }\n    }\n  }\n\n  void M_decompose(size_type u, size_type p, size_type\
    \ h) {\n    label[u] = M_index;\n    M_head[u] = h;\n    M_parent[u] = p;\n  \
    \  ++M_index;\n    size_type max = 0, heavy = -1;\n    for (auto v: M_graph[u])\
    \ {\n      if (v != p) {\n        if (max < M_size[v]) {\n          max = M_size[v];\n\
    \          heavy = v;\n        }\n      }\n    }\n    if (heavy == size_type(-1))\
    \ return;\n    M_decompose(heavy, u, h);\n    for (auto v: M_graph[u]) {\n   \
    \   if (v != p && v != heavy) {\n        M_decompose(v, u, v);\n      }\n    }\n\
    \  }\n\npublic:\n  std::vector<size_type> label;\n\n  heavy_light_decomposition()\
    \ { }\n  explicit heavy_light_decomposition(size_type size) { initialize(size);\
    \ }\n\n  void initialize(size_type size) {\n    clear();\n    M_index = 0;\n \
    \   M_graph.assign(size, { });\n    M_size.assign(size, 0);\n    M_parent.assign(size,\
    \ 0);\n    M_head.assign(size, 0);\n    label.assign(size, 0);\n  }\n  void construct(size_type\
    \ root = 0) {\n    assert(root < M_graph.size());\n    M_calc_subtree(root, -1);\n\
    \    M_decompose(root, -1, root);\n  }\n  void add_edge(size_type u, size_type\
    \ v) {\n    assert(u < M_graph.size());\n    assert(v < M_graph.size());\n   \
    \ assert(u != v);\n    M_graph[u].push_back(v);\n    M_graph[v].push_back(u);\n\
    \  }\n\n  template <class Func> \n  void each_edge(size_type u, size_type v, const\
    \ Func &func) const {\n    assert(u < M_graph.size());\n    assert(v < M_graph.size());\n\
    \    while (true) {\n      if (label[u] > label[v]) {\n        std::swap(u, v);\n\
    \      }\n      if (M_head[u] == M_head[v]) {\n        if (label[u] + 1 <= label[v])\
    \ {\n          func(label[u] + 1, label[v]);\n        }\n        return;\n   \
    \   }\n      func(label[M_head[v]], label[v]);\n      v = M_parent[M_head[v]];\n\
    \    }\n  }\n\n  template <class Func> \n  void each_vertex(size_type u, size_type\
    \ v, const Func &func) const {\n    assert(u < M_graph.size());\n    assert(v\
    \ < M_graph.size());\n    while (true) {\n      if (label[u] > label[v]) {\n \
    \       std::swap(u, v);\n      }\n      if (M_head[u] == M_head[v]) {\n     \
    \   func(label[u], label[v]);\n        return;\n      }\n      func(label[M_head[v]],\
    \ label[v]);\n      v = M_parent[M_head[v]];\n    }\n  }\n\n  size_type lca(size_type\
    \ u, size_type v) const {\n    assert(u < M_graph.size());\n    assert(v < M_graph.size());\n\
    \    if (label[u] > label[v]) {\n      std::swap(u, v);\n    }\n    while (label[u]\
    \ <= label[v]) {\n      if (M_head[u] == M_head[v]) {\n        return u;\n   \
    \   }\n      v = M_parent[M_head[v]];\n    }\n    return v;\n  }\n\n  size_type\
    \ size() const {\n    return M_graph.size();\n  }\n  bool empty() const {\n  \
    \  return M_graph.empty();\n  }\n  void clear() {\n    M_index = 0;\n    M_graph.clear();\n\
    \    M_graph.shrink_to_fit();\n    M_size.clear();\n    M_size.shrink_to_fit();\n\
    \    M_parent.clear();\n    M_parent.shrink_to_fit();\n    M_head.clear();\n \
    \   M_head.shrink_to_fit();\n    label.clear();\n    label.shrink_to_fit();\n\
    \  }\n};\n\n/**\n * @title Heavy-Light Decomposition\n */\n#line 2 \"container/fenwick_tree.cpp\"\
    \n\n#line 2 \"other/bit_operation.cpp\"\n\n#line 4 \"other/bit_operation.cpp\"\
    \n#include <cstdint>\n\nconstexpr size_t bit_ppc(const uint64_t x) { return __builtin_popcountll(x);\
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
    \ (x << 32);\n  return x;\n}\n\n/**\n * @title Bit Operations\n */\n#line 4 \"\
    container/fenwick_tree.cpp\"\n\n#line 8 \"container/fenwick_tree.cpp\"\n#include\
    \ <type_traits>\n\ntemplate <class T>\nclass fenwick_tree {\npublic:\n  using\
    \ value_type = T;\n  using size_type = size_t;\n\nprivate:\n  std::vector<value_type>\
    \ M_tree;\n\npublic:\n  fenwick_tree() = default;\n  explicit fenwick_tree(size_type\
    \ size) { initialize(size); }\n\n  void initialize(size_type size) {\n    M_tree.assign(size\
    \ + 1, value_type { });\n  }\n\n  void add(size_type index, const value_type&\
    \ x) {\n    assert(index < size());\n    ++index;\n    while (index <= size())\
    \ {\n      M_tree[index] += x;\n      index += bit_lsb(index);\n    }\n  }\n\n\
    \  template <size_type Indexed = 1>\n  value_type get(size_type index) const {\n\
    \    assert(index < size());\n    index += Indexed;\n    value_type res{ };\n\
    \    while (index > 0) {\n      res += M_tree[index];\n      index -= bit_lsb(index);\n\
    \    }\n    return res;\n  }\n  value_type fold(size_type first, size_type last)\
    \ const {\n    assert(first <= last);\n    assert(last <= size());\n    value_type\
    \ res{};\n    while (first < last) {\n      res += M_tree[last];\n      last -=\
    \ bit_lsb(last);\n    }\n    while (last < first) {\n      res -= M_tree[first];\n\
    \      first -= bit_lsb(first);\n    }\n    return res;\n  }\n\n  template <class\
    \ Func>\n  size_type satisfies(const size_type left, Func &&func) const {\n  \
    \  assert(left <= size());\n    if (func(value_type { })) return left;\n    value_type\
    \ val = -get<0>(left);\n    size_type res = 0;\n    for (size_type cur = bit_cover(size()\
    \ + 1) >> 1; cur > 0; cur >>= 1) {\n      if ((res + cur <= left) || (res + cur\
    \ <= size() && !func(val + M_tree[res + cur]))) {\n        val += M_tree[res +\
    \ cur];\n        res += cur;\n      }\n    }\n    return res + 1;\n  }\n\n  void\
    \ clear() {\n    M_tree.clear();\n    M_tree.shrink_to_fit();\n  }\n  size_type\
    \ size() const {\n    return M_tree.size() - 1;\n  }\n};\n\n/**\n * @title Fenwick\
    \ Tree\n */\n#line 6 \"test/vertex_set_path_sum.test.cpp\"\n\n#line 10 \"test/vertex_set_path_sum.test.cpp\"\
    \n#include <iostream>\n\nint main() {\n  size_t N, Q;\n  std::cin >> N >> Q;\n\
    \  std::vector<uint64_t> A(N);\n  for (auto &x: A) {\n    std::cin >> x;\n  }\n\
    \  heavy_light_decomposition hld(N);\n  for (size_t i = 1; i < N; ++i) {\n   \
    \ size_t x, y;\n    std::cin >> x >> y;\n    hld.add_edge(x, y);\n  }\n  hld.construct();\n\
    \  fenwick_tree<uint64_t> fen(N);\n  for (size_t i = 0; i < N; ++i) {\n    fen.add(hld.label[i],\
    \ A[i]);\n  }\n  uint64_t answer;\n  const auto query = [&](const size_t x, const\
    \ size_t y) {\n    answer += fen.fold(x, y + 1);\n  };\n  while (Q--) {\n    size_t\
    \ t;\n    std::cin >> t;\n    if (t == 0) {\n      size_t p;\n      uint64_t x;\n\
    \      std::cin >> p >> x;\n      fen.add(hld.label[p], x);\n    }\n    else {\n\
    \      size_t x, y;\n      std::cin >> x >> y;\n      answer = 0;\n      hld.each_vertex(x,\
    \ y, query);\n      std::cout << answer << '\\n';\n    }\n  }\n  return 0;\n}\n"
  code: "\n#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_path_sum\"\
    \n\n#include \"../graph/heavy_light_decomposition.cpp\"\n#include \"../container/fenwick_tree.cpp\"\
    \n\n#include <cstddef>\n#include <cstdint>\n#include <vector>\n#include <iostream>\n\
    \nint main() {\n  size_t N, Q;\n  std::cin >> N >> Q;\n  std::vector<uint64_t>\
    \ A(N);\n  for (auto &x: A) {\n    std::cin >> x;\n  }\n  heavy_light_decomposition\
    \ hld(N);\n  for (size_t i = 1; i < N; ++i) {\n    size_t x, y;\n    std::cin\
    \ >> x >> y;\n    hld.add_edge(x, y);\n  }\n  hld.construct();\n  fenwick_tree<uint64_t>\
    \ fen(N);\n  for (size_t i = 0; i < N; ++i) {\n    fen.add(hld.label[i], A[i]);\n\
    \  }\n  uint64_t answer;\n  const auto query = [&](const size_t x, const size_t\
    \ y) {\n    answer += fen.fold(x, y + 1);\n  };\n  while (Q--) {\n    size_t t;\n\
    \    std::cin >> t;\n    if (t == 0) {\n      size_t p;\n      uint64_t x;\n \
    \     std::cin >> p >> x;\n      fen.add(hld.label[p], x);\n    }\n    else {\n\
    \      size_t x, y;\n      std::cin >> x >> y;\n      answer = 0;\n      hld.each_vertex(x,\
    \ y, query);\n      std::cout << answer << '\\n';\n    }\n  }\n  return 0;\n}\n"
  dependsOn:
  - graph/heavy_light_decomposition.cpp
  - container/fenwick_tree.cpp
  - other/bit_operation.cpp
  isVerificationFile: true
  path: test/vertex_set_path_sum.test.cpp
  requiredBy: []
  timestamp: '2020-09-09 22:02:05+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/vertex_set_path_sum.test.cpp
layout: document
redirect_from:
- /verify/test/vertex_set_path_sum.test.cpp
- /verify/test/vertex_set_path_sum.test.cpp.html
title: test/vertex_set_path_sum.test.cpp
---
