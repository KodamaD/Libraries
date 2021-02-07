---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/z_algorithm.cpp
    title: Z-Algorithm
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/zalgorithm
    links:
    - https://judge.yosupo.jp/problem/zalgorithm
  bundledCode: "#line 1 \"test/z_algorithm.test.cpp\"\n\n#define PROBLEM \"https://judge.yosupo.jp/problem/zalgorithm\"\
    \n\n#line 2 \"string/z_algorithm.cpp\"\n\n#include <cstddef>\n#include <vector>\n\
    \ntemplate <class InputIterator>\nstd::vector<size_t> z_algorithm(InputIterator\
    \ first, InputIterator last) {\n  const std::vector<typename InputIterator::value_type>\
    \ str(first, last);\n  const size_t size = str.size();\n  std::vector<size_t>\
    \ result(size);\n  result[0] = size;\n  size_t i = 1, j = 0;\n  while (i < size)\
    \ {\n    while (i + j < size && str[i + j] == str[j]) {\n      ++j;\n    }\n \
    \   result[i] = j;\n    if (j == 0) { \n      ++i; \n      continue; \n    }\n\
    \    size_t k = 1;\n    while (i + k < size && k + result[k] < j) { \n      result[i\
    \ + k] = result[k];\n      ++k; \n    }\n    i += k;\n    j -= k;\n  }\n  return\
    \ result;\n}\n\n/**\n * @title Z-Algorithm\n */\n#line 5 \"test/z_algorithm.test.cpp\"\
    \n\n#line 8 \"test/z_algorithm.test.cpp\"\n#include <string>\n#include <iostream>\n\
    \nint main() {\n  std::string S;\n  std::cin >> S;\n  auto ans = z_algorithm(S.begin(),\
    \ S.end());\n  for (size_t i = 0; i < S.size(); ++i) {\n    std::cout << ans[i];\n\
    \    std::cout << (i + 1 == S.size() ? '\\n' : ' ');\n  }\n  return 0;\n}\n"
  code: "\n#define PROBLEM \"https://judge.yosupo.jp/problem/zalgorithm\"\n\n#include\
    \ \"../string/z_algorithm.cpp\"\n\n#include <cstddef>\n#include <vector>\n#include\
    \ <string>\n#include <iostream>\n\nint main() {\n  std::string S;\n  std::cin\
    \ >> S;\n  auto ans = z_algorithm(S.begin(), S.end());\n  for (size_t i = 0; i\
    \ < S.size(); ++i) {\n    std::cout << ans[i];\n    std::cout << (i + 1 == S.size()\
    \ ? '\\n' : ' ');\n  }\n  return 0;\n}"
  dependsOn:
  - string/z_algorithm.cpp
  isVerificationFile: true
  path: test/z_algorithm.test.cpp
  requiredBy: []
  timestamp: '2020-08-14 11:56:16+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/z_algorithm.test.cpp
layout: document
redirect_from:
- /verify/test/z_algorithm.test.cpp
- /verify/test/z_algorithm.test.cpp.html
title: test/z_algorithm.test.cpp
---
