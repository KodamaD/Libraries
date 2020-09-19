---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: implementing/trie.cpp
    title: implementing/trie.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"implementing/aho_corasick.cpp\"\n\n#line 2 \"implementing/trie.cpp\"\
    \n\n#include <cstddef>\n#include <vector>\n#include <iterator>\n#include <map>\n\
    #include <array>\n\ntemplate <class Node>\nclass trie_impl {\npublic:\n  using\
    \ size_type = size_t;\n  using value_type = typename Node::value_type;\n\nprotected:\n\
    \  using node_type = Node;\n\n  std::vector<node_type> M_tree;\n\n  size_type\
    \ M_add_node() {\n    const auto res = M_tree.size();\n    M_tree.emplace_back();\n\
    \    return res;\n  }\n\npublic:\n  explicit trie_impl() { M_add_node(); }\n\n\
    \  template <class InputIterator>\n  std::vector<size_type> insert(InputIterator\
    \ first, InputIterator last) {\n    std::vector<size_type> res;\n    res.reserve(std::distance(first,\
    \ last) + 1);\n    res.push_back(0);\n    size_type cur = 0;\n    for (; first\
    \ != last; ++first) {\n      const auto &c = *first;\n      if (~next(cur, c)\
    \ == 0) {\n        const auto new_node = M_add_node();\n        M_tree[cur].emplace(c,\
    \ new_node);\n      }\n      cur = next(cur, c);\n      res.push_back(cur);\n\
    \    }\n    return res;\n  }\n\n  template <class InputIterator>\n  std::vector<size_type>\
    \ find_path(InputIterator first, InputIterator last) const {\n    const size_type\
    \ size = std::distance(first, last) + 1;\n    std::vector<size_type> res;\n  \
    \  res.reserve(size);\n    res.push_back(0);\n    size_type cur = 0;\n    for\
    \ (; first != last; ++first) {\n      cur = next(cur, *first);\n      if (~cur\
    \ == 0) {\n        break;\n      }\n      res.push_back(cur);\n    }\n    res.resize(size,\
    \ size_type(-1));\n    return res;\n  }\n\n  size_type next(const size_type index,\
    \ const value_type &value) const {\n    return M_tree[index].next(value);\n  }\n\
    \  size_type size() const {\n    return M_tree.size();\n  }\n\n};\n\ntemplate\
    \ <class T>\nclass map_based_trie_node {\npublic:\n  using value_type = T;\nprivate:\n\
    \  std::map<value_type, size_t> M_children;\npublic:\n  explicit map_based_trie_node():\
    \ M_children() { }\n  size_t next(const value_type &value) const {\n    const\
    \ auto itr = M_children.find(value);\n    return (itr == M_children.end() ? size_t(-1)\
    \ : itr -> second);\n  }\n  void emplace(const value_type &value, const size_t\
    \ index) {\n    M_children.emplace(value, index);\n  }\n};\n\ntemplate <class\
    \ T, T MinValue, size_t Size>\nclass array_based_trie_node {\npublic:\n  using\
    \ value_type = T;\nprivate:\n  std::array<size_t, Size> M_children;\npublic:\n\
    \  explicit array_based_trie_node() { M_children.fill(size_t(-1)); }\n  size_t\
    \ next(const value_type &value) const {\n    return M_children[value - MinValue];\n\
    \  }\n  void emplace(const value_type &value, const size_t index) {\n    M_children[value\
    \ - MinValue] = index;\n  }\n};\n\ntemplate <class T>\nusing trie_any = trie_impl<map_based_trie_node<T>>;\n\
    \ntemplate <class T, T MinValue, size_t Size>\nusing trie_alphabet = trie_impl<array_based_trie_node<T,\
    \ MinValue, Size>>;\n#line 4 \"implementing/aho_corasick.cpp\"\n\ntemplate <class\
    \ Trie>\nclass aho_corasick_impl: public Trie {\npublic:\n  using value_type =\
    \ typename Trie::value_type;\n  using size_type = typename Trie::size_type;\n\n\
    private:\n  std::vector<size_type> link;\n\npublic:\n\n  void construct() {\n\
    \    \n  }\n\n};\n\ntemplate <class T>\nusing aho_corasick_any = aho_corasick_impl<trie_any<T>>;\n\
    \ntemplate <class T, T MinValue, size_t Size>\nusing aho_corasick_alphabet = aho_corasick_impl<trie_alphabet<T,\
    \ MinValue, Size>>;\n\n#include <iostream>\n\nint main() {\n  aho_corasick_any<char>\
    \ a;\n  std::cout << a.size() << '\\n';\n}\n"
  code: "#pragma once\n\n#include \"trie.cpp\"\n\ntemplate <class Trie>\nclass aho_corasick_impl:\
    \ public Trie {\npublic:\n  using value_type = typename Trie::value_type;\n  using\
    \ size_type = typename Trie::size_type;\n\nprivate:\n  std::vector<size_type>\
    \ link;\n\npublic:\n\n  void construct() {\n    \n  }\n\n};\n\ntemplate <class\
    \ T>\nusing aho_corasick_any = aho_corasick_impl<trie_any<T>>;\n\ntemplate <class\
    \ T, T MinValue, size_t Size>\nusing aho_corasick_alphabet = aho_corasick_impl<trie_alphabet<T,\
    \ MinValue, Size>>;\n\n#include <iostream>\n\nint main() {\n  aho_corasick_any<char>\
    \ a;\n  std::cout << a.size() << '\\n';\n}\n"
  dependsOn:
  - implementing/trie.cpp
  isVerificationFile: false
  path: implementing/aho_corasick.cpp
  requiredBy: []
  timestamp: '2020-09-09 18:08:09+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: implementing/aho_corasick.cpp
layout: document
redirect_from:
- /library/implementing/aho_corasick.cpp
- /library/implementing/aho_corasick.cpp.html
title: implementing/aho_corasick.cpp
---
