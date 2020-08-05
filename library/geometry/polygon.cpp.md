---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: 2D Polygons

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed7daeb157cd9b31e53896ad3c771a26">geometry</a>
* <a href="{{ site.github.repository_url }}/blob/master/geometry/polygon.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-05 18:30:10+09:00




## Depends on

* :warning: <a href="constants.cpp.html">Geometric Constants</a>
* :warning: <a href="figures.cpp.html">2D Figures</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "../geometry/figures.cpp"

#include <cstddef>
#include <vector>
#include <numeric>
#include <algorithm>

template <class T>
using polygon = std::vector<vector_type<T>>;

template <class T>
T closest_pair_impl(typename polygon<T>::iterator begin, typename polygon<T>::iterator end) {
  size_t size = end - begin;
  if (size <= 1) return real_constant<T>::infinity();
  size_t mid = size >> 1;
  auto boundary = (begin + mid) -> x;
  auto res = std::min(closest_pair_impl<T>(begin, begin + mid), closest_pair_impl<T>(begin + mid, end));
  std::inplace_merge(begin, begin + mid, end, cmp_y<T>);
  polygon<T> rectangle;
  for (auto itr1 = begin; itr1 != end; ++itr1) {
    if (geq(std::abs(itr1 -> x - boundary), res)) continue;
    for (auto itr2 = rectangle.rbegin(); itr2 != rectangle.rend(); ++itr2) {
      auto dx = itr1 -> x - itr2 -> x;
      auto dy = itr1 -> y - itr2 -> y;
      if (geq(dy, res)) break;
      res = std::min(res, abs(vector_type<T>(dx, dy)));
    }
    rectangle.push_back(*itr1);
  }
  return res;
}

template <class T>
T closest_pair(polygon<T> poly) {
  std::sort(poly.begin(), poly.end(), cmp_x<T>);
  return closest_pair_impl<T>(poly.begin(), poly.end());
}

template <class T>
std::vector<size_t> convex_hull(const polygon<T> &poly) {
  if (poly.empty()) return { };
  size_t N = poly.size();
  std::vector<size_t> order(N);
  std::iota(order.begin(), order.end(), 0);
  std::sort(order.begin(), order.end(), [&](size_t i, size_t j) {
    return cmp_x<T>(poly[i], poly[j]);
  });
  size_t M = 0;
  std::vector<size_t> res(2 * N);
  const auto necessary = [&](size_t i, size_t j, size_t k) {
    return cross(poly[j] - poly[k], poly[i] - poly[k]) > 0;
  };
  for (size_t i = 0; i < N; ++i) {
    while (M >= 2 && necessary(order[i], res[M - 1], res[M - 2])) --M;
    res[M++] = order[i];
  }
  for (size_t i = N - 1; i--;) {
    while (M >= 2 && necessary(order[i], res[M - 1], res[M - 2])) --M;
    res[M++] = order[i];
  }
  res.resize(M - 1);
  res.shrink_to_fit();
  return res;
}

/**
 * @title 2D Polygons
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "geometry/polygon.cpp"

#line 2 "geometry/figures.cpp"

#line 2 "geometry/constants.cpp"

#include <cmath>

template <class T>
struct real_constant;

template <>
struct real_constant<double> {
  using value_type = double;
  static constexpr value_type infinity() { return 1e9; }
  static constexpr value_type epsilon() { return 1e-9; }
  static constexpr value_type pi() { return std::acos(-1.0); }
};

template <>
struct real_constant<long double> {
  using value_type = long double;
  static constexpr value_type infinity() { return 1e18; }
  static constexpr value_type epsilon() { return 1e-10; }
  static constexpr value_type pi() { return std::acos(-1.0L); }
};

template <>
struct real_constant<__float128> {
  using value_type = __float128;
  static constexpr value_type infinity() { return 1e18; }
  static constexpr value_type epsilon() { return 1e-10; }
  static constexpr value_type pi() { return std::acos(-1.0L); }
};

template <>
struct real_constant<int32_t> {
  using value_type = int32_t;
  static constexpr value_type infinity() { return 1e9; }
  static constexpr value_type epsilon() { return 1; }
};

template <>
struct real_constant<int64_t> {
  using value_type = int64_t;
  static constexpr value_type infinity() { return 1e18; }
  static constexpr value_type epsilon() { return 1; }
};

template <class T, class U>
bool leq(T x, U y) {
  return x - y < real_constant<T>::epsilon();
}
template <class T, class U>
bool geq(T x, U y) {
  return y - x < real_constant<T>::epsilon();
}
template <class T, class U>
bool equal(T x, U y) {
  return leq(x, y) && geq(x, y);
}

template <class T>
T to_radian(T deg) {
  return deg * real_constant<T>::pi() / 180;
}
template <class T>
T to_degree(T rad) {
  return rad / real_constant<T>::pi() * 180;
}

/**
 * @title Geometric Constants
 */
