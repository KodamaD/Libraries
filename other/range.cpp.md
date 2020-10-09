---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Range
    links: []
  bundledCode: "#line 2 \"other/range.cpp\"\n\n#include <algorithm>\n\nclass range\
    \ {\npublic:\n  class iterator {\n  private:\n    int64_t M_position;\n\n  public:\n\
    \    constexpr iterator(int64_t position) noexcept: M_position(position) { }\n\
    \    constexpr void operator ++ () noexcept { ++M_position; }\n    constexpr bool\
    \ operator != (iterator other) const noexcept { return M_position != other.M_position;\
    \ }\n    constexpr int64_t operator * () const noexcept { return M_position; }\n\
    \  };\n\n  class reverse_iterator {\n  private:\n    int64_t M_position;\n  \n\
    \  public:\n    constexpr reverse_iterator(int64_t position) noexcept: M_position(position)\
    \ { }\n    constexpr void operator ++ () noexcept { --M_position; }\n    constexpr\
    \ bool operator != (reverse_iterator other) const noexcept { return M_position\
    \ != other.M_position; }\n    constexpr int64_t operator * () const noexcept {\
    \ return M_position; }\n  };\n  \nprivate:\n  const iterator M_first, M_last;\n\
    \npublic:\n  constexpr range(int64_t first, int64_t last) noexcept: M_first(first),\
    \ M_last(std::max(first, last)) { }\n  constexpr iterator begin() const noexcept\
    \ { return M_first; }\n  constexpr iterator end() const noexcept { return M_last;\
    \ }\n  constexpr reverse_iterator rbegin() const noexcept { return reverse_iterator(*M_last\
    \ - 1); } \n  constexpr reverse_iterator rend() const noexcept { return reverse_iterator(*M_first\
    \ - 1); } \n};\n\n/**\n * @title Range\n */\n"
  code: "#pragma once\n\n#include <algorithm>\n\nclass range {\npublic:\n  class iterator\
    \ {\n  private:\n    int64_t M_position;\n\n  public:\n    constexpr iterator(int64_t\
    \ position) noexcept: M_position(position) { }\n    constexpr void operator ++\
    \ () noexcept { ++M_position; }\n    constexpr bool operator != (iterator other)\
    \ const noexcept { return M_position != other.M_position; }\n    constexpr int64_t\
    \ operator * () const noexcept { return M_position; }\n  };\n\n  class reverse_iterator\
    \ {\n  private:\n    int64_t M_position;\n  \n  public:\n    constexpr reverse_iterator(int64_t\
    \ position) noexcept: M_position(position) { }\n    constexpr void operator ++\
    \ () noexcept { --M_position; }\n    constexpr bool operator != (reverse_iterator\
    \ other) const noexcept { return M_position != other.M_position; }\n    constexpr\
    \ int64_t operator * () const noexcept { return M_position; }\n  };\n  \nprivate:\n\
    \  const iterator M_first, M_last;\n\npublic:\n  constexpr range(int64_t first,\
    \ int64_t last) noexcept: M_first(first), M_last(std::max(first, last)) { }\n\
    \  constexpr iterator begin() const noexcept { return M_first; }\n  constexpr\
    \ iterator end() const noexcept { return M_last; }\n  constexpr reverse_iterator\
    \ rbegin() const noexcept { return reverse_iterator(*M_last - 1); } \n  constexpr\
    \ reverse_iterator rend() const noexcept { return reverse_iterator(*M_first -\
    \ 1); } \n};\n\n/**\n * @title Range\n */"
  dependsOn: []
  isVerificationFile: false
  path: other/range.cpp
  requiredBy: []
  timestamp: '2020-09-13 16:51:07+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other/range.cpp
layout: document
redirect_from:
- /library/other/range.cpp
- /library/other/range.cpp.html
title: Range
---
