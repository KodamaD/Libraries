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


# :warning: container/segment_tree.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5f0b6ebc4bea10285ba2b8a6ce78b863">container</a>
* <a href="{{ site.github.repository_url }}/blob/master/container/segment_tree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-04 16:35:04+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cstddef>
#include <vector>
#include <iterator>
#include <algorithm>

template <class Monoid>
class segment_tree {
public:
  using structure    = Monoid;
  using value_monoid = typename Monoid::value_structure;
  using value_type   = typename Monoid::value_structure::type;
  using size_type    = size_t;

private:
  std::vector<value_type> M_tree;

  void M_fix_change(const size_type index) {
    M_tree[index] = value_monoid::operation(M_tree[index << 1 | 0], M_tree[index << 1 | 1]);
  }

public:
  segment_tree() = default;
  explicit segment_tree(const size_type size) { initialize(size); }
  template <class InputIterator>
  explicit segment_tree(InputIterator first, InputIterator last) { construct(first, last); }

  void initialize(const size_type size) {
    clear();
    M_tree.assign(size << 1, value_monoid::identity());
  }

  template <class InputIterator>
  void construct(InputIterator first, InputIterator last) {
    clear();
    const size_type size = std::distance(first, last);
    M_tree.reserve(size << 1);
    M_tree.assign(size, value_monoid::identity());
    std::copy(first, last, std::back_inserter(M_tree));
    for (size_type index = size - 1; index != 0; --index) {
      M_fix_change(index);
    }
  }

  void assign(size_type index, const value_type &value) {
    index += size();
    M_tree[index] = value;
    while (index != 1) {
      index >>= 1;
      M_fix_change(index);
    } 
  }

  const value_type& at(size_type index) const { 
    return M_tree[index + size()];
  }

  value_type fold(size_type first, size_type last) const {
    first += size();
    last += size();
    value_type fold_l = value_monoid::identity();
    value_type fold_r = value_monoid::identity();
    while (first != last) {
      if (first & 1) {
        fold_l = value_monoid::operation(fold_l, M_tree[first]);
        ++first;
      }
      if (last & 1) {
        --last;
        fold_r = value_monoid::operation(M_tree[last], fold_r);      
      }
      first >>= 1;
      last  >>= 1;
    }
    return value_monoid::operation(fold_l, fold_r);
  }

  void clear() {
    M_tree.clear();
    M_tree.shrink_to_fit();
  }

  size_type size() const { 
    return M_tree.size() >> 1;
  }

};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "container/segment_tree.cpp"

#include <cstddef>
#include <vector>
#include <iterator>
#include <algorithm>

template <class Monoid>
class segment_tree {
public:
  using structure    = Monoid;
  using value_monoid = typename Monoid::value_structure;
  using value_type   = typename Monoid::value_structure::type;
  using size_type    = size_t;

private:
  std::vector<value_type> M_tree;

  void M_fix_change(const size_type index) {
    M_tree[index] = value_monoid::operation(M_tree[index << 1 | 0], M_tree[index << 1 | 1]);
  }

public:
  segment_tree() = default;
  explicit segment_tree(const size_type size) { initialize(size); }
  template <class InputIterator>
  explicit segment_tree(InputIterator first, InputIterator last) { construct(first, last); }

  void initialize(const size_type size) {
    clear();
    M_tree.assign(size << 1, value_monoid::identity());
  }

  template <class InputIterator>
  void construct(InputIterator first, InputIterator last) {
    clear();
    const size_type size = std::distance(first, last);
    M_tree.reserve(size << 1);
    M_tree.assign(size, value_monoid::identity());
    std::copy(first, last, std::back_inserter(M_tree));
    for (size_type index = size - 1; index != 0; --index) {
      M_fix_change(index);
    }
  }

  void assign(size_type index, const value_type &value) {
    index += size();
    M_tree[index] = value;
    while (index != 1) {
      index >>= 1;
      M_fix_change(index);
    } 
  }

  const value_type& at(size_type index) const { 
    return M_tree[index + size()];
  }

  value_type fold(size_type first, size_type last) const {
    first += size();
    last += size();
    value_type fold_l = value_monoid::identity();
    value_type fold_r = value_monoid::identity();
    while (first != last) {
      if (first & 1) {
        fold_l = value_monoid::operation(fold_l, M_tree[first]);
        ++first;
      }
      if (last & 1) {
        --last;
        fold_r = value_monoid::operation(M_tree[last], fold_r);      
      }
      first >>= 1;
      last  >>= 1;
    }
    return value_monoid::operation(fold_l, fold_r);
  }

  void clear() {
    M_tree.clear();
    M_tree.shrink_to_fit();
  }

  size_type size() const { 
    return M_tree.size() >> 1;
  }

};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