#line 4 "geometry/figures.cpp"

template <class T>
struct vector_type {
  using value_type = T;
  value_type x, y;
  vector_type(): x(0), y(0) { }
  vector_type(value_type x_, value_type y_): x(x_), y(y_) { }
  vector_type &operator += (const vector_type &rhs) { x += rhs.x; y += rhs.y; return *this; }
  vector_type operator + (const vector_type &rhs) const { return vector_type(*this) += rhs; }
  vector_type &operator -= (const vector_type &rhs) { x -= rhs.x; y -= rhs.y; return *this; }
  vector_type operator - (const vector_type &rhs) const { return vector_type(*this) -= rhs; }
  vector_type operator - () const { return vector_type(-x, -y); }
  vector_type &operator *= (value_type rhs) { x *= rhs; y *= rhs; return *this; }
  vector_type &operator /= (value_type rhs) { x /= rhs; y /= rhs; return *this; }
  bool operator == (const vector_type &rhs) const { return equal(x, rhs.x) && equal(y, rhs.y); }
  bool operator != (const vector_type &rhs) const { return !equal(x, rhs.x) || !equal(y, rhs.y); }
};

template <class T, class U>
vector_type<T> operator * (vector_type<T> v, U rhs) { return v *= rhs; }
template <class T, class U>
vector_type<T> operator * (U rhs, vector_type<T> v) { return v *= rhs; }
template <class T, class U>
vector_type<T> operator / (vector_type<T> v, U rhs) { return v /= rhs; }

template <class T>
std::istream& operator >> (std::istream& is, vector_type<T> &v) { return is >> v.x >> v.y; }
template <class T>
std::ostream& operator << (std::ostream& os, const vector_type<T> &v) { return os << v.x << ' ' <<  v.y; }

template <class T>
T norm(const vector_type<T> &v) { 
  return v.x * v.x + v.y * v.y; 
}
template <class T>
T absolute(const vector_type<T> &v) { 
  return std::sqrt(norm(v));
}
template <class T>
T argument(const vector_type<T> &v) {  
  auto res = std::atan2(v.y, v.x); 
  return res < 0 ? res + 2 * real_constant<T>::pi() : res;
}

template <class T>
T distance(const vector_type<T> &v, const vector_type<T> &u) { 
  return absolute(v - u); 
}
template <class T>
T dot(const vector_type<T> &v, const vector_type<T> &u) { 
  return v.x * u.x + v.y * u.y; 
}
template <class T>
T cross(const vector_type<T> &v, const vector_type<T> &u) { 
  return v.x * u.y - v.y * u.x; 
}

template <class T>
size_t orthan(const vector_type<T> &v) {
  if (v.x > 0 && v.y >= 0) return 0;
  if (v.x <= 0 && v.y > 0) return 1;
  if (v.x < 0 && v.y <= 0) return 2;
  if (v.x >= 0 && v.y < 0) return 3;
  return 0;
}

template <class T>
vector_type<T> polar(T rho, T theta = T()) {
  return rho * vector_type<T>(std::cos(theta), std::sin(theta));
}

template <class T>
bool cmp_x(const vector_type<T> &v, const vector_type<T> &u) {
  if (equal(v.x, u.x)) return v.y < u.y;
  return v.x < u.x;
}
template <class T>
bool cmp_y(const vector_type<T> &v, const vector_type<T> &u) {
  if (equal(v.y, u.y)) return v.x < u.x;
  return v.y < u.y;
}
template <class T>
bool cmp_arg(const vector_type<T> &v, const vector_type<T> &u) {
  if (orthan(v) != orthan(u)) return orthan(v) < orthan(u);
  if (!equal(cross(v, u), 0)) return cross(v, u) > 0;
  return norm(v) < norm(u);
}

