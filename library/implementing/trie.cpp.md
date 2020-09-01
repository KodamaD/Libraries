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


# :warning: implementing/trie.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#be68540dfa000a0fb38be40d32259215">implementing</a>
* <a href="{{ site.github.repository_url }}/blob/master/implementing/trie.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-01 23:08:04+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cstddef>
#include <vector>
#include <iterator>
#include <map>
#include <array>

template <class Node>
class trie_impl {
public:
  using size_type = size_t;
  using value_type = typename Node::value_type;

private:
  using node_type = Node;

  std::vector<node_type> M_tree;

  size_type M_add_node() {
    const auto res = M_tree.size();
    M_tree.emplace_back();
    return res;
  }

public:
  explicit trie_impl() { M_add_node(); }

  template <class InputIterator>
  std::vector<size_type> insert(InputIterator first, InputIterator last) {
    std::vector<size_type> res;
    res.reserve(std::distance(first, last) + 1);
    res.push_back(0);
    size_type cur = 0;
    for (; first != last; ++first) {
      const auto &c = *first;
      if (~next(cur, c) == 0) {
        const auto new_node = M_add_node();
        M_tree[cur].emplace(c, new_node);
      }
      cur = next(cur, c);
      res.push_back(cur);
    }
    return res;
  }

  template <class InputIterator>
  std::vector<size_type> find_path(InputIterator first, InputIterator last) const {
    const size_type size = std::distance(first, last) + 1;
    std::vector<size_type> res;
    res.reserve(size);
    res.push_back(0);
    size_type cur = 0;
    for (; first != last; ++first) {
      cur = next(cur, *first);
      if (~cur == 0) {
        break;
      }
      res.push_back(cur);
    }
    res.resize(size, size_type(-1));
    return res;
  }

  size_type next(const size_type index, const value_type &value) const {
    return M_tree[index].next(value);
  }
  size_type size() const {
    return M_tree.size();
  }

};

template <class T>
class map_based_trie_node {
public:
  using value_type = T;
private:
  std::map<value_type, size_t> M_children;
public:
  explicit map_based_trie_node(): M_children() { }
  size_t next(const value_type &value) const {
    const auto itr = M_children.find(value);
    return (itr == M_children.end() ? size_t(-1) : itr -> second);
  }
  void emplace(const value_type &value, const size_t index) {
    M_children.emplace(value, index);
  }
};

template <class T, T MinValue, size_t Size>
class array_based_trie_node {
public:
  using value_type = T;
private:
  std::array<size_t, Size> M_children;
public:
  explicit array_based_trie_node() { M_children.fill(size_t(-1)); }
  size_t next(const value_type &value) const {
    return M_children[value - MinValue];
  }
  void emplace(const value_type &value, const size_t index) {
    M_children[value - MinValue] = index;
  }
};

template <class T>
using trie_any = trie_impl<map_based_trie_node<T>>;

template <class T, T MinValue, size_t Size>
using trie_alphabet = trie_impl<array_based_trie_node<T, MinValue, Size>>;

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "implementing/trie.cpp"

#include <cstddef>
#include <vector>
#include <iterator>
#include <map>
#include <array>

template <class Node>
class trie_impl {
public:
  using size_type = size_t;
  using value_type = typename Node::value_type;

private:
  using node_type = Node;

  std::vector<node_type> M_tree;

  size_type M_add_node() {
    const auto res = M_tree.size();
    M_tree.emplace_back();
    return res;
  }

public:
  explicit trie_impl() { M_add_node(); }

  template <class InputIterator>
  std::vector<size_type> insert(InputIterator first, InputIterator last) {
    std::vector<size_type> res;
    res.reserve(std::distance(first, last) + 1);
    res.push_back(0);
    size_type cur = 0;
    for (; first != last; ++first) {
      const auto &c = *first;
      if (~next(cur, c) == 0) {
        const auto new_node = M_add_node();
        M_tree[cur].emplace(c, new_node);
      }
      cur = next(cur, c);
      res.push_back(cur);
    }
    return res;
  }

  template <class InputIterator>
  std::vector<size_type> find_path(InputIterator first, InputIterator last) const {
    const size_type size = std::distance(first, last) + 1;
    std::vector<size_type> res;
    res.reserve(size);
    res.push_back(0);
    size_type cur = 0;
    for (; first != last; ++first) {
      cur = next(cur, *first);
      if (~cur == 0) {
        break;
      }
      res.push_back(cur);
    }
    res.resize(size, size_type(-1));
    return res;
  }

  size_type next(const size_type index, const value_type &value) const {
    return M_tree[index].next(value);
  }
  size_type size() const {
    return M_tree.size();
  }

};

template <class T>
class map_based_trie_node {
public:
  using value_type = T;
private:
  std::map<value_type, size_t> M_children;
public:
  explicit map_based_trie_node(): M_children() { }
  size_t next(const value_type &value) const {
    const auto itr = M_children.find(value);
    return (itr == M_children.end() ? size_t(-1) : itr -> second);
  }
  void emplace(const value_type &value, const size_t index) {
    M_children.emplace(value, index);
  }
};

template <class T, T MinValue, size_t Size>
class array_based_trie_node {
public:
  using value_type = T;
private:
  std::array<size_t, Size> M_children;
public:
  explicit array_based_trie_node() { M_children.fill(size_t(-1)); }
  size_t next(const value_type &value) const {
    return M_children[value - MinValue];
  }
  void emplace(const value_type &value, const size_t index) {
    M_children[value - MinValue] = index;
  }
};

template <class T>
using trie_any = trie_impl<map_based_trie_node<T>>;

template <class T, T MinValue, size_t Size>
using trie_alphabet = trie_impl<array_based_trie_node<T, MinValue, Size>>;

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

