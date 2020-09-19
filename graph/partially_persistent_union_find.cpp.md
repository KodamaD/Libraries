---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    document_title: Partially Persistent Union Find
    links: []
  bundledCode: "#line 2 \"graph/partially_persistent_union_find.cpp\"\n\n#include\
    \ <cstddef>\n#include <vector>\n#include <utility>\n#include <algorithm>\n#include\
    \ <cassert>\n\nclass partially_persistent_union_find {\npublic:\n  using size_type\
    \ = size_t;\n  using time_type = size_t;\n\n  static time_type far_future() {\n\
    \    return static_cast<time_type>(-1);\n  }\n\nprivate:\n  class node_type {\n\
    \  public:\n    size_type parent;\n    time_type updated;\n    std::vector<time_type>\
    \ history;\n    std::vector<size_type> size;\n    node_type(size_type parent):\n\
    \      parent(parent), updated(far_future()),\n      history(1, 0), size(1, 1)\n\
    \    { }\n  };\n\n  std::vector<node_type> M_forest;\n  std::vector<size_type>\
    \ M_components;\n\npublic:\n  partially_persistent_union_find() = default;\n \
    \ explicit partially_persistent_union_find(const size_type size) { initialize(size);\
    \ }\n\n  void initialize(const size_type size) {\n    clear();\n    M_forest.reserve(size);\n\
    \    for (size_type index = 0; index < size; ++index) {\n      M_forest.emplace_back(index);\n\
    \    }\n    M_components.push_back(size);\n  }\n\n  size_type find_parent(const\
    \ size_type node, const time_type time) const {\n    assert(node < size());\n\
    \    if (M_forest[node].updated > time) return node;\n    return find_parent(M_forest[node].parent,\
    \ time);\n  }\n  size_type count_components(const time_type time) const {\n  \
    \  return M_components[std::min(now(), time)];\n  }\n  size_type component_size(size_type\
    \ node, time_type time) const {\n    assert(node < size());\n    time = std::min(time,\
    \ now());\n    node = find_parent(node, time);\n    const auto &history = M_forest[node].history;\n\
    \    auto index = std::lower_bound(history.cbegin(), history.cend(), time + 1)\
    \ - history.cbegin() - 1;\n    return M_forest[node].size[index];\n  }\n\n  time_type\
    \ when(const size_type node1, const size_type node2) const {\n    assert(node1\
    \ < size());\n    assert(node2 < size());\n    if (!same_component(node1, node2,\
    \ now())) return far_future();\n    time_type ok = now(), ng = 0, md;\n    while\
    \ (ok - ng > 1) {\n      md = (ok + ng) / 2;\n      (same_component(node1, node2,\
    \ md) ? ok : ng) = md;\n    }\n    return ok;\n  }\n\n  bool same_component(const\
    \ size_type node1, const size_type node2, const time_type time) const {\n    assert(node1\
    \ < size());\n    assert(node2 < size());\n    return find_parent(node1, time)\
    \ == find_parent(node2, time);\n  }\n  bool unite(size_type node1, size_type node2)\
    \ {\n    assert(node1 < size());\n    assert(node2 < size());\n    node1 = find_parent(node1,\
    \ now());\n    node2 = find_parent(node2, now());\n    size_type current = M_components.back();\n\
    \    if (node1 == node2) {\n      M_components.push_back(current);\n      return\
    \ false;\n    }\n    M_components.push_back(current - 1);\n    const size_type\
    \ size1 = M_forest[node1].size.back();\n    const size_type size2 = M_forest[node2].size.back();\n\
    \    if (size1 < size2) std::swap(node1, node2);\n    M_forest[node1].history.push_back(now());\n\
    \    M_forest[node1].size.push_back(size1 + size2);\n    M_forest[node2].parent\
    \ = node1;\n    M_forest[node2].updated = now();\n    return true;\n  }\n\n  time_type\
    \ now() const {\n    return M_components.size() - 1;\n  }\n  size_type size()\
    \ const {\n    return M_forest.size();\n  }\n  bool empty() const {\n    return\
    \ M_forest.empty();\n  }\n  void clear() {\n    M_forest.clear();\n    M_forest.shrink_to_fit();\n\
    \    M_components.clear();\n    M_components.shrink_to_fit();\n  }\n};\n\n/**\n\
    \ * @title Partially Persistent Union Find\n */\n"
  code: "#pragma once\n\n#include <cstddef>\n#include <vector>\n#include <utility>\n\
    #include <algorithm>\n#include <cassert>\n\nclass partially_persistent_union_find\
    \ {\npublic:\n  using size_type = size_t;\n  using time_type = size_t;\n\n  static\
    \ time_type far_future() {\n    return static_cast<time_type>(-1);\n  }\n\nprivate:\n\
    \  class node_type {\n  public:\n    size_type parent;\n    time_type updated;\n\
    \    std::vector<time_type> history;\n    std::vector<size_type> size;\n    node_type(size_type\
    \ parent):\n      parent(parent), updated(far_future()),\n      history(1, 0),\
    \ size(1, 1)\n    { }\n  };\n\n  std::vector<node_type> M_forest;\n  std::vector<size_type>\
    \ M_components;\n\npublic:\n  partially_persistent_union_find() = default;\n \
    \ explicit partially_persistent_union_find(const size_type size) { initialize(size);\
    \ }\n\n  void initialize(const size_type size) {\n    clear();\n    M_forest.reserve(size);\n\
    \    for (size_type index = 0; index < size; ++index) {\n      M_forest.emplace_back(index);\n\
    \    }\n    M_components.push_back(size);\n  }\n\n  size_type find_parent(const\
    \ size_type node, const time_type time) const {\n    assert(node < size());\n\
    \    if (M_forest[node].updated > time) return node;\n    return find_parent(M_forest[node].parent,\
    \ time);\n  }\n  size_type count_components(const time_type time) const {\n  \
    \  return M_components[std::min(now(), time)];\n  }\n  size_type component_size(size_type\
    \ node, time_type time) const {\n    assert(node < size());\n    time = std::min(time,\
    \ now());\n    node = find_parent(node, time);\n    const auto &history = M_forest[node].history;\n\
    \    auto index = std::lower_bound(history.cbegin(), history.cend(), time + 1)\
    \ - history.cbegin() - 1;\n    return M_forest[node].size[index];\n  }\n\n  time_type\
    \ when(const size_type node1, const size_type node2) const {\n    assert(node1\
    \ < size());\n    assert(node2 < size());\n    if (!same_component(node1, node2,\
    \ now())) return far_future();\n    time_type ok = now(), ng = 0, md;\n    while\
    \ (ok - ng > 1) {\n      md = (ok + ng) / 2;\n      (same_component(node1, node2,\
    \ md) ? ok : ng) = md;\n    }\n    return ok;\n  }\n\n  bool same_component(const\
    \ size_type node1, const size_type node2, const time_type time) const {\n    assert(node1\
    \ < size());\n    assert(node2 < size());\n    return find_parent(node1, time)\
    \ == find_parent(node2, time);\n  }\n  bool unite(size_type node1, size_type node2)\
    \ {\n    assert(node1 < size());\n    assert(node2 < size());\n    node1 = find_parent(node1,\
    \ now());\n    node2 = find_parent(node2, now());\n    size_type current = M_components.back();\n\
    \    if (node1 == node2) {\n      M_components.push_back(current);\n      return\
    \ false;\n    }\n    M_components.push_back(current - 1);\n    const size_type\
    \ size1 = M_forest[node1].size.back();\n    const size_type size2 = M_forest[node2].size.back();\n\
    \    if (size1 < size2) std::swap(node1, node2);\n    M_forest[node1].history.push_back(now());\n\
    \    M_forest[node1].size.push_back(size1 + size2);\n    M_forest[node2].parent\
    \ = node1;\n    M_forest[node2].updated = now();\n    return true;\n  }\n\n  time_type\
    \ now() const {\n    return M_components.size() - 1;\n  }\n  size_type size()\
    \ const {\n    return M_forest.size();\n  }\n  bool empty() const {\n    return\
    \ M_forest.empty();\n  }\n  void clear() {\n    M_forest.clear();\n    M_forest.shrink_to_fit();\n\
    \    M_components.clear();\n    M_components.shrink_to_fit();\n  }\n};\n\n/**\n\
    \ * @title Partially Persistent Union Find\n */"
  dependsOn: []
  isVerificationFile: false
  path: graph/partially_persistent_union_find.cpp
  requiredBy: []
  timestamp: '2020-09-09 18:08:09+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/partially_persistent_union_find.cpp
layout: document
redirect_from:
- /library/graph/partially_persistent_union_find.cpp
- /library/graph/partially_persistent_union_find.cpp.html
title: Partially Persistent Union Find
---
