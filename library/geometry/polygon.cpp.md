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


# :warning: geometry/polygon.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed7daeb157cd9b31e53896ad3c771a26">geometry</a>
* <a href="{{ site.github.repository_url }}/blob/master/geometry/polygon.cpp">View this file on GitHub</a>
    - Last commit date: 2020-06-10 22:29:55+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp

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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "geometry/polygon.cpp"

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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

