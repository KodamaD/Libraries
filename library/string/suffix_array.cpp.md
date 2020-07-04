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


# :warning: string/suffix_array.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b45cffe084dd3d20d928bee85e7b0f21">string</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/suffix_array.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-06 17:40:04+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp

template <class T>
class suffix_array {
public:
  using container_type = T;
  using size_type = size_t;

private:
  const size_type M_size;
  const container_type &M_data;
  std::vector<size_type> M_array, M_rank;

public:
  suffix_array(const container_type &data_): M_size(data_.size()), M_data(data_) { 
    M_array.assign(M_size + 1, 0);
    M_rank.assign(M_size + 1, 0);
    M_array.front() = M_size;
    std::iota(M_array.begin() + 1, M_array.end(), 0);
    std::stable_sort(M_array.begin() + 1, M_array.end(), [&](size_type i, size_type j) {
      return M_data[i] < M_data[j];
    });
    M_rank[M_array[0]] = 1;
    for (size_type i = 1; i <= M_size; ++i) {
      if (i > 1 && M_data[M_array[i]] == M_data[M_array[i - 1]]) M_rank[M_array[i]] = M_rank[M_array[i - 1]];
      else M_rank[M_array[i]] = M_rank[M_array[i - 1]] + 1;
    }
    size_type length;
    auto compare = [&](size_type i, size_type j) {
      if (M_rank[i] != M_rank[j]) return M_rank[i] < M_rank[j];
      size_type ti = (i + length <= M_size ? M_rank[i + length] : 0);
      size_type tj = (j + length <= M_size ? M_rank[j + length] : 0);
      return ti < tj;
    };
    std::vector<size_type> copy(M_size + 1);
    for (length = 1; length < M_size; length <<= 1) {
      std::stable_sort(M_array.begin(), M_array.end(), compare);
      copy[M_array[0]] = 1;
      for (size_type i = 1; i <= M_size; ++i) {
        copy[M_array[i]] = copy[M_array[i - 1]] + (compare(M_array[i - 1], M_array[i]) ? 1 : 0);
      }
      for (size_type i = 0; i <= M_size; ++i) {
        M_rank[i] = copy[i];
      }
    }
  }

  size_type operator [](size_type i) const {
    return M_array[i];
  }
  size_type rank(size_type i) const {
    return M_rank[i];
  }
  size_type size() const {
    return M_size;
  }
  const container_type &get() const {
    return M_data;
  }

};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "string/suffix_array.cpp"

template <class T>
class suffix_array {
public:
  using container_type = T;
  using size_type = size_t;

private:
  const size_type M_size;
  const container_type &M_data;
  std::vector<size_type> M_array, M_rank;

public:
  suffix_array(const container_type &data_): M_size(data_.size()), M_data(data_) { 
    M_array.assign(M_size + 1, 0);
    M_rank.assign(M_size + 1, 0);
    M_array.front() = M_size;
    std::iota(M_array.begin() + 1, M_array.end(), 0);
    std::stable_sort(M_array.begin() + 1, M_array.end(), [&](size_type i, size_type j) {
      return M_data[i] < M_data[j];
    });
    M_rank[M_array[0]] = 1;
    for (size_type i = 1; i <= M_size; ++i) {
      if (i > 1 && M_data[M_array[i]] == M_data[M_array[i - 1]]) M_rank[M_array[i]] = M_rank[M_array[i - 1]];
      else M_rank[M_array[i]] = M_rank[M_array[i - 1]] + 1;
    }
    size_type length;
    auto compare = [&](size_type i, size_type j) {
      if (M_rank[i] != M_rank[j]) return M_rank[i] < M_rank[j];
      size_type ti = (i + length <= M_size ? M_rank[i + length] : 0);
      size_type tj = (j + length <= M_size ? M_rank[j + length] : 0);
      return ti < tj;
    };
    std::vector<size_type> copy(M_size + 1);
    for (length = 1; length < M_size; length <<= 1) {
      std::stable_sort(M_array.begin(), M_array.end(), compare);
      copy[M_array[0]] = 1;
      for (size_type i = 1; i <= M_size; ++i) {
        copy[M_array[i]] = copy[M_array[i - 1]] + (compare(M_array[i - 1], M_array[i]) ? 1 : 0);
      }
      for (size_type i = 0; i <= M_size; ++i) {
        M_rank[i] = copy[i];
      }
    }
  }

  size_type operator [](size_type i) const {
    return M_array[i];
  }
  size_type rank(size_type i) const {
    return M_rank[i];
  }
  size_type size() const {
    return M_size;
  }
  const container_type &get() const {
    return M_data;
  }

};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

