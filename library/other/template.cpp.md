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


# :warning: other/template.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#795f3202b17cb6bc3d4b771d8c6c9eaf">other</a>
* <a href="{{ site.github.repository_url }}/blob/master/other/template.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-03 23:58:07+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp

#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
#include <array>

template <class T, class U>
inline bool chmin(T &lhs, const U &rhs) {
  if (lhs > rhs) { lhs = rhs; return true; }
  return false;
}

template <class T, class U>
inline bool chmax(T &lhs, const U &rhs) {
  if (lhs < rhs) { lhs = rhs; return true; }
  return false;
}

struct range {
  using itr = int64_t;
  struct iterator {
    itr i;
    constexpr iterator(itr i_) noexcept : i(i_) { }
    constexpr void operator ++ () noexcept { ++i; }
    constexpr itr operator * () const noexcept { return i; }
    constexpr bool operator != (iterator x) const noexcept { return i != x.i; }
  };
  const iterator l, r;
  constexpr range(itr l_, itr r_) noexcept : l(l_), r(std::max(l_, r_)) { }
  constexpr iterator begin() const noexcept { return l; }
  constexpr iterator end() const noexcept { return r; }
};

struct revrange {
  using itr = int64_t;
  struct iterator {
    itr i;
    constexpr iterator(itr i_) noexcept : i(i_) { }
    constexpr void operator ++ () noexcept { --i; }
    constexpr itr operator * () const noexcept { return i; }
    constexpr bool operator != (iterator x) const noexcept { return i != x.i; }
  };
  const iterator l, r;
  constexpr revrange(itr l_, itr r_) noexcept : l(l_ - 1), r(std::max(l_, r_) - 1) { }
  constexpr iterator begin() const noexcept { return r; }
  constexpr iterator end() const noexcept { return l; }
};

using i32 = int32_t;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;

constexpr i32 inf32 = (i32(1) << 30) - 1;
constexpr i64 inf64 = (i64(1) << 62) - 1;

int main() {
  
  return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "other/template.cpp"

#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
#include <array>

template <class T, class U>
inline bool chmin(T &lhs, const U &rhs) {
  if (lhs > rhs) { lhs = rhs; return true; }
  return false;
}

template <class T, class U>
inline bool chmax(T &lhs, const U &rhs) {
  if (lhs < rhs) { lhs = rhs; return true; }
  return false;
}

struct range {
  using itr = int64_t;
  struct iterator {
    itr i;
    constexpr iterator(itr i_) noexcept : i(i_) { }
    constexpr void operator ++ () noexcept { ++i; }
    constexpr itr operator * () const noexcept { return i; }
    constexpr bool operator != (iterator x) const noexcept { return i != x.i; }
  };
  const iterator l, r;
  constexpr range(itr l_, itr r_) noexcept : l(l_), r(std::max(l_, r_)) { }
  constexpr iterator begin() const noexcept { return l; }
  constexpr iterator end() const noexcept { return r; }
};

struct revrange {
  using itr = int64_t;
  struct iterator {
    itr i;
    constexpr iterator(itr i_) noexcept : i(i_) { }
    constexpr void operator ++ () noexcept { --i; }
    constexpr itr operator * () const noexcept { return i; }
    constexpr bool operator != (iterator x) const noexcept { return i != x.i; }
  };
  const iterator l, r;
  constexpr revrange(itr l_, itr r_) noexcept : l(l_ - 1), r(std::max(l_, r_) - 1) { }
  constexpr iterator begin() const noexcept { return r; }
  constexpr iterator end() const noexcept { return l; }
};

using i32 = int32_t;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;

constexpr i32 inf32 = (i32(1) << 30) - 1;
constexpr i64 inf64 = (i64(1) << 62) - 1;

int main() {
  
  return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

