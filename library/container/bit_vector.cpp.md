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


# :warning: container/bit_vector.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5f0b6ebc4bea10285ba2b8a6ce78b863">container</a>
* <a href="{{ site.github.repository_url }}/blob/master/container/bit_vector.cpp">View this file on GitHub</a>
    - Last commit date: 2020-06-07 19:54:49+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp

class bit_vector {
public:
  using size_type = size_t;
  using bit_type = uint64_t;
  using count_type = uint32_t;

  static constexpr size_type block_size = 64;

private:
  size_type size;
  std::vector<bit_type> block;
  std::vector<count_type> accum;

public:
  bit_vector() = default;
  bit_vector(const std::vector<bool> &data_) { build(data_); }

  void build(const std::vector<bool> &data_) {
    size = data_.size();
    size_type fixed_size = size / block_size + 1;
    block.assign(fixed_size, 0);
    accum.assign(fixed_size, 0);
    for (size_type i = 0; i < size; ++i) {
      if (data_[i]) {
        block[i / block_size] |= bit_type(1) << (i & (block_size - 1));
      }
    }
    for (size_type i = 1; i < fixed_size; ++i) {
      accum[i] = accum[i - 1] + __builtin_popcountll(block[i - 1]);
    }
  }

  bool access(size_type idx) const {
    return block[idx / block_size] >> (idx & (block_size - 1)) & 1;
  }
  size_type rank(bool value, size_type idx) const {
    bit_type mask = (bit_type(1) << (idx & (block_size - 1))) - 1;
    size_type res = accum[idx / block_size] + __builtin_popcountll(block[idx / block_size] & mask);
    return value ? res : idx - res;
  }
  size_type select(bool value, size_type idx) const {
    if (idx >= rank(value, size)) {
      return size;
    }
    size_type ok = 0, ng = size;
    while (ng - ok > 1) {
      size_type md = (ok + ng) >> 1;
      (rank(value, md) <= idx ? ok : ng) = md;
    }
    return ok;
  }
  size_type select(bool value, size_type idx, size_type l) const {
    return select(value, idx + rank(value, l));
  }

};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "container/bit_vector.cpp"

class bit_vector {
public:
  using size_type = size_t;
  using bit_type = uint64_t;
  using count_type = uint32_t;

  static constexpr size_type block_size = 64;

private:
  size_type size;
  std::vector<bit_type> block;
  std::vector<count_type> accum;

public:
  bit_vector() = default;
  bit_vector(const std::vector<bool> &data_) { build(data_); }

  void build(const std::vector<bool> &data_) {
    size = data_.size();
    size_type fixed_size = size / block_size + 1;
    block.assign(fixed_size, 0);
    accum.assign(fixed_size, 0);
    for (size_type i = 0; i < size; ++i) {
      if (data_[i]) {
        block[i / block_size] |= bit_type(1) << (i & (block_size - 1));
      }
    }
    for (size_type i = 1; i < fixed_size; ++i) {
      accum[i] = accum[i - 1] + __builtin_popcountll(block[i - 1]);
    }
  }

  bool access(size_type idx) const {
    return block[idx / block_size] >> (idx & (block_size - 1)) & 1;
  }
  size_type rank(bool value, size_type idx) const {
    bit_type mask = (bit_type(1) << (idx & (block_size - 1))) - 1;
    size_type res = accum[idx / block_size] + __builtin_popcountll(block[idx / block_size] & mask);
    return value ? res : idx - res;
  }
  size_type select(bool value, size_type idx) const {
    if (idx >= rank(value, size)) {
      return size;
    }
    size_type ok = 0, ng = size;
    while (ng - ok > 1) {
      size_type md = (ok + ng) >> 1;
      (rank(value, md) <= idx ? ok : ng) = md;
    }
    return ok;
  }
  size_type select(bool value, size_type idx, size_type l) const {
    return select(value, idx + rank(value, l));
  }

};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

