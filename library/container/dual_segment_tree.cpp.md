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


# :warning: container/dual_segment_tree.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5f0b6ebc4bea10285ba2b8a6ce78b863">container</a>
* <a href="{{ site.github.repository_url }}/blob/master/container/dual_segment_tree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-02 22:30:28+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp

template <class CombinedMonoid>
class dual_segment_tree {
public:
  using structure       = CombinedMonoid;
  using value_type      = typename CombinedMonoid::value_structure::type;
  using operator_monoid = typename CombinedMonoid::operator_structure;
  using operator_type   = typename CombinedMonoid::operator_structure::type;
  using size_type       = size_t;

private:
  
  static size_type S_lsb(const size_type index) {
    return      __builtin_ctz(index);
  }
  static size_type S_msb(const size_type index) {
    return 31 - __builtin_clz(index);
  }

  static void S_apply(operator_type &op, const operator_type &add) {
    op = operator_monoid::operation(op, add);
  }

  void M_propagate(const size_type index) {
    S_apply(M_tree[index << 1 | 0], M_tree[index]);
    S_apply(M_tree[index << 1 | 1], M_tree[index]);
    M_tree[index] = operator_monoid::identity();
  }

  void M_pushdown(const size_type index) {
    const size_type lsb = S_lsb(index);
    for (size_type story = S_msb(index); story != lsb; --story) {
      M_propagate(index >> story);
    }
  }

  std::vector<value_type> M_leaves; 
  std::vector<operator_type> M_tree;

public:
  dual_segment_tree() = default;
  explicit dual_segment_tree(const size_type size) { initialize(size); }
  template <class InputIterator>
  explicit dual_segment_tree(InputIterator first, InputIterator last) { construct(first, last); }

  void initialize(const size_type size) {
    clear();
    M_leaves.assign(size, value_type{});
    M_tree.assign(size << 1, operator_monoid::identity());
  }

  template <class InputIterator>
  void construct(InputIterator first, InputIterator last) {
    clear();
    const size_type size = std::distance(first, last);
    M_leaves.reserve(size);
    std::copy(first, last, std::back_inserter(M_leaves));
    M_tree.assign(size << 1, operator_monoid::identity());
  }

  value_type at(size_type index) const {
    const size_type index_c = index;
    index += size();
    operator_type op = M_tree[index];
    while (index != 1) {
      index >>= 1;
      S_apply(op, M_tree[index]);
    }
    return structure::operation(M_leaves[index_c], op);
  }

  void operate(size_type first, size_type last, const operator_type &op) {
    first += size();
    last  += size();
    M_pushdown(first);
    M_pushdown(last);
    while (first != last) {
      if (first & 1) {
        S_apply(M_tree[first], op);
        ++first;
      }
      if (last & 1) {
        --last;
        S_apply(M_tree[last], op);
      }
      first >>= 1;
      last  >>= 1;
    }
  }

  void assign(size_type index, const value_type &val) {
    const size_type index_c = index;
    index += size();
    for (size_type story = S_msb(index); story != 0; --story) {
      M_propagate(index >> story);
    }
    M_tree[index] = operator_monoid::identity();
    M_leaves[index_c] = val;
  }

  void clear() {
    M_leaves.clear();
    M_leaves.shrink_to_fit();
    M_tree.clear();
    M_tree.shrink_to_fit();
  }

  size_type size() const { 
    return M_leaves.size();
  }

};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "container/dual_segment_tree.cpp"

template <class CombinedMonoid>
class dual_segment_tree {
public:
  using structure       = CombinedMonoid;
  using value_type      = typename CombinedMonoid::value_structure::type;
  using operator_monoid = typename CombinedMonoid::operator_structure;
  using operator_type   = typename CombinedMonoid::operator_structure::type;
  using size_type       = size_t;

private:
  
  static size_type S_lsb(const size_type index) {
    return      __builtin_ctz(index);
  }
  static size_type S_msb(const size_type index) {
    return 31 - __builtin_clz(index);
  }

  static void S_apply(operator_type &op, const operator_type &add) {
    op = operator_monoid::operation(op, add);
  }

  void M_propagate(const size_type index) {
    S_apply(M_tree[index << 1 | 0], M_tree[index]);
    S_apply(M_tree[index << 1 | 1], M_tree[index]);
    M_tree[index] = operator_monoid::identity();
  }

  void M_pushdown(const size_type index) {
    const size_type lsb = S_lsb(index);
    for (size_type story = S_msb(index); story != lsb; --story) {
      M_propagate(index >> story);
    }
  }

  std::vector<value_type> M_leaves; 
  std::vector<operator_type> M_tree;

public:
  dual_segment_tree() = default;
  explicit dual_segment_tree(const size_type size) { initialize(size); }
  template <class InputIterator>
  explicit dual_segment_tree(InputIterator first, InputIterator last) { construct(first, last); }

  void initialize(const size_type size) {
    clear();
    M_leaves.assign(size, value_type{});
    M_tree.assign(size << 1, operator_monoid::identity());
  }

  template <class InputIterator>
  void construct(InputIterator first, InputIterator last) {
    clear();
    const size_type size = std::distance(first, last);
    M_leaves.reserve(size);
    std::copy(first, last, std::back_inserter(M_leaves));
    M_tree.assign(size << 1, operator_monoid::identity());
  }

  value_type at(size_type index) const {
    const size_type index_c = index;
    index += size();
    operator_type op = M_tree[index];
    while (index != 1) {
      index >>= 1;
      S_apply(op, M_tree[index]);
    }
    return structure::operation(M_leaves[index_c], op);
  }

  void operate(size_type first, size_type last, const operator_type &op) {
    first += size();
    last  += size();
    M_pushdown(first);
    M_pushdown(last);
    while (first != last) {
      if (first & 1) {
        S_apply(M_tree[first], op);
        ++first;
      }
      if (last & 1) {
        --last;
        S_apply(M_tree[last], op);
      }
      first >>= 1;
      last  >>= 1;
    }
  }

  void assign(size_type index, const value_type &val) {
    const size_type index_c = index;
    index += size();
    for (size_type story = S_msb(index); story != 0; --story) {
      M_propagate(index >> story);
    }
    M_tree[index] = operator_monoid::identity();
    M_leaves[index_c] = val;
  }

  void clear() {
    M_leaves.clear();
    M_leaves.shrink_to_fit();
    M_tree.clear();
    M_tree.shrink_to_fit();
  }

  size_type size() const { 
    return M_leaves.size();
  }

};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

