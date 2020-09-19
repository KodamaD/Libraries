---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: geometry/figures.cpp
    title: 2D Figures
  - icon: ':warning:'
    path: geometry/constants.cpp
    title: Geometric Constants
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    document_title: 2D Polygons
    links: []
  bundledCode: "#line 2 \"geometry/polygon.cpp\"\n\n#line 2 \"geometry/figures.cpp\"\
    \n\n#line 2 \"geometry/constants.cpp\"\n\n#include <cmath>\n\ntemplate <class\
    \ T>\nstruct real_constant;\n\ntemplate <>\nstruct real_constant<double> {\n \
    \ using value_type = double;\n  static constexpr value_type infinity() { return\
    \ 1e9; }\n  static constexpr value_type epsilon() { return 1e-9; }\n  static constexpr\
    \ value_type pi() { return std::acos(-1.0); }\n};\n\ntemplate <>\nstruct real_constant<long\
    \ double> {\n  using value_type = long double;\n  static constexpr value_type\
    \ infinity() { return 1e18; }\n  static constexpr value_type epsilon() { return\
    \ 1e-10; }\n  static constexpr value_type pi() { return std::acos(-1.0L); }\n\
    };\n\ntemplate <>\nstruct real_constant<__float128> {\n  using value_type = __float128;\n\
    \  static constexpr value_type infinity() { return 1e18; }\n  static constexpr\
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
    \ * 180;\n}\n\n/**\n * @title Geometric Constants\n */\n#line 4 \"geometry/figures.cpp\"\
    \n\ntemplate <class T>\nstruct vector_type {\n  using value_type = T;\n  value_type\
    \ x, y;\n  vector_type(): x(0), y(0) { }\n  vector_type(value_type x_, value_type\
    \ y_): x(x_), y(y_) { }\n  vector_type &operator += (const vector_type &rhs) {\
    \ x += rhs.x; y += rhs.y; return *this; }\n  vector_type operator + (const vector_type\
    \ &rhs) const { return vector_type(*this) += rhs; }\n  vector_type &operator -=\
    \ (const vector_type &rhs) { x -= rhs.x; y -= rhs.y; return *this; }\n  vector_type\
    \ operator - (const vector_type &rhs) const { return vector_type(*this) -= rhs;\
    \ }\n  vector_type operator - () const { return vector_type(-x, -y); }\n  vector_type\
    \ &operator *= (value_type rhs) { x *= rhs; y *= rhs; return *this; }\n  vector_type\
    \ &operator /= (value_type rhs) { x /= rhs; y /= rhs; return *this; }\n  bool\
    \ operator == (const vector_type &rhs) const { return equal(x, rhs.x) && equal(y,\
    \ rhs.y); }\n  bool operator != (const vector_type &rhs) const { return !equal(x,\
    \ rhs.x) || !equal(y, rhs.y); }\n};\n\ntemplate <class T, class U>\nvector_type<T>\
    \ operator * (vector_type<T> v, U rhs) { return v *= rhs; }\ntemplate <class T,\
    \ class U>\nvector_type<T> operator * (U rhs, vector_type<T> v) { return v *=\
    \ rhs; }\ntemplate <class T, class U>\nvector_type<T> operator / (vector_type<T>\
    \ v, U rhs) { return v /= rhs; }\n\ntemplate <class T>\nstd::istream& operator\
    \ >> (std::istream& is, vector_type<T> &v) { return is >> v.x >> v.y; }\ntemplate\
    \ <class T>\nstd::ostream& operator << (std::ostream& os, const vector_type<T>\
    \ &v) { return os << v.x << ' ' <<  v.y; }\n\ntemplate <class T>\nT norm(const\
    \ vector_type<T> &v) { \n  return v.x * v.x + v.y * v.y; \n}\ntemplate <class\
    \ T>\nT absolute(const vector_type<T> &v) { \n  return std::sqrt(norm(v));\n}\n\
    template <class T>\nT argument(const vector_type<T> &v) {  \n  auto res = std::atan2(v.y,\
    \ v.x); \n  return res < 0 ? res + 2 * real_constant<T>::pi() : res;\n}\n\ntemplate\
    \ <class T>\nT distance(const vector_type<T> &v, const vector_type<T> &u) { \n\
    \  return absolute(v - u); \n}\ntemplate <class T>\nT dot(const vector_type<T>\
    \ &v, const vector_type<T> &u) { \n  return v.x * u.x + v.y * u.y; \n}\ntemplate\
    \ <class T>\nT cross(const vector_type<T> &v, const vector_type<T> &u) { \n  return\
    \ v.x * u.y - v.y * u.x; \n}\n\ntemplate <class T>\nsize_t orthan(const vector_type<T>\
    \ &v) {\n  if (v.x > 0 && v.y >= 0) return 0;\n  if (v.x <= 0 && v.y > 0) return\
    \ 1;\n  if (v.x < 0 && v.y <= 0) return 2;\n  if (v.x >= 0 && v.y < 0) return\
    \ 3;\n  return 0;\n}\n\ntemplate <class T>\nvector_type<T> polar(T rho, T theta\
    \ = T()) {\n  return rho * vector_type<T>(std::cos(theta), std::sin(theta));\n\
    }\n\ntemplate <class T>\nbool cmp_x(const vector_type<T> &v, const vector_type<T>\
    \ &u) {\n  if (equal(v.x, u.x)) return v.y < u.y;\n  return v.x < u.x;\n}\ntemplate\
    \ <class T>\nbool cmp_y(const vector_type<T> &v, const vector_type<T> &u) {\n\
    \  if (equal(v.y, u.y)) return v.x < u.x;\n  return v.y < u.y;\n}\ntemplate <class\
    \ T>\nbool cmp_arg(const vector_type<T> &v, const vector_type<T> &u) {\n  if (orthan(v)\
    \ != orthan(u)) return orthan(v) < orthan(u);\n  if (!equal(cross(v, u), 0)) return\
    \ cross(v, u) > 0;\n  return norm(v) < norm(u);\n}\n\ntemplate <class T>\nstruct\
    \ line_type {\n  using value_type = T;\n  value_type a, b, c;\n  line_type():\
    \ a(0), b(0), c(0) { }\n  line_type(value_type a_, value_type c_): a(a_), b(-1),\
    \ c(c_) { }\n  line_type(value_type a_, value_type b_, value_type c_): a(a_),\
    \ b(b_), c(c_) { }\n  value_type valx(value_type y) const { return (b * y + c)\
    \ / (-a); }\n  value_type valy(value_type x) const { return (a * x + c) / (-b);\
    \ }\n  bool operator == (const value_type &l) const { return equal(a * l.b, b\
    \ * l.a) && equal(a * l.c, c * l.a); }\n  bool operator != (const value_type &l)\
    \ const { return !equal(a * l.b, b * l.a) || !equal(a * l.c, c * l.a); }\n};\n\
    \ntemplate <class T>\nbool parallel(const line_type<T> &l, const line_type<T>\
    \ &m) { \n  return equal(l.a * m.b, l.b * m.a); \n}\ntemplate <class T>\nbool\
    \ vertical(const line_type<T> &l, const line_type<T> &m) { \n  return equal(l.a\
    \ * m.a + l.b * m.b, 0); \n}\ntemplate <class T>\nbool is_on(const line_type<T>\
    \ &l, const vector_type<T> &v) { \n  return equal(l.a * v.x + l.b * v.y + l.c,\
    \ 0);\n}\n\ntemplate <class T>\nvector_type<T> intersection(const line_type<T>\
    \ &l, const line_type<T> &m) {\n  auto x = (l.b * m.c - l.c * m.b) / (l.a * m.b\
    \ - l.b * m.a);\n  auto y = (l.c * m.a - l.a * m.c) / (l.a * m.b - l.b * m.a);\n\
    \  return vector_type<T>(x, y);\n}\ntemplate <class T>\nvector_type<T> direction(const\
    \ line_type<T> &l) { \n  return vector_type<T>(-l.b, l.a); \n}\ntemplate <class\
    \ T>\nvector_type<T> perpend(const line_type<T> &l, const vector_type<T> &v) {\n\
    \  auto u = vector_type<T>(l.a, l.b);\n  auto d = -l.c / norm(u);\n  auto e =\
    \ dot(v, u) / norm(u);\n  return (d - e) * u;\n}\ntemplate <class T>\nvector_type<T>\
    \ project(const line_type<T> &l, const vector_type<T> &v) {\n  return v + perpend(l,\
    \ v);\n}\ntemplate <class T>\nvector_type<T> relfect(const line_type<T> &l, const\
    \ vector_type<T> &v) {\n  return v + perpend(l, v) * 2;\n}\n\ntemplate <class\
    \ T>\nT distance(const line_type<T> &l, const vector_type<T> &v) { \n  return\
    \ std::abs(l.a * v.x + l.b * v.y + l.c) / absolute(vector_type<T>(l.a, l.b));\
    \ \n}\n\ntemplate <class T>\nstruct segment_type {\n  using value_type = T;\n\
    \  vector_type<value_type> st, en;\n  segment_type(): st(0, 0), en(0, 0) { }\n\
    \  segment_type(const vector_type<value_type> &l, const vector_type<value_type>\
    \ &r): st(l), en(r) { }\n  segment_type(value_type x1, value_type y1, value_type\
    \ x2, value_type y2): st(x1, y1), en(x2, y2) { } \n  bool operator == (const segment_type\
    \ &s) const { \n    return (st == s.st && en == s.en) || (st == s.en && en ==\
    \ s.st);\n  }\n  bool operator != (const segment_type &s) const { \n    return\
    \ !(st == s.st && en == s.en) && !(st == s.en && en == s.st);\n  }\n};\n\ntemplate\
    \ <class T>\nvector_type<T> direction(const segment_type<T> &l) { return l.en\
    \ - l.st;; }\ntemplate <class T>\nline_type<T> to_line(const segment_type<T> &s)\
    \ {\n  auto v = direction(s);\n  auto c = v.y * s.st.x - v.x * s.st.y;\n  return\
    \ line_type<T>(-v.y, v.x, c);\n}\ntemplate <class T>\nline_type<T> bisect(const\
    \ segment_type<T> &s) {\n  auto v = direction(s), u = (s.st + s.en) / 2;\n  return\
    \ line_type<T>(v.x, v.y, -v.x * u.x - v.y * u.y);\n}\n\ntemplate <class T>\nbool\
    \ intersects(const segment_type<T> &s, const segment_type<T> &t) {\n  auto v =\
    \ direction(s), u = direction(t);\n  auto d = cross(v, t.st - s.st) * cross(v,\
    \ t.en - s.st);\n  auto e = cross(u, s.st - t.st) * cross(u, s.en - t.st);\n \
    \ return leq(d, 0) && leq(e, 0);\n}\n\ntemplate <class T>\nstruct circle_type\
    \ {\n  using value_type = T;\n  vector_type<value_type> cn;\n  value_type rd;\n\
    \  circle_type(): cn(0, 0), rd(0) { }\n  circle_type(const vector_type<value_type>\
    \ &cn_, value_type rd_): cn(cn_), rd(rd_) { }\n  circle_type(value_type x_, value_type\
    \ y_, value_type rd_): cn(x_, y_), rd(rd_) { }\n};\n\ntemplate <class T>\nbool\
    \ is_on(const circle_type<T> &c, const vector_type<T> &v) {\n  return equal(c.rd\
    \ * c.rd, norm(v - c.cn));\n}\ntemplate <class T>\nbool is_inside(const circle_type<T>\
    \ &c, const vector_type<T> &v) {\n  return geq(c.rd * c.rd, norm(v - c.cn));\n\
    }\n\ntemplate <class T>\nstd::vector<vector_type<T>> intersection(const circle_type<T>\
    \ &c, const circle_type<T> &d) {\n  auto v = d.cn - c.cn;\n  auto l = absolute(v);\n\
    \  if (equal(l, 0)) return {};\n  if (equal(l + c.rd + d.rd, std::max({ l, c.rd,\
    \ d.rd }) * 2)) return { c.cn + v * (c.rd / l) };\n  if (l + c.rd + d.rd < std::max({\
    \ l, c.rd, d.rd }) * 2) return {};\n  auto x = -(d.rd * d.rd - l * l - c.rd *\
    \ c.rd) / (l * 2);\n  auto y = std::sqrt(c.rd * c.rd - x * x);\n  auto mid = c.cn\
    \ + v * (x / l);\n  auto vec = (-v.y, v.x);\n  return { mid + vec * (y / l), mid\
    \ - vec * (y / l) };\n}\ntemplate <class T>\nstd::vector<vector_type<T>> intersection(const\
    \ circle_type<T> &c, const line_type<T> &l) {\n  auto v = project(l, c.cn);\n\
    \  if (is_on(c, v)) return { v };\n  if (!is_inside(c, v)) return {};\n  auto\
    \ u = direction(l);\n  auto d = std::sqrt(c.rd * c.rd - norm(v - c.cn)) / absolute(u);\n\
    \  return { v + u * d, v - u * d };\n}\n\n/**\n * @title 2D Figures\n */\n#line\
    \ 4 \"geometry/polygon.cpp\"\n\n#include <cstddef>\n#include <vector>\n#include\
    \ <numeric>\n#include <algorithm>\n\ntemplate <class T>\nusing polygon = std::vector<vector_type<T>>;\n\
    \ntemplate <class T>\nT closest_pair_impl(typename polygon<T>::iterator begin,\
    \ typename polygon<T>::iterator end) {\n  size_t size = end - begin;\n  if (size\
    \ <= 1) return real_constant<T>::infinity();\n  size_t mid = size >> 1;\n  auto\
    \ boundary = (begin + mid) -> x;\n  auto res = std::min(closest_pair_impl<T>(begin,\
    \ begin + mid), closest_pair_impl<T>(begin + mid, end));\n  std::inplace_merge(begin,\
    \ begin + mid, end, cmp_y<T>);\n  polygon<T> rectangle;\n  for (auto itr1 = begin;\
    \ itr1 != end; ++itr1) {\n    if (geq(std::abs(itr1 -> x - boundary), res)) continue;\n\
    \    for (auto itr2 = rectangle.rbegin(); itr2 != rectangle.rend(); ++itr2) {\n\
    \      auto dx = itr1 -> x - itr2 -> x;\n      auto dy = itr1 -> y - itr2 -> y;\n\
    \      if (geq(dy, res)) break;\n      res = std::min(res, abs(vector_type<T>(dx,\
    \ dy)));\n    }\n    rectangle.push_back(*itr1);\n  }\n  return res;\n}\n\ntemplate\
    \ <class T>\nT closest_pair(polygon<T> poly) {\n  std::sort(poly.begin(), poly.end(),\
    \ cmp_x<T>);\n  return closest_pair_impl<T>(poly.begin(), poly.end());\n}\n\n\
    template <class T>\nstd::vector<size_t> convex_hull(const polygon<T> &poly) {\n\
    \  if (poly.empty()) return { };\n  size_t N = poly.size();\n  std::vector<size_t>\
    \ order(N);\n  std::iota(order.begin(), order.end(), 0);\n  std::sort(order.begin(),\
    \ order.end(), [&](size_t i, size_t j) {\n    return cmp_x<T>(poly[i], poly[j]);\n\
    \  });\n  size_t M = 0;\n  std::vector<size_t> res(2 * N);\n  const auto necessary\
    \ = [&](size_t i, size_t j, size_t k) {\n    return cross(poly[j] - poly[k], poly[i]\
    \ - poly[k]) > 0;\n  };\n  for (size_t i = 0; i < N; ++i) {\n    while (M >= 2\
    \ && necessary(order[i], res[M - 1], res[M - 2])) --M;\n    res[M++] = order[i];\n\
    \  }\n  for (size_t i = N - 1; i--;) {\n    while (M >= 2 && necessary(order[i],\
    \ res[M - 1], res[M - 2])) --M;\n    res[M++] = order[i];\n  }\n  res.resize(M\
    \ - 1);\n  res.shrink_to_fit();\n  return res;\n}\n\n/**\n * @title 2D Polygons\n\
    \ */\n"
  code: "#pragma once\n\n#include \"../geometry/figures.cpp\"\n\n#include <cstddef>\n\
    #include <vector>\n#include <numeric>\n#include <algorithm>\n\ntemplate <class\
    \ T>\nusing polygon = std::vector<vector_type<T>>;\n\ntemplate <class T>\nT closest_pair_impl(typename\
    \ polygon<T>::iterator begin, typename polygon<T>::iterator end) {\n  size_t size\
    \ = end - begin;\n  if (size <= 1) return real_constant<T>::infinity();\n  size_t\
    \ mid = size >> 1;\n  auto boundary = (begin + mid) -> x;\n  auto res = std::min(closest_pair_impl<T>(begin,\
    \ begin + mid), closest_pair_impl<T>(begin + mid, end));\n  std::inplace_merge(begin,\
    \ begin + mid, end, cmp_y<T>);\n  polygon<T> rectangle;\n  for (auto itr1 = begin;\
    \ itr1 != end; ++itr1) {\n    if (geq(std::abs(itr1 -> x - boundary), res)) continue;\n\
    \    for (auto itr2 = rectangle.rbegin(); itr2 != rectangle.rend(); ++itr2) {\n\
    \      auto dx = itr1 -> x - itr2 -> x;\n      auto dy = itr1 -> y - itr2 -> y;\n\
    \      if (geq(dy, res)) break;\n      res = std::min(res, abs(vector_type<T>(dx,\
    \ dy)));\n    }\n    rectangle.push_back(*itr1);\n  }\n  return res;\n}\n\ntemplate\
    \ <class T>\nT closest_pair(polygon<T> poly) {\n  std::sort(poly.begin(), poly.end(),\
    \ cmp_x<T>);\n  return closest_pair_impl<T>(poly.begin(), poly.end());\n}\n\n\
    template <class T>\nstd::vector<size_t> convex_hull(const polygon<T> &poly) {\n\
    \  if (poly.empty()) return { };\n  size_t N = poly.size();\n  std::vector<size_t>\
    \ order(N);\n  std::iota(order.begin(), order.end(), 0);\n  std::sort(order.begin(),\
    \ order.end(), [&](size_t i, size_t j) {\n    return cmp_x<T>(poly[i], poly[j]);\n\
    \  });\n  size_t M = 0;\n  std::vector<size_t> res(2 * N);\n  const auto necessary\
    \ = [&](size_t i, size_t j, size_t k) {\n    return cross(poly[j] - poly[k], poly[i]\
    \ - poly[k]) > 0;\n  };\n  for (size_t i = 0; i < N; ++i) {\n    while (M >= 2\
    \ && necessary(order[i], res[M - 1], res[M - 2])) --M;\n    res[M++] = order[i];\n\
    \  }\n  for (size_t i = N - 1; i--;) {\n    while (M >= 2 && necessary(order[i],\
    \ res[M - 1], res[M - 2])) --M;\n    res[M++] = order[i];\n  }\n  res.resize(M\
    \ - 1);\n  res.shrink_to_fit();\n  return res;\n}\n\n/**\n * @title 2D Polygons\n\
    \ */"
  dependsOn:
  - geometry/figures.cpp
  - geometry/constants.cpp
  isVerificationFile: false
  path: geometry/polygon.cpp
  requiredBy: []
  timestamp: '2020-08-05 18:30:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: geometry/polygon.cpp
layout: document
redirect_from:
- /library/geometry/polygon.cpp
- /library/geometry/polygon.cpp.html
title: 2D Polygons
---
