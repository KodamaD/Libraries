---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Time Measurement
    links: []
  bundledCode: "#line 2 \"other/time_measurement.cpp\"\n\n#include <chrono>\n#include\
    \ <cstdint>\n#include <iostream>\n\nclass measure {\npublic:\n  using time_point\
    \ = decltype(std::chrono::system_clock::now());\n\nprivate:\n  const time_point\
    \ M_start;\n\n  static time_point S_current_time() {\n    return std::chrono::system_clock::now();\n\
    \  }\n\npublic:\n  explicit measure(): M_start(S_current_time()) { }\n\n  template\
    \ <class Duration = std::chrono::milliseconds>\n  uint64_t get() const {\n   \
    \ return std::chrono::duration_cast<Duration>(S_current_time() - M_start).count();\n\
    \  }\n\n  void print_ms() const {\n    std::cerr << \"current time: \" << get<std::chrono::milliseconds>()\
    \ << \"ms\" << std::endl;\n  }\n\n};\n\n/**\n * @title Time Measurement\n */\n"
  code: "#pragma once\n\n#include <chrono>\n#include <cstdint>\n#include <iostream>\n\
    \nclass measure {\npublic:\n  using time_point = decltype(std::chrono::system_clock::now());\n\
    \nprivate:\n  const time_point M_start;\n\n  static time_point S_current_time()\
    \ {\n    return std::chrono::system_clock::now();\n  }\n\npublic:\n  explicit\
    \ measure(): M_start(S_current_time()) { }\n\n  template <class Duration = std::chrono::milliseconds>\n\
    \  uint64_t get() const {\n    return std::chrono::duration_cast<Duration>(S_current_time()\
    \ - M_start).count();\n  }\n\n  void print_ms() const {\n    std::cerr << \"current\
    \ time: \" << get<std::chrono::milliseconds>() << \"ms\" << std::endl;\n  }\n\n\
    };\n\n/**\n * @title Time Measurement\n */"
  dependsOn: []
  isVerificationFile: false
  path: other/time_measurement.cpp
  requiredBy: []
  timestamp: '2020-08-05 18:30:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other/time_measurement.cpp
layout: document
redirect_from:
- /library/other/time_measurement.cpp
- /library/other/time_measurement.cpp.html
title: Time Measurement
---
