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


# :warning: container/fenwick_tree.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5f0b6ebc4bea10285ba2b8a6ce78b863">container</a>
* <a href="{{ site.github.repository_url }}/blob/master/container/fenwick_tree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-02 22:24:52+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp

template <class T>
class fenwick_tree {
public:
  using value_type = T;

private:
  int size;
  std::vector<value_type> node;

public:
  fenwick_tree() = default;
  fenwick_tree(int size_) { init(size_); }

  void init(int size_) {
    size = size_;
    node.assign(size_ + 1, 0);
  }

  void modify(int i, const value_type& x) {
    ++i;
    while (i <= size) {
      node[i] += x;
      i += i & -i;
    }
  }

  value_type get(int i) const {
    ++i;
    value_type res = 0;
    while (i > 0) {
      res += node[i];
      i -= i & -i;
    }
    return res;
  }
  value_type fold(int l, int r) const {
    return get(r - 1) - get(l - 1);
  }

};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "container/fenwick_tree.cpp"

template <class T>
class fenwick_tree {
public:
  using value_type = T;

private:
  int size;
  std::vector<value_type> node;

public:
  fenwick_tree() = default;
  fenwick_tree(int size_) { init(size_); }

  void init(int size_) {
    size = size_;
    node.assign(size_ + 1, 0);
  }

  void modify(int i, const value_type& x) {
    ++i;
    while (i <= size) {
      node[i] += x;
      i += i & -i;
    }
  }

  value_type get(int i) const {
    ++i;
    value_type res = 0;
    while (i > 0) {
      res += node[i];
      i -= i & -i;
    }
    return res;
  }
  value_type fold(int l, int r) const {
    return get(r - 1) - get(l - 1);
  }

};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

