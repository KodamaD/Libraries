---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    document_title: Network Simplex
    links: []
  bundledCode: "#line 2 \"implementing/network_simplex.cpp\"\n\n#include <cstddef>\n\
    #include <cstdint>\n\ntemplate <class Flow, class Cost>\nclass network_simplex\
    \ {\npublic:\n  using flow_type = Flow;\n  using cost_type = Cost;\n  using size_type\
    \ = size_t;\n\n  class edge_type {\n  public:\n    const size_type src;\n    const\
    \ size_type dest;\n    flow_type flow;\n    const flow_type capacity;\n    const\
    \ cost_type cost;\n\n    explicit edge_type(const size_type src, const size_type\
    \ dest,\n      const flow_type flow, const flow_type capacity, const cost_type\
    \ cost):\n      src(src), dest(dest), flow(flow), capacity(capacity), cost(cost)\
    \ { }\n  };\n\nprivate:\n  std::vector<edge_type> edges;\n  \npublic:\n\n\n\n\
    };\n\n/**\n * @title Network Simplex\n */\n"
  code: "#pragma once\n\n#include <cstddef>\n#include <cstdint>\n\ntemplate <class\
    \ Flow, class Cost>\nclass network_simplex {\npublic:\n  using flow_type = Flow;\n\
    \  using cost_type = Cost;\n  using size_type = size_t;\n\n  class edge_type {\n\
    \  public:\n    const size_type src;\n    const size_type dest;\n    flow_type\
    \ flow;\n    const flow_type capacity;\n    const cost_type cost;\n\n    explicit\
    \ edge_type(const size_type src, const size_type dest,\n      const flow_type\
    \ flow, const flow_type capacity, const cost_type cost):\n      src(src), dest(dest),\
    \ flow(flow), capacity(capacity), cost(cost) { }\n  };\n\nprivate:\n  std::vector<edge_type>\
    \ edges;\n  \npublic:\n\n\n\n};\n\n/**\n * @title Network Simplex\n */"
  dependsOn: []
  isVerificationFile: false
  path: implementing/network_simplex.cpp
  requiredBy: []
  timestamp: '2020-09-19 12:22:26+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: implementing/network_simplex.cpp
layout: document
redirect_from:
- /library/implementing/network_simplex.cpp
- /library/implementing/network_simplex.cpp.html
title: Network Simplex
---
