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
  code: "\n#define PROBLEM \"https://judge.yosupo.jp/problem/sqrt_mod\"\n\n#include\
    \ \"../algebraic/modular.cpp\"\n#include \"../algebraic/modular_operation.cpp\"\
    \n\n#include <cstddef>\n#include <cstdint>\n#include <iostream>\n\nint main()\
    \ {\n  size_t Q;\n  std::cin >> Q;\n  while (Q--) {\n    uint32_t x;\n    std::cin\
    \ >> x >> runtime_mod::value();\n    if (x == 0) std::cout << \"0\\n\";\n    else\
    \ {\n      const auto ans = sqrt(rmint32_t(x));\n      if (ans.zero()) std::cout\
    \ << \"-1\\n\";\n      else std::cout << ans << '\\n';\n    }\n  }\n  return 0;\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: test/sqrt_mod.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: test/sqrt_mod.cpp
layout: document
redirect_from:
- /library/test/sqrt_mod.cpp
- /library/test/sqrt_mod.cpp.html
title: test/sqrt_mod.cpp
---
