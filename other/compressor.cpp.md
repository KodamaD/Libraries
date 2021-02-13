---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Compressor
    links: []
  bundledCode: "#line 2 \"other/compressor.cpp\"\n\n#include <vector>\n#include <cstddef>\n\
    #include <cassert>\n#include <algorithm>\n\ntemplate <class T>\nclass compressor\
    \ {\n  std::vector<T> data;\n  bool compressed;\n\npublic:\n  compressor(const\
    \ std::size_t capacity = 0) {\n    data.reserve(capacity);\n    compressed = false;\n\
    \  }\n\n  void add(const T &value) {\n    assert(!compressed);\n    data.push_back(value);\n\
    \  }\n\n  void build() {\n    assert(!compressed);\n    std::sort(data.begin(),\
    \ data.end());\n    data.erase(std::unique(data.begin(), data.end()), data.end());\n\
    \    compressed = true;\n  }\n\n  std::size_t get(const T &value) const {\n  \
    \  assert(compressed);\n    return std::lower_bound(data.cbegin(), data.cend(),\
    \ value) - data.cbegin();\n  }\n\n  std::size_t size() const {\n    assert(compressed);\n\
    \    return data.size();\n  }\n\n  T restore(const std::size_t index) const {\n\
    \    assert(compressed);\n    return data[index];\n  }\n};\n\n/**\n * @title Compressor\n\
    \ */\n"
  code: "#pragma once\n\n#include <vector>\n#include <cstddef>\n#include <cassert>\n\
    #include <algorithm>\n\ntemplate <class T>\nclass compressor {\n  std::vector<T>\
    \ data;\n  bool compressed;\n\npublic:\n  compressor(const std::size_t capacity\
    \ = 0) {\n    data.reserve(capacity);\n    compressed = false;\n  }\n\n  void\
    \ add(const T &value) {\n    assert(!compressed);\n    data.push_back(value);\n\
    \  }\n\n  void build() {\n    assert(!compressed);\n    std::sort(data.begin(),\
    \ data.end());\n    data.erase(std::unique(data.begin(), data.end()), data.end());\n\
    \    compressed = true;\n  }\n\n  std::size_t get(const T &value) const {\n  \
    \  assert(compressed);\n    return std::lower_bound(data.cbegin(), data.cend(),\
    \ value) - data.cbegin();\n  }\n\n  std::size_t size() const {\n    assert(compressed);\n\
    \    return data.size();\n  }\n\n  T restore(const std::size_t index) const {\n\
    \    assert(compressed);\n    return data[index];\n  }\n};\n\n/**\n * @title Compressor\n\
    \ */"
  dependsOn: []
  isVerificationFile: false
  path: other/compressor.cpp
  requiredBy: []
  timestamp: '2021-02-13 19:27:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other/compressor.cpp
layout: document
redirect_from:
- /library/other/compressor.cpp
- /library/other/compressor.cpp.html
title: Compressor
---