template <class T>
struct line_type {
  using value_type = T;
  value_type a, b, c;
  line_type(): a(0), b(0), c(0) { }
  line_type(value_type a_, value_type c_): a(a_), b(-1), c(c_) { }
  line_type(value_type a_, value_type b_, value_type c_): a(a_), b(b_), c(c_) { }
  value_type valx(value_type y) const { return (b * y + c) / (-a); }
  value_type valy(value_type x) const { return (a * x + c) / (-b); }
  bool operator == (const value_type &l) const { return equal(a * l.b, b * l.a) && equal(a * l.c, c * l.a); }
  bool operator != (const value_type &l) const { return !equal(a * l.b, b * l.a) || !equal(a * l.c, c * l.a); }
};

template <class T>
bool parallel(const line_type<T> &l, const line_type<T> &m) { 
  return equal(l.a * m.b, l.b * m.a); 
}
template <class T>
bool vertical(const line_type<T> &l, const line_type<T> &m) { 
  return equal(l.a * m.a + l.b * m.b, 0); 
}
template <class T>
bool is_on(const line_type<T> &l, const vector_type<T> &v) { 
  return equal(l.a * v.x + l.b * v.y + l.c, 0);
}

template <class T>
vector_type<T> intersection(const line_type<T> &l, const line_type<T> &m) {
  auto x = (l.b * m.c - l.c * m.b) / (l.a * m.b - l.b * m.a);
  auto y = (l.c * m.a - l.a * m.c) / (l.a * m.b - l.b * m.a);
  return vector_type<T>(x, y);
}
template <class T>
vector_type<T> direction(const line_type<T> &l) { 
  return vector_type<T>(-l.b, l.a); 
}
template <class T>
vector_type<T> perpend(const line_type<T> &l, const vector_type<T> &v) {
  auto u = vector_type<T>(l.a, l.b);
  auto d = -l.c / norm(u);
  auto e = dot(v, u) / norm(u);
  return (d - e) * u;
}
template <class T>
vector_type<T> project(const line_type<T> &l, const vector_type<T> &v) {
  return v + perpend(l, v);
}
template <class T>
vector_type<T> relfect(const line_type<T> &l, const vector_type<T> &v) {
  return v + perpend(l, v) * 2;
}

template <class T>
T distance(const line_type<T> &l, const vector_type<T> &v) { 
  return std::abs(l.a * v.x + l.b * v.y + l.c) / absolute(vector_type<T>(l.a, l.b)); 
}

template <class T>
struct segment_type {
  using value_type = T;
  vector_type<value_type> st, en;
  segment_type(): st(0, 0), en(0, 0) { }
  segment_type(const vector_type<value_type> &l, const vector_type<value_type> &r): st(l), en(r) { }
  segment_type(value_type x1, value_type y1, value_type x2, value_type y2): st(x1, y1), en(x2, y2) { } 
  bool operator == (const segment_type &s) const { 
    return (st == s.st && en == s.en) || (st == s.en && en == s.st);
  }
  bool operator != (const segment_type &s) const { 
    return !(st == s.st && en == s.en) && !(st == s.en && en == s.st);
  }
};

template <class T>
vector_type<T> direction(const segment_type<T> &l) { return l.en - l.st;; }
template <class T>
line_type<T> to_line(const segment_type<T> &s) {
  auto v = direction(s);
  auto c = v.y * s.st.x - v.x * s.st.y;
  return line_type<T>(-v.y, v.x, c);
}
template <class T>
line_type<T> bisect(const segment_type<T> &s) {
  auto v = direction(s), u = (s.st + s.en) / 2;
  return line_type<T>(v.x, v.y, -v.x * u.x - v.y * u.y);
}

template <class T>
bool intersects(const segment_type<T> &s, const segment_type<T> &t) {
  auto v = direction(s), u = direction(t);
  auto d = cross(v, t.st - s.st) * cross(v, t.en - s.st);
  auto e = cross(u, s.st - t.st) * cross(u, s.en - t.st);
  return leq(d, 0) && leq(e, 0);
}

template <class T>
struct circle_type {
  using value_type = T;
  vector_type<value_type> cn;
  value_type rd;
  circle_type(): cn(0, 0), rd(0) { }
  circle_type(const vector_type<value_type> &cn_, value_type rd_): cn(cn_), rd(rd_) { }
  circle_type(value_type x_, value_type y_, value_type rd_): cn(x_, y_), rd(rd_) { }
};

