---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes: {}
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 70, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: ../algebraic/modular_operation.cpp:\
    \ line -1: no such header\n"
  code: "\n#define PROBLEM \"https://judge.yosupo.jp/problem/discrete_logarithm_mod\"\
    \n\n#include \"../algebraic/modular.cpp\"\n#include \"../algebraic/modular_operation.cpp\"\
    \n\n#include <cstddef>\n#include <cstdint>\n#include <iostream>\n\nint main()\
    \ {\n  size_t Q;\n  std::cin >> Q;\n  while (Q--) {\n    uint32_t x, y;\n    std::cin\
    \ >> x >> y >> runtime_mod::value();\n    const auto ans = log(rmint32_t(x), rmint32_t(y));\n\
    \    if (ans == runtime_mod::value()) {\n      std::cout << \"-1\\n\";\n    }\n\
    \    else {\n      std::cout << ans << '\\n';\n    }\n  }\n  return 0;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: test/discrete_log.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: test/discrete_log.cpp
layout: document
redirect_from:
- /library/test/discrete_log.cpp
- /library/test/discrete_log.cpp.html
title: test/discrete_log.cpp
---
