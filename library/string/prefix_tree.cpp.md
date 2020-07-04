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


# :warning: string/prefix_tree.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b45cffe084dd3d20d928bee85e7b0f21">string</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/prefix_tree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-06 17:40:04+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp

template <size_t L = 26>
class prefix_tree {
public:
  static constexpr size_t letter_size = L;

  struct node {
    int index;
    std::array<int, letter_size> next;
    char letter;
    node(char c): letter(c), index(-1) {
      next.fill(-1);
    }
  };

private:
  const char base;
  std::vector<node> data;

public:
  prefix_tree(char base = 'a', char root = '$'): base(base) { data.emplace_back(root); }

  void add(const std::string& str, int index) {
    int pos = 0;
    for (int i = 0; i < str.size(); ++i) {
      int k = str[i] - base;
      if (data[pos].next[k] != -1) {
        pos = data[pos].next[k];
        continue;
      }
      int pos_new = data.size();
      data[pos].next[k] = pos_new;
      data.emplace_back(str[i]);
      pos = pos_new;
    }
    data[pos].index = index;
  }

  int find(const std::string& str) const {
    int pos = 0;
    for (int i = 0; i < str.size(); ++i) {
      int k = str[i] - base;
      if (data[pos].next[k] == -1) {
        return -1;
      }
      pos = data[pos].next[k];
    }
    return pos;
  }

  int find(int i, char c) const {
    return data[i].next[c - base];
  }
  int index(int i) const {
    return i == -1 ? -1 : data[i].index;
  }

};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "string/prefix_tree.cpp"

template <size_t L = 26>
class prefix_tree {
public:
  static constexpr size_t letter_size = L;

  struct node {
    int index;
    std::array<int, letter_size> next;
    char letter;
    node(char c): letter(c), index(-1) {
      next.fill(-1);
    }
  };

private:
  const char base;
  std::vector<node> data;

public:
  prefix_tree(char base = 'a', char root = '$'): base(base) { data.emplace_back(root); }

  void add(const std::string& str, int index) {
    int pos = 0;
    for (int i = 0; i < str.size(); ++i) {
      int k = str[i] - base;
      if (data[pos].next[k] != -1) {
        pos = data[pos].next[k];
        continue;
      }
      int pos_new = data.size();
      data[pos].next[k] = pos_new;
      data.emplace_back(str[i]);
      pos = pos_new;
    }
    data[pos].index = index;
  }

  int find(const std::string& str) const {
    int pos = 0;
    for (int i = 0; i < str.size(); ++i) {
      int k = str[i] - base;
      if (data[pos].next[k] == -1) {
        return -1;
      }
      pos = data[pos].next[k];
    }
    return pos;
  }

  int find(int i, char c) const {
    return data[i].next[c - base];
  }
  int index(int i) const {
    return i == -1 ? -1 : data[i].index;
  }

};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