template <class T>
bool is_on(const circle_type<T> &c, const vector_type<T> &v) {
  return equal(c.rd * c.rd, norm(v - c.cn));
}
template <class T>
bool is_inside(const circle_type<T> &c, const vector_type<T> &v) {
  return geq(c.rd * c.rd, norm(v - c.cn));
}

template <class T>
std::vector<vector_type<T>> intersection(const circle_type<T> &c, const circle_type<T> &d) {
  auto v = d.cn - c.cn;
  auto l = absolute(v);
  if (equal(l, 0)) return {};
  if (equal(l + c.rd + d.rd, std::max({ l, c.rd, d.rd }) * 2)) return { c.cn + v * (c.rd / l) };
  if (l + c.rd + d.rd < std::max({ l, c.rd, d.rd }) * 2) return {};
  auto x = -(d.rd * d.rd - l * l - c.rd * c.rd) / (l * 2);
  auto y = std::sqrt(c.rd * c.rd - x * x);
  auto mid = c.cn + v * (x / l);
  auto vec = (-v.y, v.x);
  return { mid + vec * (y / l), mid - vec * (y / l) };
}
template <class T>
std::vector<vector_type<T>> intersection(const circle_type<T> &c, const line_type<T> &l) {
  auto v = project(l, c.cn);
  if (is_on(c, v)) return { v };
  if (!is_inside(c, v)) return {};
  auto u = direction(l);
  auto d = std::sqrt(c.rd * c.rd - norm(v - c.cn)) / absolute(u);
  return { v + u * d, v - u * d };
}

/**
 * @title 2D Figures
 */
#line 4 "geometry/polygon.cpp"

#include <cstddef>
#include <vector>
#include <numeric>
#include <algorithm>

template <class T>
using polygon = std::vector<vector_type<T>>;

template <class T>
T closest_pair_impl(typename polygon<T>::iterator begin, typename polygon<T>::iterator end) {
  size_t size = end - begin;
  if (size <= 1) return real_constant<T>::infinity();
  size_t mid = size >> 1;
  auto boundary = (begin + mid) -> x;
  auto res = std::min(closest_pair_impl<T>(begin, begin + mid), closest_pair_impl<T>(begin + mid, end));
  std::inplace_merge(begin, begin + mid, end, cmp_y<T>);
  polygon<T> rectangle;
  for (auto itr1 = begin; itr1 != end; ++itr1) {
    if (geq(std::abs(itr1 -> x - boundary), res)) continue;
    for (auto itr2 = rectangle.rbegin(); itr2 != rectangle.rend(); ++itr2) {
      auto dx = itr1 -> x - itr2 -> x;
      auto dy = itr1 -> y - itr2 -> y;
      if (geq(dy, res)) break;
      res = std::min(res, abs(vector_type<T>(dx, dy)));
    }
    rectangle.push_back(*itr1);
  }
  return res;
}

template <class T>
T closest_pair(polygon<T> poly) {
  std::sort(poly.begin(), poly.end(), cmp_x<T>);
  return closest_pair_impl<T>(poly.begin(), poly.end());
}

template <class T>
std::vector<size_t> convex_hull(const polygon<T> &poly) {
  if (poly.empty()) return { };
  size_t N = poly.size();
  std::vector<size_t> order(N);
  std::iota(order.begin(), order.end(), 0);
  std::sort(order.begin(), order.end(), [&](size_t i, size_t j) {
    return cmp_x<T>(poly[i], poly[j]);
  });
  size_t M = 0;
  std::vector<size_t> res(2 * N);
  const auto necessary = [&](size_t i, size_t j, size_t k) {
    return cross(poly[j] - poly[k], poly[i] - poly[k]) > 0;
  };
  for (size_t i = 0; i < N; ++i) {
    while (M >= 2 && necessary(order[i], res[M - 1], res[M - 2])) --M;
    res[M++] = order[i];
  }
  for (size_t i = N - 1; i--;) {
    while (M >= 2 && necessary(order[i], res[M - 1], res[M - 2])) --M;
    res[M++] = order[i];
  }
  res.resize(M - 1);
  res.shrink_to_fit();
  return res;
}

/**
 * @title 2D Polygons
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

