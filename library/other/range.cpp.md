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


# :warning: Range

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#795f3202b17cb6bc3d4b771d8c6c9eaf">other</a>
* <a href="{{ site.github.repository_url }}/blob/master/other/range.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-01 22:24:08+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <algorithm>

class range {
public:
  class iterator {
  private:
    int64_t M_position;

  public:
    constexpr iterator(int64_t position) noexcept: M_position(position) { }
    constexpr void operator ++ () noexcept { ++M_position; }
    constexpr bool operator != (iterator other) const noexcept { return M_position != other.M_position; }
    constexpr int64_t operator * () const noexcept { return M_position; }

  };

  class reverse_iterator {
  private:
    int64_t M_position;
  
  public:
    constexpr reverse_iterator(int64_t position) noexcept: M_position(position) { }
    constexpr void operator ++ () noexcept { --M_position; }
    constexpr bool operator != (reverse_iterator other) const noexcept { return M_position != other.M_position; }
    constexpr int64_t operator * () const noexcept { return M_position; }

  };
  
private:
  const iterator M_first, M_last;

public:
  constexpr range(int64_t first, int64_t last) noexcept: M_first(first), M_last(std::max(first, last)) { }
  constexpr iterator begin() const noexcept { return M_first; }
  constexpr iterator end() const noexcept { return M_last; }
  constexpr reverse_iterator rbegin() const noexcept { return reverse_iterator(*M_last - 1); } 
  constexpr reverse_iterator rend() const noexcept { return reverse_iterator(*M_first - 1); } 

};

/**
 * @title Range
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "other/range.cpp"

#include <algorithm>

class range {
public:
  class iterator {
  private:
    int64_t M_position;

  public:
    constexpr iterator(int64_t position) noexcept: M_position(position) { }
    constexpr void operator ++ () noexcept { ++M_position; }
    constexpr bool operator != (iterator other) const noexcept { return M_position != other.M_position; }
    constexpr int64_t operator * () const noexcept { return M_position; }

  };

  class reverse_iterator {
  private:
    int64_t M_position;
  
  public:
    constexpr reverse_iterator(int64_t position) noexcept: M_position(position) { }
    constexpr void operator ++ () noexcept { --M_position; }
    constexpr bool operator != (reverse_iterator other) const noexcept { return M_position != other.M_position; }
    constexpr int64_t operator * () const noexcept { return M_position; }

  };
  
private:
  const iterator M_first, M_last;

public:
  constexpr range(int64_t first, int64_t last) noexcept: M_first(first), M_last(std::max(first, last)) { }
  constexpr iterator begin() const noexcept { return M_first; }
  constexpr iterator end() const noexcept { return M_last; }
  constexpr reverse_iterator rbegin() const noexcept { return reverse_iterator(*M_last - 1); } 
  constexpr reverse_iterator rend() const noexcept { return reverse_iterator(*M_first - 1); } 

};

/**
 * @title Range
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

