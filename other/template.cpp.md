---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Template
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.6/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.6/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.8.6/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.8.6/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: /Users/kodamankod/Desktop/cpp_programming/Library/other/chmin_chmax.cpp:\
    \ line -1: no such header\n"
  code: "\n/**\n * @title Template\n */\n\n#include <iostream>\n#include <algorithm>\n\
    #include <utility>\n#include <numeric>\n#include <vector>\n#include <array>\n\
    #include <cassert>\n\n#include \"/Users/kodamankod/Desktop/cpp_programming/Library/other/chmin_chmax.cpp\"\
    \n#include \"/Users/kodamankod/Desktop/cpp_programming/Library/other/range.cpp\"\
    \n\nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    \nconstexpr i32 inf32 = (i32(1) << 30) - 1;\nconstexpr i64 inf64 = (i64(1) <<\
    \ 62) - 1;\n\nint main() {\n  \n  return 0;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: other/template.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other/template.cpp
layout: document
redirect_from:
- /library/other/template.cpp
- /library/other/template.cpp.html
title: Template
---
