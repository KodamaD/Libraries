---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: geometry/figures.cpp
    title: 2D Figures
  - icon: ':warning:'
    path: geometry/polygon.cpp
    title: 2D Polygons
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Geometric Constants
    links: []
  bundledCode: "#line 2 \"geometry/constants.cpp\"\n\n#include <cmath>\n\ntemplate\
    \ <class T>\nstruct real_constant;\n\ntemplate <>\nstruct real_constant<double>\
    \ {\n  using value_type = double;\n  static constexpr value_type infinity() {\
    \ return 1e9; }\n  static constexpr value_type epsilon() { return 1e-9; }\n  static\
    \ constexpr value_type pi() { return std::acos(-1.0); }\n};\n\ntemplate <>\nstruct\
    \ real_constant<long double> {\n  using value_type = long double;\n  static constexpr\
    \ value_type infinity() { return 1e18; }\n  static constexpr value_type epsilon()\
    \ { return 1e-10; }\n  static constexpr value_type pi() { return std::acos(-1.0L);\
    \ }\n};\n\ntemplate <>\nstruct real_constant<__float128> {\n  using value_type\
    \ = __float128;\n  static constexpr value_type infinity() { return 1e18; }\n \
    \ static constexpr value_type epsilon() { return 1e-10; }\n  static constexpr\
    \ value_type pi() { return std::acos(-1.0L); }\n};\n\ntemplate <>\nstruct real_constant<int32_t>\
    \ {\n  using value_type = int32_t;\n  static constexpr value_type infinity() {\
    \ return 1e9; }\n  static constexpr value_type epsilon() { return 1; }\n};\n\n\
    template <>\nstruct real_constant<int64_t> {\n  using value_type = int64_t;\n\
    \  static constexpr value_type infinity() { return 1e18; }\n  static constexpr\
    \ value_type epsilon() { return 1; }\n};\n\ntemplate <class T, class U>\nbool\
    \ leq(T x, U y) {\n  return x - y < real_constant<T>::epsilon();\n}\ntemplate\
    \ <class T, class U>\nbool geq(T x, U y) {\n  return y - x < real_constant<T>::epsilon();\n\
    }\ntemplate <class T, class U>\nbool equal(T x, U y) {\n  return leq(x, y) &&\
    \ geq(x, y);\n}\n\ntemplate <class T>\nT to_radian(T deg) {\n  return deg * real_constant<T>::pi()\
    \ / 180;\n}\ntemplate <class T>\nT to_degree(T rad) {\n  return rad / real_constant<T>::pi()\
    \ * 180;\n}\n\n/**\n * @title Geometric Constants\n */\n"
  code: "#pragma once\n\n#include <cmath>\n\ntemplate <class T>\nstruct real_constant;\n\
    \ntemplate <>\nstruct real_constant<double> {\n  using value_type = double;\n\
    \  static constexpr value_type infinity() { return 1e9; }\n  static constexpr\
    \ value_type epsilon() { return 1e-9; }\n  static constexpr value_type pi() {\
    \ return std::acos(-1.0); }\n};\n\ntemplate <>\nstruct real_constant<long double>\
    \ {\n  using value_type = long double;\n  static constexpr value_type infinity()\
    \ { return 1e18; }\n  static constexpr value_type epsilon() { return 1e-10; }\n\
    \  static constexpr value_type pi() { return std::acos(-1.0L); }\n};\n\ntemplate\
    \ <>\nstruct real_constant<__float128> {\n  using value_type = __float128;\n \
    \ static constexpr value_type infinity() { return 1e18; }\n  static constexpr\
    \ value_type epsilon() { return 1e-10; }\n  static constexpr value_type pi() {\
    \ return std::acos(-1.0L); }\n};\n\ntemplate <>\nstruct real_constant<int32_t>\
    \ {\n  using value_type = int32_t;\n  static constexpr value_type infinity() {\
    \ return 1e9; }\n  static constexpr value_type epsilon() { return 1; }\n};\n\n\
    template <>\nstruct real_constant<int64_t> {\n  using value_type = int64_t;\n\
    \  static constexpr value_type infinity() { return 1e18; }\n  static constexpr\
    \ value_type epsilon() { return 1; }\n};\n\ntemplate <class T, class U>\nbool\
    \ leq(T x, U y) {\n  return x - y < real_constant<T>::epsilon();\n}\ntemplate\
    \ <class T, class U>\nbool geq(T x, U y) {\n  return y - x < real_constant<T>::epsilon();\n\
    }\ntemplate <class T, class U>\nbool equal(T x, U y) {\n  return leq(x, y) &&\
    \ geq(x, y);\n}\n\ntemplate <class T>\nT to_radian(T deg) {\n  return deg * real_constant<T>::pi()\
    \ / 180;\n}\ntemplate <class T>\nT to_degree(T rad) {\n  return rad / real_constant<T>::pi()\
    \ * 180;\n}\n\n/**\n * @title Geometric Constants\n */"
  dependsOn: []
  isVerificationFile: false
  path: geometry/constants.cpp
  requiredBy:
  - geometry/figures.cpp
  - geometry/polygon.cpp
  timestamp: '2020-07-11 19:42:18+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: geometry/constants.cpp
layout: document
redirect_from:
- /library/geometry/constants.cpp
- /library/geometry/constants.cpp.html
title: Geometric Constants
---
