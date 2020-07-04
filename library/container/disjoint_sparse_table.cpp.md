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


# :warning: container/disjoint_sparse_table.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5f0b6ebc4bea10285ba2b8a6ce78b863">container</a>
* <a href="{{ site.github.repository_url }}/blob/master/container/disjoint_sparse_table.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-02 22:24:52+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp

template <class T>
class disjoint_sparse_table {
public:
  using value_type = typename T::value_type;
  static inline const auto op = typename T::value_operation();

private:
  std::vector<std::vector<value_type>> table;

public: 
  disjoint_sparse_table() = default;
  disjoint_sparse_table(const std::vector<value_type> &table_) { build(table_); }

  void build(const std::vector<value_type> &table_) {
    int height = 0, size = table_.size();
    while ((1 << height) < size) ++height;
    if (size == 1) ++height;
    table.assign(height, std::vector<value_type>(size));
    for (int i = 0; i < size; ++i) {
      table[0][i] = table_[i];
    }
    for (int i = 1; i < height; ++i) {
      int bit = (1 << i);
      for (int l = 0; l < size; l += (bit << 1)) {
        int m = (l + bit < size ? l + bit : size);
        table[i][m - 1] = table_[m - 1];
        for (int j = m - 2; j >= l; --j) {
          table[i][j] = op(table_[j], table[i][j + 1]);
        }
        if (m >= size) continue;
        int r = (m + bit < size ? m + bit : size);
        table[i][m] = table_[m];
        for (int j = m + 1; j < r; ++j) {
          table[i][j] = op(table[i][j - 1], table_[j]);
        }
      }
    }
  }

  value_type fold(int l, int r) const {
    if (l >= --r) return table[0][l];
    int h = 31 - __builtin_clz(l ^ r);
    return op(table[h][l], table[h][r]);
  }

};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "container/disjoint_sparse_table.cpp"

template <class T>
class disjoint_sparse_table {
public:
  using value_type = typename T::value_type;
  static inline const auto op = typename T::value_operation();

private:
  std::vector<std::vector<value_type>> table;

public: 
  disjoint_sparse_table() = default;
  disjoint_sparse_table(const std::vector<value_type> &table_) { build(table_); }

  void build(const std::vector<value_type> &table_) {
    int height = 0, size = table_.size();
    while ((1 << height) < size) ++height;
    if (size == 1) ++height;
    table.assign(height, std::vector<value_type>(size));
    for (int i = 0; i < size; ++i) {
      table[0][i] = table_[i];
    }
    for (int i = 1; i < height; ++i) {
      int bit = (1 << i);
      for (int l = 0; l < size; l += (bit << 1)) {
        int m = (l + bit < size ? l + bit : size);
        table[i][m - 1] = table_[m - 1];
        for (int j = m - 2; j >= l; --j) {
          table[i][j] = op(table_[j], table[i][j + 1]);
        }
        if (m >= size) continue;
        int r = (m + bit < size ? m + bit : size);
        table[i][m] = table_[m];
        for (int j = m + 1; j < r; ++j) {
          table[i][j] = op(table[i][j - 1], table_[j]);
        }
      }
    }
  }

  value_type fold(int l, int r) const {
    if (l >= --r) return table[0][l];
    int h = 31 - __builtin_clz(l ^ r);
    return op(table[h][l], table[h][r]);
  }

};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

