---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Range
    links: []
  bundledCode: "#line 2 \"other/range.cpp\"\n\n#include <algorithm>\n\nclass range\
    \ {\n  struct iter {\n    std::size_t itr;\n    constexpr iter(std::size_t pos)\
    \ noexcept: itr(pos) { }\n    constexpr void operator ++ () noexcept { ++itr;\
    \ }\n    constexpr bool operator != (iter other) const noexcept { return itr !=\
    \ other.itr; }\n    constexpr std::size_t operator * () const noexcept { return\
    \ itr; }\n  };\n\n  struct reviter {\n    std::size_t itr;\n    constexpr reviter(std::size_t\
    \ pos) noexcept: itr(pos) { }\n    constexpr void operator ++ () noexcept { --itr;\
    \ }\n    constexpr bool operator != (reviter other) const noexcept { return itr\
    \ != other.itr; }\n    constexpr std::size_t operator * () const noexcept { return\
    \ itr; }\n  };\n\n  const iter first, last;\n\npublic:\n  constexpr range(std::size_t\
    \ first, std::size_t last) noexcept: first(first), last(std::max(first, last))\
    \ { }\n  constexpr iter begin() const noexcept { return first; }\n  constexpr\
    \ iter end() const noexcept { return last; }\n  constexpr reviter rbegin() const\
    \ noexcept { return reviter(*last - 1); } \n  constexpr reviter rend() const noexcept\
    \ { return reviter(*first - 1); } \n};\n\n/**\n * @title Range\n */\n"
  code: "#pragma once\n\n#include <algorithm>\n\nclass range {\n  struct iter {\n\
    \    std::size_t itr;\n    constexpr iter(std::size_t pos) noexcept: itr(pos)\
    \ { }\n    constexpr void operator ++ () noexcept { ++itr; }\n    constexpr bool\
    \ operator != (iter other) const noexcept { return itr != other.itr; }\n    constexpr\
    \ std::size_t operator * () const noexcept { return itr; }\n  };\n\n  struct reviter\
    \ {\n    std::size_t itr;\n    constexpr reviter(std::size_t pos) noexcept: itr(pos)\
    \ { }\n    constexpr void operator ++ () noexcept { --itr; }\n    constexpr bool\
    \ operator != (reviter other) const noexcept { return itr != other.itr; }\n  \
    \  constexpr std::size_t operator * () const noexcept { return itr; }\n  };\n\n\
    \  const iter first, last;\n\npublic:\n  constexpr range(std::size_t first, std::size_t\
    \ last) noexcept: first(first), last(std::max(first, last)) { }\n  constexpr iter\
    \ begin() const noexcept { return first; }\n  constexpr iter end() const noexcept\
    \ { return last; }\n  constexpr reviter rbegin() const noexcept { return reviter(*last\
    \ - 1); } \n  constexpr reviter rend() const noexcept { return reviter(*first\
    \ - 1); } \n};\n\n/**\n * @title Range\n */"
  dependsOn: []
  isVerificationFile: false
  path: other/range.cpp
  requiredBy: []
  timestamp: '2021-02-07 17:51:45+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other/range.cpp
layout: document
redirect_from:
- /library/other/range.cpp
- /library/other/range.cpp.html
title: Range
---
