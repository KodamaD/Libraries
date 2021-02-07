---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/suffix_array.cpp
    title: Suffix Array
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/suffixarray
    links:
    - https://judge.yosupo.jp/problem/suffixarray
  bundledCode: "#line 1 \"test/suffix_array.test.cpp\"\n\n#define PROBLEM \"https://judge.yosupo.jp/problem/suffixarray\"\
    \n\n#line 2 \"string/suffix_array.cpp\"\n\n#include <cstddef>\n#include <vector>\n\
    #include <numeric>\n#include <algorithm>\n\ntemplate <class T>\nclass suffix_array\
    \ {\npublic:\n  using value_type = T;\n  using size_type  = size_t;\n\nprivate:\n\
    \  std::vector<value_type> M_data;\n  std::vector<size_type> M_array, M_rank;\n\
    \npublic:\n  suffix_array() = default;\n  template <class InputIterator>\n  explicit\
    \ suffix_array(InputIterator first, InputIterator last) { construct(first, last);\
    \ } \n\n  template <class InputIterator>\n  void construct(InputIterator first,\
    \ InputIterator last) { \n    clear();\n    M_data = std::vector<typename InputIterator::value_type>(first,\
    \ last);\n    M_array.assign(size() + 1, 0);\n    M_rank.assign(size() + 1, 0);\n\
    \    M_array.front() = size();\n    std::iota(M_array.begin() + 1, M_array.end(),\
    \ 0);\n    std::stable_sort(M_array.begin() + 1, M_array.end(), [&](size_type\
    \ i, size_type j) {\n      return M_data[i] < M_data[j];\n    });\n    M_rank[M_array[0]]\
    \ = 1;\n    for (size_type i = 1; i <= size(); ++i) {\n      if (i > 1 && M_data[M_array[i]]\
    \ == M_data[M_array[i - 1]]) M_rank[M_array[i]] = M_rank[M_array[i - 1]];\n  \
    \    else M_rank[M_array[i]] = M_rank[M_array[i - 1]] + 1;\n    }\n    size_type\
    \ length;\n    auto compare = [&](size_type i, size_type j) {\n      if (M_rank[i]\
    \ != M_rank[j]) return M_rank[i] < M_rank[j];\n      size_type ti = (i + length\
    \ <= size() ? M_rank[i + length] : 0);\n      size_type tj = (j + length <= size()\
    \ ? M_rank[j + length] : 0);\n      return ti < tj;\n    };\n    std::vector<size_type>\
    \ copy(size() + 1);\n    for (length = 1; length < size(); length <<= 1) {\n \
    \     std::stable_sort(M_array.begin(), M_array.end(), compare);\n      copy[M_array[0]]\
    \ = 1;\n      for (size_type i = 1; i <= size(); ++i) {\n        copy[M_array[i]]\
    \ = copy[M_array[i - 1]] + (compare(M_array[i - 1], M_array[i]) ? 1 : 0);\n  \
    \    }\n      std::copy(copy.begin(), copy.end(), M_rank.begin());\n    }\n  }\n\
    \n  size_type operator [](size_type i) const {\n    return M_array[i];\n  }\n\
    \  size_type rank(size_type i) const {\n    return M_rank[i];\n  }\n\n  std::vector<value_type>\
    \ &get() const {\n    return M_data;\n  }\n  size_type size() const {\n    return\
    \ M_data.size();\n  }\n  void clear() {\n    M_data.clear();\n    M_data.shrink_to_fit();\n\
    \    M_array.clear();\n    M_array.shrink_to_fit();\n    M_rank.clear();\n   \
    \ M_rank.shrink_to_fit();\n  }\n\n};\n\n/**\n * @title Suffix Array\n */\n#line\
    \ 5 \"test/suffix_array.test.cpp\"\n\n#line 7 \"test/suffix_array.test.cpp\"\n\
    #include <iostream>\n#include <string>\n\nint main() {  \n  std::string S;\n \
    \ std::cin >> S;\n  suffix_array<char> ans(S.begin(), S.end());\n  for (size_t\
    \ i = 1; i <= S.size(); ++i) {\n    std::cout << ans[i] << \" \\n\"[i == S.size()];\n\
    \  }\n  return 0;\n}\n"
  code: "\n#define PROBLEM \"https://judge.yosupo.jp/problem/suffixarray\"\n\n#include\
    \ \"../string/suffix_array.cpp\"\n\n#include <cstddef>\n#include <iostream>\n\
    #include <string>\n\nint main() {  \n  std::string S;\n  std::cin >> S;\n  suffix_array<char>\
    \ ans(S.begin(), S.end());\n  for (size_t i = 1; i <= S.size(); ++i) {\n    std::cout\
    \ << ans[i] << \" \\n\"[i == S.size()];\n  }\n  return 0;\n}\n"
  dependsOn:
  - string/suffix_array.cpp
  isVerificationFile: true
  path: test/suffix_array.test.cpp
  requiredBy: []
  timestamp: '2020-07-11 19:42:18+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/suffix_array.test.cpp
layout: document
redirect_from:
- /verify/test/suffix_array.test.cpp
- /verify/test/suffix_array.test.cpp.html
title: test/suffix_array.test.cpp
---
